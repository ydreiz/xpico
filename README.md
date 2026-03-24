# xpico

A minimal X11 screen color picker for Linux. Click anywhere on the screen and get the hex color code copied to your clipboard.

## Features

- Crosshair cursor for precise pixel selection
- Outputs color as a lowercase hex string (e.g. `#1a2b3c`)
- Automatically copies the result to the system clipboard via `xclip`
- Single-file C implementation (~100 lines)

## Prerequisites

- X11-based desktop (does not work natively on Wayland)
- `libx11-dev` (build time)
- `xclip` (runtime)
- `clang` or `gcc`

On Debian/Ubuntu:

```bash
sudo apt install libx11-dev xclip clang
```

## Build

```bash
make
```

## Usage

```bash
./xpico
```

1. The cursor changes to a crosshair.
2. Click on any pixel on the screen.
3. The hex color code is printed to stdout and copied to your clipboard.

## Roadmap

- [ ] Magnified preview window around the cursor for precise pixel selection
- [ ] Multiple color format output: RGB, RGBA, HEX, HSL, HSV

## Acknowledgements

Inspired by [pico](https://github.com/sid-lakhani/pico) by sid-lakhani.

## License

[MIT](LICENSE)
