#include "svg_plot.hpp"

#include <algorithm>
#include <cmath>
#include <fstream>
#include <utility>

namespace {

constexpr double kCanvasSize = 900.0;
constexpr double kMargin = 60.0;

struct Bounds {
    double minX, maxX, minY, maxY;
};

Bounds computeBounds(const std::vector<Point>& points, const CarState& car) {
    Bounds b{car.x, car.x, car.y, car.y};
    for (const auto& p : points) {
        b.minX = std::min(b.minX, p.x);
        b.maxX = std::max(b.maxX, p.x);
        b.minY = std::min(b.minY, p.y);
        b.maxY = std::max(b.maxY, p.y);
    }
    return b;
}

}  // namespace

void writeSvgPlot(const std::string& filename, const std::vector<Point>& points,
                   const std::vector<Point>& path, const CarState& car) {
    Bounds b = computeBounds(points, car);

    // The "diameter" of the point distribution - the larger of the x/y
    // spans. We scale the drawing to this, so a tight cluster of 15 points
    // and a wide spread of 500 both fill the canvas instead of one being a
    // speck in the corner.
    double spanX = std::max(b.maxX - b.minX, 1e-6);
    double spanY = std::max(b.maxY - b.minY, 1e-6);
    double diameter = std::max(spanX, spanY);

    double drawable = kCanvasSize - 2.0 * kMargin;
    double scale = drawable / diameter;

    double centerX = (b.minX + b.maxX) / 2.0;
    double centerY = (b.minY + b.maxY) / 2.0;

    // World space -> SVG pixel space. SVG y grows downward, so flip y.
    auto toPx = [&](const Point& p) -> std::pair<double, double> {
        double px = kCanvasSize / 2.0 + (p.x - centerX) * scale;
        double py = kCanvasSize / 2.0 - (p.y - centerY) * scale;
        return {px, py};
    };

    std::ofstream f(filename);
    f << "<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"" << kCanvasSize
      << "\" height=\"" << kCanvasSize << "\" viewBox=\"0 0 " << kCanvasSize << " "
      << kCanvasSize << "\">\n";
    f << "<rect width=\"100%\" height=\"100%\" fill=\"white\"/>\n";

    // Candidate points: small grey dots.
    for (const auto& p : points) {
        auto [px, py] = toPx(p);
        f << "<circle cx=\"" << px << "\" cy=\"" << py << "\" r=\"4\" fill=\"#999999\"/>\n";
    }

    // Computed path: red line from the car through each visited point.
    if (!path.empty()) {
        auto [startPx, startPy] = toPx({car.x, car.y});
        f << "<polyline points=\"" << startPx << "," << startPy << " ";
        for (const auto& p : path) {
            auto [px, py] = toPx(p);
            f << px << "," << py << " ";
        }
        f << "\" fill=\"none\" stroke=\"#d62828\" stroke-width=\"3\"/>\n";

        for (const auto& p : path) {
            auto [px, py] = toPx(p);
            f << "<circle cx=\"" << px << "\" cy=\"" << py << "\" r=\"5\" fill=\"#d62828\"/>\n";
        }
    }

    // Car marker: dark dot plus a short line showing heading direction.
    {
        auto [px, py] = toPx({car.x, car.y});
        f << "<circle cx=\"" << px << "\" cy=\"" << py << "\" r=\"8\" fill=\"#1d3557\"/>\n";
        double headingLen = 30.0;
        double hx = px + headingLen * std::cos(car.heading);
        double hy = py - headingLen * std::sin(car.heading);
        f << "<line x1=\"" << px << "\" y1=\"" << py << "\" x2=\"" << hx << "\" y2=\"" << hy
          << "\" stroke=\"#1d3557\" stroke-width=\"3\"/>\n";
    }

    f << "</svg>\n";
}
