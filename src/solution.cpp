#include "solution_interface.hpp"
#include "constants.hpp"
#include <string>

const float MaxStep = 10.0;                 // in meter
const float MaxAngRad = 30.0 * kPi / 180.0; // in rad

// ============================================================================
// This is the only file you should need to edit.
// Read INSTRUCTIONS.md before you start.
// ============================================================================
Point CheckNearestPoint(CarState &car)
{
    //
}

std::vector<Point> buildPath(const std::vector<Point> &points, const CarState &car)
{
    // check nearest
    for (int i = 0; i < points.size(); i++)
    {
        double CheckDistance(points[i], );
    }

    Point CheckNearestPoint(car);
    // Returning an empty path for now so the project builds and the test
    // runner runs end-to-end - everything will fail until you implement this.
    return {};
}
