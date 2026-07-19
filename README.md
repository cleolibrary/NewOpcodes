# NewOpcodes

[![Build](https://github.com/cleolibrary/NewOpcodes/actions/workflows/release.yml/badge.svg)](https://github.com/cleolibrary/NewOpcodes/actions/workflows/release.yml)

A CLEO plugin by [DK22Pac](https://github.com/DK22Pac) that adds new opcodes for GTA San Andreas. Preserved and maintained with permission from the original author.

## Installation

1. Download the latest `NewOpcodes.cleo` from the [releases page](https://github.com/cleolibrary/NewOpcodes/releases).
2. Copy the file in the `CLEO` folder of your GTA San Andreas installation.

> **Note:** If using CLEO 5, copy the file in the `CLEO\CLEO_PLUGINS` folder instead.

## Documentation

Full documentation for all NewOpcodes commands is available on the **Sanny Builder Library**:

- https://library.sannybuilder.com/#/sa/script/extensions/NewOpcodes

## Build From Source

### Prerequisites

- Visual Studio 2022
- Git

### Build

```
git clone --recursive https://github.com/cleolibrary/NewOpcodes.git
cd NewOpcodes
```

If you already cloned without `--recursive`, run `git submodule update --init`.

1. Set environment variable `PLUGIN_SDK_DIR` to the `plugin-sdk` folder inside the repo.
2. Open `plugin-sdk\plugin.sln`, build `PLUGIN_SA` to produce `plugin-sdk\output\lib\plugin.lib`.
3. Open `newOpcodes.sln` and build to produce `build\newOpcodes.cleo`.

A pre-built `CLEO.lib` is included - no extra CLEO SDK setup needed.

## Notes

- **Author:** [DK22Pac](https://github.com/DK22Pac)
- **GTA Forums:** https://gtaforums.com/topic/518780-cleo4newopcodes-by-dk22pac/
