#include <chrono>
#include <iomanip>
#include <iostream>

#include "solution_interface.hpp"
#include "svg_plot.hpp"
#include "tests.hpp"
#include "track_generator.hpp"

int main() {
    std::cout << "=== UTFR Driverless Final Project: Cone Path Traversal ===\n\n";

    bool sanityPass = testForwardSanity();
    std::cout << "\n";

    auto tracks = generateBenchmarkTracks();

    int passedChecks = sanityPass ? 1 : 0;
    int totalChecks = 1;

    for (const auto& track : tracks) {
        std::cout << "--- " << track.name << " (" << track.points.size() << " points) ---\n";

        auto startTime = std::chrono::high_resolution_clock::now();
        std::vector<Point> path = buildPath(track.points, track.car);
        auto endTime = std::chrono::high_resolution_clock::now();
        double ms = std::chrono::duration<double, std::milli>(endTime - startTime).count();

        bool lengthOk = testLengthCheck(track.points, track.car, path);
        double curviness = computeCurviness(track.car, path);

        std::cout << "[Test C] Curviness score: " << std::fixed << std::setprecision(4)
                  << curviness << " (0 = straight, 1 = max curvy)\n";
        std::cout << "[Info]   Runtime: " << std::fixed << std::setprecision(3) << ms << " ms\n";
        std::cout << "[Info]   Path length: " << path.size() << " / " << track.points.size()
                  << " points used\n";

        std::string svgName = track.name + "_plot.svg";
        writeSvgPlot(svgName, track.points, path, track.car);
        std::cout << "[Info]   Plot written to " << svgName << "\n";

        ++totalChecks;
        if (lengthOk) ++passedChecks;
        std::cout << "\n";
    }

    std::cout << "=== " << passedChecks << "/" << totalChecks << " checks passed ===\n";
    return (passedChecks == totalChecks) ? 0 : 1;
}
