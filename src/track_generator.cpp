#include "track_generator.hpp"

#include <cmath>
#include <random>
#include <utility>

#include "constants.hpp"

namespace {

// Scatters `count` points randomly around (originX, originY) within maxRadius.
// Two constraints are enforced via rejection sampling:
//   - every point is at least carClearance metres from the car
//   - every point is at least minSpacing metres from every other placed point
std::vector<Point> scatterPointsAround(double originX, double originY, int count,
                                        double maxRadius,
                                        double carClearance,
                                        double minSpacing,
                                        unsigned seed) {
    std::mt19937 rng(seed);
    std::uniform_real_distribution<double> angleDist(0.0, 2.0 * kPi);
    std::uniform_real_distribution<double> radiusDist(0.0, maxRadius);

    const double carClearSq  = carClearance * carClearance;
    const double minSpacingSq = minSpacing * minSpacing;

    std::vector<Point> pts;
    pts.reserve(static_cast<size_t>(count));

    // Cap retries per point to avoid an infinite loop if the area is too full.
    const int kMaxAttempts = 100'000;
    int attempts = 0;
    while (static_cast<int>(pts.size()) < count && attempts < kMaxAttempts) {
        ++attempts;
        double angle  = angleDist(rng);
        double radius = radiusDist(rng);
        Point  c{originX + radius * std::cos(angle),
                 originY + radius * std::sin(angle)};

        // Must be at least carClearance from the car.
        double dcx = c.x - originX;
        double dcy = c.y - originY;
        if (dcx * dcx + dcy * dcy < carClearSq) continue;

        // Must be at least minSpacing from every already-placed point.
        bool tooClose = false;
        for (const auto& p : pts) {
            double dx = c.x - p.x;
            double dy = c.y - p.y;
            if (dx * dx + dy * dy < minSpacingSq) { tooClose = true; break; }
        }
        if (tooClose) continue;

        pts.push_back(c);
        attempts = 0;  // reset on a successful placement
    }
    return pts;
}

}  // namespace

std::vector<Track> generateBenchmarkTracks() {
    std::vector<Track> tracks;

    // Track 1: 15 points, car at origin facing +x (0 rad).
    {
        Track t;
        t.name   = "track_1";
        t.car    = {0.0, 0.0, 0.0};
        t.points = scatterPointsAround(t.car.x, t.car.y, 15, 15.0, 1.5, 3.0, 101);
        tracks.push_back(std::move(t));
    }

    // Track 2: 50 points, car at (-5, -5) facing +y (pi/2 rad).
    {
        Track t;
        t.name   = "track_2";
        t.car    = {-5.0, -5.0, kPi / 2.0};
        t.points = scatterPointsAround(t.car.x, t.car.y, 50, 25.0, 1.5, 3.0, 202);
        tracks.push_back(std::move(t));
    }

    // Track 3: 500 points, car at (-7, 10) facing -1 rad (~-57°).
    {
        Track t;
        t.name   = "track_3";
        t.car    = {-7.0, 10.0, -1.0};
        t.points = scatterPointsAround(t.car.x, t.car.y, 500, 60.0, 1.5, 3.0, 303);
        tracks.push_back(std::move(t));
    }

    return tracks;
}
