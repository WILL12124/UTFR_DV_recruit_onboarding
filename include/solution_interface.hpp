#pragma once
#include <vector>

#include "types.hpp"

// ============================================================================
// THE PROBLEM  (full write-up: INSTRUCTIONS.md)
// ============================================================================
// You're given a set of candidate points scattered around the car, and the
// car's current position + heading. Build a path that:
//
//   - starts at the car and moves only forward, point to point
//   - is as short and as straight as you can reasonably make it
//   - keeps extending forward until there is nothing left ahead of it
//
// Implement this function in solution.cpp. Do not change the signature -
// the test runner calls it directly and won't compile if you do.
//
// Return the ordered sequence of points that make up your path. Do not
// include the car's own starting position in the returned vector.
// ============================================================================
std::vector<Point> buildPath(const std::vector<Point>& points, const CarState& car);
