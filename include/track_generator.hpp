#pragma once
#include <string>
#include <vector>

#include "types.hpp"

struct Track {
    std::string name;
    CarState car;
    std::vector<Point> points;
};

// Generates the three fixed benchmark tracks used by the test runner.
// Each track uses a fixed RNG seed, so results are reproducible run to run.
std::vector<Track> generateBenchmarkTracks();
