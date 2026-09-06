#pragma once
#include <string>
#include <vector>

#include "types.hpp"

// Writes an autoscaled SVG plot of the candidate points, the car, and the
// computed path to `filename`. Scaling is based on the bounding
// box/diameter of the point cloud (plus the car), so tracks of very
// different sizes and spreads all render at a readable size. Open the
// output file directly in a browser to view it.
void writeSvgPlot(const std::string& filename, const std::vector<Point>& points,
                   const std::vector<Point>& path, const CarState& car);
