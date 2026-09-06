#include "track_generator.hpp"

#include <cmath>
#include <random>
#include <utility>

#include "constants.hpp"

namespace {

// Scatters `count` points at a random angle and random radius around
// (originX, originY) - i.e. anywhere in a full circle around the car, not
// just in front of it. Fixed seed -> reproducible track across runs.
std::vector<Point> scatterPointsAround(double originX, double originY, int count,
                                        double minRadius, double maxRadius,
                                        unsigned seed) {
    std::mt19937 rng(seed);
    std::uniform_real_distribution<double> angleDist(0.0, 2.0 * kPi);
    std::uniform_real_distribution<double> radiusDist(minRadius, maxRadius);

    std::vector<Point> pts;
    pts.reserve(static_cast<size_t>(count));
    for (int i = 0; i < count; ++i) {
        double angle = angleDist(rng);
        double radius = radiusDist(rng);
        pts.push_back({originX + radius * std::cos(angle),
                       originY + radius * std::sin(angle)});
    }
    return pts;
}

}  // namespace

std::vector<Track> generateBenchmarkTracks() {
    std::vector<Track> tracks;

    // Track 1: 15 points, car at origin facing +x (heading 0 rad / 0 deg).
    {
        Track t;
        t.name = "track_1";
        t.car = {0.0, 0.0, 0.0};
        t.points = scatterPointsAround(t.car.x, t.car.y, 15, 3.0, 25.0, 101);
        tracks.push_back(std::move(t));
    }

    // Track 2: 50 points, car at (-5, -5) facing +y (heading pi/2 rad / 90 deg).
    {
        Track t;
        t.name = "track_2";
        t.car = {-5.0, -5.0, kPi / 2.0};
        t.points = scatterPointsAround(t.car.x, t.car.y, 50, 3.0, 35.0, 202);
        tracks.push_back(std::move(t));
    }

    // Track 3: 500 points, car at (-7, 10) facing heading = -1 rad (~-57.3 deg).
    {
        Track t;
        t.name = "track_3";
        t.car = {-7.0, 10.0, -1.0};
        t.points = scatterPointsAround(t.car.x, t.car.y, 500, 3.0, 60.0, 303);
        tracks.push_back(std::move(t));
    }

    return tracks;
}
