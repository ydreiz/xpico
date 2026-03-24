#include <alloca.h>
#include <stdio.h>
#include <stdlib.h>

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/cursorfont.h>

#ifdef __clang__
#define GET_COLUMN() __builtin_COLUMN()
#else
#define GET_COLUMN() 0 // GCC doesn't support __builtin_COLUMN()
#endif

#define ERROR(msg)                                                             \
  do {                                                                         \
    fprintf(stderr, "%s:%d:%d: [ERROR] %s\n", __FILE__, __LINE__,              \
            GET_COLUMN(), msg);                                                \
  } while (0)

#define ERROR_EXIT(msg)                                                        \
  do {                                                                         \
    ERROR((msg));                                                              \
    exit(EXIT_FAILURE);                                                        \
  } while (0)

void exec_clipboard(const char *color);

int handle_x_errors(Display *dpy, XErrorEvent *err) {
  char error_text[1024];
  char message[2048];

  XGetErrorText(dpy, err->error_code, error_text, sizeof(error_text));

  snprintf(message, sizeof(message), "X11 Error %s (Request code: %d)\n",
           error_text, err->request_code);
  ERROR(message);

  return 0;
}

int main(void) {
  Display *dpy = XOpenDisplay(NULL);
  if (dpy == NULL) {
    ERROR_EXIT("xpico failed to open display");
  }
  XSetErrorHandler(handle_x_errors);

  Window root = XRootWindow(dpy, XDefaultScreen(dpy));

  Cursor cursor = XCreateFontCursor(dpy, XC_crosshair);
  XDefineCursor(dpy, root, cursor);

  unsigned int mask = ButtonPressMask;

  int grab = XGrabPointer(dpy, root, True, mask, GrabModeAsync, GrabModeAsync,
                          0, cursor, CurrentTime);
  if (grab != GrabSuccess) {
    ERROR_EXIT("xpico failed to grab pointer");
  }

  unsigned long pixel;
  XEvent event = {0};
  while (1) {
    XNextEvent(dpy, &event);
    if (event.type == ButtonPress) {
      int x = event.xbutton.x_root;
      int y = event.xbutton.y_root;

      XImage *image = XGetImage(dpy, root, x, y, 2, 2, AllPlanes, ZPixmap);
      if (image == NULL) {
        ERROR_EXIT("xpico failed to get image");
      }
      if (image->data == NULL) {
        ERROR_EXIT("xpico failed to get image data");
      }
      pixel = XGetPixel(image, 0, 0);

      XDestroyImage(image);
      XUngrabPointer(dpy, CurrentTime);
      break;
    }
  }

  unsigned long hex = (pixel & 0xFFFFFF);

  char hex_buff[128];
  snprintf(hex_buff, sizeof(hex_buff), "#%06lx", hex);

  exec_clipboard(hex_buff);

  XCloseDisplay(dpy);
  return 0;
}

void exec_clipboard(const char *color) {
  if (system("which xclip > /dev/null 2>&1") == -1) {
    ERROR("xclip is not installed. Please install it to use clipboard "
          "functionality.");
    return;
  }

  char cmd[128];
  snprintf(cmd, sizeof(cmd), "echo -n '%s' | xclip -selection clipboard",
           color);
  if (system(cmd) == -1) {
    ERROR("Failed to copy to clipboard. Is 'xclip' installed?");
  } else {
    fprintf(stdout, "%s\n", color);
  }
}
