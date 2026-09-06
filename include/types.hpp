#pragma once

// A single 2D point in the world frame. Units are meters.
struct Point {
    double x = 0.0;
    double y = 0.0;
};

// The car's state: position (x, y) and heading.
//
// heading is in radians, using the standard math convention:
//   0 radians      -> facing the +x direction
//   pi/2 radians   -> facing the +y direction
// and increases counter-clockwise, same convention as std::atan2(dy, dx).
struct CarState {
    double x = 0.0;
    double y = 0.0;
    double heading = 0.0;
};
