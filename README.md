# LCC Robotics 2024 Repository

This repo contains the code for LCC's robot for Kryptik 2024, a robotics competition hosted
by [CRC Robotics](https://robo-crc.ca/).

The project is scaffolded using the [`PlatformIO`](https://platformio.org/) framework, as it allows for flexible and platform-agnostic projects for embedded applications
with minimal configuration.

## Cloning the Repo

Make sure you have [`git`](https://git-scm.com/) installed on your machine. Then, clone this repository by command line:

```shell
git clone --recurse-submodules https://github.com/LCC-Robotics/LCC-Robotics-CRC-2023.git
```

## Build and Upload

The full list of build methods can be found in PlatformIO's [docs](https://docs.platformio.org/en/latest/).

### VSCode Extension

Install the PlatformIO extension
for [VSCode](https://marketplace.visualstudio.com/items?itemName=platformio.platformio-ide).

Open the project in `VSCode`. Then, in the PlatformIO extension menu, press `Build` to build the project, or
press `Upload` to build and upload the
firmware to the board.

### PlatformIO Core (CLI)

Install the PlatformIO [CLI tool](https://docs.platformio.org/en/stable/core/index.html).

`cd` into the project directory. Then, run one of the following commands:

```shell
# build only (default=release)
pio run

# build only (debug)
pio run --environment debug

# build and upload (default=release)
pio run --target upload

# build and upload (debug)
pio run --environment debug --target upload
```

## Compilation Database

If you are using `clangd` or an IDE such as `CLion`, you will need to generate `compile_commands.json` in order to get
code completion and error checking working.

Generate `compile_commands.json` using `PlatformIO CLI`:

```shell
pio run --target compiledb
```

## Authors

[Kenneth Lew](https://github.com/lew1101)

[Angela Wang](https://github.com/A-Blve)
