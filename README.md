# Advent of Code - C++ Solutions

Welcome to my collection of [Advent of Code](https://adventofcode.com/) solutions written in C++! This repository contains my journey through the annual programming puzzles, solving challenges day by day with clean, efficient C++ code.

Whether you're here to see how I tackled these puzzles, learn from the solutions, or just enjoy some C++ code, you're in the right place! Each year brings new challenges, and this repository will grow with each puzzle solved.

## Building

Getting started is easy! Here's everything you need to build and run the solutions.

### Prerequisites

- CMake 3.10 or higher - For managing the build system
- Some kind of compiler (I tested with MSVC. Clang or the like should work fine though.)

### Build Instructions

```bash
# Create build directory
mkdir build
cd build

# Configure and build
cmake ..
cmake --build .
```

The executables will be created in the `build/` directory (or `build/Debug/` on Windows). Each year gets its own executable (e.g., `aoc2025`, `aoc2026`).

## Usage

### Running a Day

Each year has a single executable that accepts a day number as an argument:

```bash
# From the build directory
./aoc2025 1          # Run day 1
./aoc2025 2          # Run day 2
./aoc2025 -1         # Alternative syntax
./aoc2025 --day 1    # Alternative syntax

# On Windows
aoc2025.exe 1
aoc2025.exe 2

# Or from project root
./build/aoc2025 1
```

Just run the executable with a day number and watch it solve the puzzle! The output will show both part 1 and part 2 results.

### Input Files

Place your puzzle input files in the `puzzle_input/` folder at the project root. Files should be named without any extension (just the day name):

- `puzzle_input/day_1`
- `puzzle_input/day_2`
- etc.

The program will automatically search for input files in the `puzzle_input/` folder, starting from the project root and checking parent directories if needed. No need to worry about paths - it just works!

#### Alternative Input Locations

You can also specify a custom input directory using environment variables:

```bash
# Windows (CMD)
set AOC_INPUT_DIR=C:\path\to\inputs

# Windows (PowerShell)
$env:AOC_INPUT_DIR = "C:\path\to\inputs"

# Linux/Mac
export AOC_INPUT_DIR=/path/to/inputs
```

## Adding a New Day

Ready to tackle a new puzzle? Here's how to add your solution:

1. Create a new directory: `src/YYYY/day_N/` (where YYYY is the year and N is the day number)
2. Create the following files:
   - `day_N.h` - Header file with day-specific structures and function declarations
   - `day_N.cpp` - Implementation file with your solution logic

3. Add your day function to the year's `main.cpp`:
   - Include the header: `#include "day_N/day_N.h"`
   - Add to the day functions map: `{N, run_day_N}`

4. The build system automatically finds your new days source files

5. Use the common utilities from `common.h`:

```cpp
#include "../common.h"

void run_day_N(Answer& answer) {
    std::string input = read_puzzle_input("day_N");
    // Your solution here
    answer.add("1: " + std::to_string(result1));
    answer.add("2: " + std::to_string(result2));
}
```

That's it! The build system will automatically pick up your new day and include it in the year's executable.

## Adding a New Year

Starting a new year of Advent of Code? Let's set it up!

1. Create a new directory: `src/YYYY/` (where YYYY is the year)
2. Copy the following files from an existing year:
   - `common.h`
   - `common.cpp`
   - `main.cpp`
   - `CMakeLists.txt` (update the year references if needed)
3. Start adding day solutions following the structure above

Each year is self-contained with its own executable, so you can work on multiple years simultaneously without anything conflicting with each other. The root CMakeLists.txt will automatically discover and build all years!

## Common Utilities

The `common.h` header provides helpful utilities that make solving puzzles easier:

- `RisError` - Class for error handling
- `Answer` - Structure to collect and print results beautifully
- `read_puzzle_input(key)` - Function to read puzzle input files automatically

This all handles the boring stuff so you can focus on solving puzzles! Here's how to use them:

```cpp
#include "../common.h"

void run_day_N(Answer& answer) {
    try {
        std::string input = read_puzzle_input("day_N");
        // Process input and solve the puzzle...
        answer.add("1: " + std::to_string(part1_result));
        answer.add("2: " + std::to_string(part2_result));
    } catch (const RisError& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        throw;
    }
}
```

## License

MIT License - see [LICENSE](LICENSE) file for details.

