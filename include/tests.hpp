#pragma once
#include <vector>

#include "types.hpp"

// ---- Test A: forward sanity ------------------------------------------------
// A small, hand-built fixture where every point is already directly ahead
// of the last one. The simplest possible case: if this fails, nothing else
// will work. Prints details and returns true on pass.
bool testForwardSanity();

// ---- Test B: length check ---------------------------------------------------
// Checks that the path didn't stop early: for every candidate point NOT
// used in the path, confirms it isn't sitting ahead of the path's final
// segment. If one is, the path quit too soon.
bool testLengthCheck(const std::vector<Point>& points, const CarState& car,
                      const std::vector<Point>& path);

// ---- Test C: curviness score -------------------------------------------------
// Not pass/fail. Normalized [0, 1] score for how much the path turns
// segment to segment: 0.0 = perfectly straight line, 1.0 = every turn is a
// full 180-degree reversal. Computed as the average absolute turning angle
// between consecutive segments, divided by pi.
double computeCurviness(const CarState& car, const std::vector<Point>& path);
