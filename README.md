# Advent of Code 2021 C++ Solutions

This repository contains my C++ solutions for **[Advent of Code 2021](https://adventofcode.com/2021)**.  
Each puzzle day is built as a **separate executable** using **CMake**, with its own input file and logic.

## Building

This project uses **CMake** to generate platform-specific build files.  
Make sure you have a C++20 compiler and CMake ≥ 3.10 installed.

## Build instructions (Linux / WSL)

```bash
# Clone the repo
git clone https://github.com/kactasar/AOC-2021.git
cd AOC-2021

# Create and enter a build directory
mkdir build && cd build

# Configure CMake
cmake ..

# Build all executables
cmake --build .
```

After building, all executables will be located in build/bin/

Puzzle input files placed in data/ will be automatically copied to build/bin/data/ during the build process. These input files are not included in the repository and must follow the dayXX_input.txt naming scheme (e.g. day01_input.txt).