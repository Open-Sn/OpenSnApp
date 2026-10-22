Standalone ROM application built around OpenSn and libROM, with supporting Python tooling and example input decks.

This repo is organized to:
- build a C++ application/binary that links against OpenSn and libROM,
- run transport problems and ROM workflows from Python drivers,
- keep reproducible example cases in a single place.

## Repository layout

- [src/](src/README.md) — C++ sources for the application (python bindings, app-specific code)
- [python/](python/README.md) — Python drivers/utilities (e.g., job management, ROM pipeline orchestration)
- [examples/](examples/README.md) — Example decks, runs, and reference cases

# Quickstart

## Dependencies

This repository builds a standalone application that links against a libROM installation, an OpenSn installation and certain OpenSn dependencies.

You must have the following available:

- OpenSn
- libROM
- OpenSn dependencies (VTK, Caliper, MPI, Python with pybind11)

---

## Build

From the `ROM` directory, point CMake at the OpenSn installation prefix and
the libROM installation:

```bash
cmake -S . -B build \
  -DCMAKE_PREFIX_PATH=<path-to-opensn-install> \
  -DLIBROM_DIR=<path-to-librom-install>
cmake --build build -j
```

Alternatively, set `OpenSn_DIR` directly to
`<path-to-opensn-install>/lib/cmake/opensn`. OpenSn's package configuration
locates its own MPI, PETSc, VTK, Caliper, Boost, Python, and pybind11
dependencies.
An example can be run from its respective folder with
```bash
python run_rom_*.py --exe=path/to/app/exe
```
