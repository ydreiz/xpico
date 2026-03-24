.PHONY:

CC = clang
CFLAGS = -Wall -Wextra -pedantic -ggdb
LDFLAGS = -lX11

xpico: main.c
	$(CC) -o xpico main.c $(LDFLAGS) $(CFLAGS)
