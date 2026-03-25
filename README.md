# xpico

Minimal X11 screen color picker for Linux.

`xpico` grabs the pointer, lets you click any pixel on screen, prints its color
as lowercase HEX (`#rrggbb`) and copies it to the clipboard via `xclip`.

## Table of contents

- [About](#about)
- [Features](#features)
- [Requirements](#requirements)
- [Quick install (release binary)](#quick-install-release-binary)
- [Build from source](#build-from-source)
- [Run](#run)
- [Project structure](#project-structure)
- [Release process](#release-process)
- [Contributing](#contributing)
- [License](#license)

## About

`xpico` is a small C utility for Linux/X11 desktops.

Typical flow:

1. Run `xpico`
2. Cursor changes to crosshair
3. Click any pixel
4. HEX color is printed to stdout and copied to clipboard

This makes it useful for scripts, terminal workflows, and quick color sampling.

## Features

- Crosshair cursor for precise pixel selection
- Lowercase HEX output (`#rrggbb`)
- Clipboard copy through `xclip`
- Local build/install through `make`
- Release-binary install via `scripts/install.sh`

## Requirements

### Runtime

- Linux with X11
- `xclip` (required for clipboard copy)

### Build from source

- GCC and `make`
- X11 development package (`libX11` headers/libs)

### Dependencies by distro

#### Debian/Ubuntu

```bash
sudo apt update
sudo apt install build-essential libx11-dev xclip
```

#### Fedora

```bash
sudo dnf install gcc make libX11-devel xclip
```

#### Arch Linux

```bash
sudo pacman -S base-devel libx11 xclip
```

## Quick install (release binary)

Install latest release to `~/.local/bin/xpico`:

```bash
curl -fsSL https://raw.githubusercontent.com/ydreiz/xpico/refs/heads/main/scripts/install.sh | bash
```

Install a specific version:

```bash
TAG=v1.0.0 curl -fsSL https://raw.githubusercontent.com/ydreiz/xpico/refs/heads/main/scripts/install.sh | bash
```

Uninstall:

```bash
curl -fsSL https://raw.githubusercontent.com/ydreiz/xpico/refs/heads/main/scripts/uninstall.sh | bash
```

Supported release architectures: `x86_64`, `arm64`.

## Build from source

### Debug build (default)

```bash
make
```

Builds `xpico` with debug flags.

### Release build

```bash
make release
```

Builds optimized binary and strips symbols.

### Local install/uninstall

By default, install target is `~/.local/bin`.

```bash
make install
make uninstall
```

### Clean

```bash
make clean
```

## Run

From repository root:

```bash
./xpico
```

If installed and `~/.local/bin` is in `PATH`:

```bash
xpico
```

Example output:

```text
#1a2b3c
```

## Project structure

```text
.
├── main.c
├── Makefile
├── scripts/
│   ├── install.sh
│   └── uninstall.sh
└── .github/workflows/
    └── build-and-release.yml
```

## Release process

Pushing a tag matching `v*` triggers GitHub Actions to:

1. Build release binaries for `x86_64` and `arm64`
2. Pack each binary to `xpico-<arch>.tar.gz`
3. Publish assets in a GitHub Release

Workflow file: `.github/workflows/build-and-release.yml`.

## Contributing

This repository is a small C utility project; improvements are welcome.

1. Fork the repository
2. Create a feature branch
3. Commit changes
4. Open a pull request

## Acknowledgements

Inspired by [pico](https://github.com/sid-lakhani/pico) by sid-lakhani.

## License

This project is licensed under the MIT License. See `LICENSE` for details.
