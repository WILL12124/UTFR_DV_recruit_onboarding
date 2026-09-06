#include "tests.hpp"

#include <cmath>
#include <iostream>

#include "constants.hpp"
#include "solution_interface.hpp"

namespace {

double normalizeAngle(double a) {
    while (a >  kPi) a -= 2.0 * kPi;
    while (a < -kPi) a += 2.0 * kPi;
    return a;
}

}  // namespace

bool testForwardSanity() {
    // Car at origin facing +x. Five points placed directly along +x, each 2 m
    // apart — well within the 5 m step limit and the ±30° cone.
    CarState car{0.0, 0.0, 0.0};
    std::vector<Point> points = {{2.0, 0.0}, {4.0, 0.0}, {6.0, 0.0}, {8.0, 0.0}, {10.0, 0.0}};

    std::vector<Point> path = buildPath(points, car);

    bool pass = true;
    if (path.size() != points.size()) {
        pass = false;
    } else {
        double lastX = car.x;
        for (const auto& p : path) {
            if (p.x <= lastX) { pass = false; break; }
            if (std::abs(p.y - car.y) > 1e-6) { pass = false; break; }
            lastX = p.x;
        }
    }

    std::cout << "[Test A] Forward sanity: " << (pass ? "PASS" : "FAIL")
              << " (expected " << points.size() << " points visited in order, got "
              << path.size() << ")\n";
    return pass;
}

bool testLengthCheck(const std::vector<Point>& points, const CarState& car,
                     const std::vector<Point>& path,
                     double maxStepDist, double coneHalfDeg) {
    const double minCos = std::cos(coneHalfDeg * kPi / 180.0);

    Point lastPos = path.empty() ? Point{car.x, car.y} : path.back();

    double heading = car.heading;
    if (!path.empty()) {
        Point prev = (path.size() >= 2) ? path[path.size() - 2] : Point{car.x, car.y};
        heading = std::atan2(lastPos.y - prev.y, lastPos.x - prev.x);
    }

    double fwdX = std::cos(heading);
    double fwdY = std::sin(heading);

    auto inPath = [&](const Point& p) {
        for (const auto& q : path)
            if (std::abs(p.x - q.x) < 1e-9 && std::abs(p.y - q.y) < 1e-9) return true;
        return false;
    };

    bool pass = true;
    int  strandedCount = 0;
    for (const auto& p : points) {
        if (inPath(p)) continue;
        double dx   = p.x - lastPos.x;
        double dy   = p.y - lastPos.y;
        double dist = std::sqrt(dx * dx + dy * dy);

        // Only counts as stranded if reachable under algorithm constraints.
        if (dist > maxStepDist + 1e-6) continue;
        if (dist < 1e-9) continue;
        double cosAngle = (dx * fwdX + dy * fwdY) / dist;
        if (cosAngle < minCos) continue;

        pass = false;
        ++strandedCount;
    }

    std::cout << "[Test B] Length check: " << (pass ? "PASS" : "FAIL");
    if (!pass)
        std::cout << " (" << strandedCount
                  << " reachable point(s) still ahead of the path's endpoint)";
    std::cout << "\n";
    return pass;
}

double computeCurviness(const CarState& car, const std::vector<Point>& path) {
    if (path.size() < 2) return 0.0;

    std::vector<double> headings;
    Point prev{car.x, car.y};
    for (const auto& p : path) {
        headings.push_back(std::atan2(p.y - prev.y, p.x - prev.x));
        prev = p;
    }

    double totalTurn = 0.0;
    for (size_t i = 1; i < headings.size(); ++i)
        totalTurn += std::abs(normalizeAngle(headings[i] - headings[i - 1]));

    double avgTurn = totalTurn / static_cast<double>(headings.size() - 1);
    return avgTurn / kPi;
}

bool testMaxStepLength(const CarState& car, const std::vector<Point>& path,
                       double maxDist) {
    bool pass       = true;
    int  violations = 0;
    Point prev{car.x, car.y};
    for (const auto& p : path) {
        double dx   = p.x - prev.x;
        double dy   = p.y - prev.y;
        double dist = std::sqrt(dx * dx + dy * dy);
        if (dist > maxDist + 1e-6) {
            pass = false;
            ++violations;
        }
        prev = p;
    }

    std::cout << "[Test D] Max step length (" << maxDist << " m): "
              << (pass ? "PASS" : "FAIL");
    if (!pass)
        std::cout << " (" << violations << " step(s) exceeded " << maxDist << " m)";
    std::cout << "\n";
    return pass;
}
