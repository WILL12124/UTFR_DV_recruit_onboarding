#pragma once

// Defined here instead of relying on M_PI, which isn't guaranteed to exist
// in <cmath> on every platform/compiler flag combination.
constexpr double kPi = 3.14159265358979323846;
