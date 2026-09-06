# Cone Path Traversal - Final Project

Read [INSTRUCTIONS.md](./INSTRUCTIONS.md) for the full problem statement
before touching any code.

## Quick start

```
mkdir build && cd build
cmake ..
cmake --build .
./run_tests
```

The only file you should need to edit is `src/solution.cpp`.

## Layout

```
include/
  types.hpp               Point / CarState structs
  constants.hpp           shared math constant
  solution_interface.hpp  the function signature you implement
  track_generator.hpp     benchmark track generation
  svg_plot.hpp            plotting
  tests.hpp               the four checks the runner performs
src/
  solution.cpp            <-- you edit this one
  track_generator.cpp
  svg_plot.cpp
  tests.cpp
  run_tests.cpp           main() - runs everything, prints results
```
