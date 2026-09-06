#pragma once
#include <vector>

#include "types.hpp"

// ---- Test A: forward sanity ------------------------------------------------
// A small, hand-built fixture where every point is directly ahead of the last,
// all within 5 m and well within the ±30° cone. The simplest possible case:
// if this fails, nothing else will work. Prints details and returns true on pass.
bool testForwardSanity();

// ---- Test B: length check ---------------------------------------------------
// Checks that the path didn't stop early: for every candidate point NOT used
// in the path, confirms it isn't reachable from the path's endpoint under the
// algorithm's own constraints (within maxStepDist AND within coneHalfDeg of
// the final heading). A reachable-but-skipped point means the path quit too soon.
bool testLengthCheck(const std::vector<Point>& points, const CarState& car,
                     const std::vector<Point>& path,
                     double maxStepDist, double coneHalfDeg);

// ---- Test C: curviness score ------------------------------------------------
// Not pass/fail. Normalised [0, 1] score for how much the path turns segment
// to segment: 0.0 = perfectly straight, 1.0 = every turn is a full 180-degree
// reversal. Computed as the average absolute turning angle between consecutive
// segments, divided by pi.
double computeCurviness(const CarState& car, const std::vector<Point>& path);

// ---- Test D: max step length ------------------------------------------------
// Hard constraint: every consecutive pair of points in the path (including the
// car-to-first-point step) must be within maxDist metres of each other.
// Returns true if all steps satisfy the constraint.
bool testMaxStepLength(const CarState& car, const std::vector<Point>& path,
                       double maxDist);
