# CMakeTutorial

This repository is a small, runnable CMake tutorial project that demonstrates how modern CMake models a project as a graph of targets instead of a pile of manual compiler and linker flags.

The example is centered on one executable, `Tutorial`, and four internal libraries:

- `libA`: a static library that demonstrates `PRIVATE` implementation details
- `libB`: a static library that demonstrates `PUBLIC` dependency propagation by linking `libA`
- `libC`: a header-only `INTERFACE` library
- `MathFunctions`: a small library that demonstrates platform-sensitive symbol detection and conditional math-library linkage

## Prerequisites

- CMake 3.15 or newer
- A working C++ compiler with C++14 support for the top-level executable
- A working C compiler because `CheckSymbolExists` probes C math headers during configuration
- A shell environment capable of running the generated build tool

Validated in this workspace on April 11, 2026 with AppleClang 21 on macOS.

## Quick Start

Configure the project with an out-of-source build:

```bash
cmake -S . -B build
```

Build everything:

```bash
cmake --build build
```

Run the test suite:

```bash
ctest --test-dir build --output-on-failure
```

Run the tutorial executable with a sample input:

```bash
./build/src/Tutorial 36
```

Install into a local staging prefix:

```bash
cmake --install build --prefix build/install
```

Run the installed executable:

```bash
./build/install/bin/Tutorial 36
```

## What You Should See

The executable prints one section per teaching point:

- project metadata from `TutorialConfig.h`
- `libA` output for `PRIVATE` usage
- `libB` output showing `PUBLIC` dependency propagation
- `libC` output showing header-only `INTERFACE` usage
- `MathFunctions` output showing detected math capabilities such as `LOG`, `EXP`, and `SQRT`

## Repository Layout

```text
.
├── CMakeLists.txt
├── TutorialConfig.h.in
├── src/
│   ├── CMakeLists.txt
│   └── main.cpp
├── libA/
│   ├── CMakeLists.txt
│   ├── libA.cpp
│   └── libA.h
├── libB/
│   ├── CMakeLists.txt
│   ├── libB.cpp
│   └── libB.h
├── libC/
│   ├── CMakeLists.txt
│   └── libC.h
├── MathFunctions/
│   ├── CMakeLists.txt
│   ├── MathFunctions.h
│   └── mysqrt.cxx
├── readme.org
└── CMake-Best-Practices---2nd-Edition-main/
```

### Directory Guide

- `CMakeLists.txt`: top-level project definition, feature checks, test registration, and install packaging
- `src/`: the `Tutorial` executable that exercises every library and prints the teaching output
- `libA/`: basic static library with `PRIVATE` compile options and public headers
- `libB/`: static library that links `libA` as `PUBLIC`
- `libC/`: header-only target implemented as an `INTERFACE` library
- `MathFunctions/`: feature detection and optional linkage to `m` on platforms that require it
- `readme.org`: Chinese companion guide with the same workflow and extra explanation
- `CMake-Best-Practices---2nd-Edition-main/`: imported reference material from the book sources, separate from the runnable tutorial at the repository root

## Suggested Walkthrough Order

If you are studying the project rather than only building it, read the files in this order:

1. `CMakeLists.txt`
2. `libA/CMakeLists.txt`
3. `libB/CMakeLists.txt`
4. `libC/CMakeLists.txt`
5. `MathFunctions/CMakeLists.txt`
6. `src/CMakeLists.txt`
7. `src/main.cpp`

This order makes the dependency graph easier to follow because the executable comes last, after the libraries it consumes.

## Build, Test, and Install Notes

- Use out-of-source builds only. The repository is set up for `build/`, `build-*`, and similar generated directories.
- `ctest` depends on the executable already being built. Configure alone is not enough.
- `cmake --install` also depends on a completed build because it installs the generated libraries and executable.
- The default build output for the executable is `build/src/Tutorial`.
- The default local install path from the command above is `build/install/`.

## Tutorial Concepts Mapped to Targets

| Target | Type | Main concept |
| --- | --- | --- |
| `libA` | Static library | `PRIVATE` compile options and implementation boundaries |
| `libB` | Static library | `PUBLIC` link propagation to consumers |
| `libC` | `INTERFACE` library | Header-only usage requirements |
| `MathFunctions` | Static library | Configure-time feature detection and conditional platform linkage |
| `Tutorial` | Executable | Consuming targets by declared dependencies instead of link-order micromanagement |

## Troubleshooting

### `ctest` says it cannot find `build/src/Tutorial`

You ran tests before the build completed. Run:

```bash
cmake --build build
ctest --test-dir build --output-on-failure
```

### `cmake --install` cannot find `.a` files or `Tutorial`

Install only after a successful build:

```bash
cmake --build build
cmake --install build --prefix build/install
```

### CMake reports that `MathFunctions` is linking against `m`

That is expected on platforms where math symbols are not provided without the math library. It is a successful feature-detection outcome, not a failure.

### You changed generators, compilers, or toolchains and configure behaves strangely

Remove the old build directory and configure again:

```bash
rm -rf build
cmake -S . -B build
```

### The executable path is not obvious

Before installation, run `./build/src/Tutorial`. After installation with the local prefix shown above, run `./build/install/bin/Tutorial`.

## Related Material

- `readme.org` provides a Chinese walkthrough of the same tutorial
- `CMake-Best-Practices---2nd-Edition-main/README.md` is the upstream reference bundle included in the workspace
