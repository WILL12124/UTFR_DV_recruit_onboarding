# Final Project: Cone Path Traversal

## The problem

You're given:

- A list of points scattered around the car (world frame, units are meters)
- The car's current state: position `(x, y)` and heading

Your job: write a function that builds a path through as many of those points
as it can, starting from the car and always moving forward, subject to two hard
constraints on every step.

Concretely:

1. Start at the car's position and heading.
2. Find the nearest point that satisfies **both** constraints below.
3. Move to it. Your heading now points from where you just were to where you
   just went.
4. Repeat until no valid next point exists.
5. Return the points in the order you visited them.

### Hard constraints on every step

| Constraint | Value |
|------------|-------|
| **Max step distance** | The next point must be ≤ **10 m** from your current position. |
| **Heading cone** | The next point must lie within **±30°** of your current heading. |

Both must hold simultaneously. If no candidate satisfies both, the path ends.

## What "ahead" means

Heading is in radians, using the standard math convention: 0 radians points
along `+x`, and the angle increases counter-clockwise (so `pi/2` points along
`+y`). Within the heading cone means the angle between your heading vector and
the vector to the candidate point is ≤ 30°, equivalently the normalised dot
product (cosine) is ≥ cos(30°) ≈ 0.866.

## What you're implementing

Everything you need to touch lives in `src/solution.cpp`:

```cpp
std::vector<Point> buildPath(const std::vector<Point>& points, const CarState& car);
```

- `points` — the full candidate list.
- `car` — starting `x`, `y`, `heading` (radians).
- Return value — the ordered sequence of points making up your path.
  Don't include the car's own starting position in the returned vector.

Don't change the function signature — the test runner calls it directly
and won't compile if you do.

## Building and running

```
mkdir build && cd build
cmake ..
cmake --build .
./run_tests
```

## What the test runner checks

**Test A — Forward sanity.** A small, hand-built case where every point is
directly ahead of the last, 2 m apart and exactly on-axis. Both hard
constraints are satisfied by construction. If your algorithm can't pass
this, start here.

**Test B — Length check.** Runs on all three benchmark tracks. For every
point *not* in your path, checks that it isn't reachable from the path's
endpoint under the algorithm's own constraints (within 5 m **and** within
±30° of the final heading). If one is, your path quit too soon.

**Test C — Curviness score.** Not pass/fail — a number from 0 (perfectly
straight) to 1 (path reverses direction on every segment), averaged over
all turns. A straighter path scores closer to 0.

**Test D — Max step length.** Hard constraint check: every consecutive pair
of points in the path (including the car-to-first-point step) must be
within 10 m of each other.

**Runtime.** Wall-clock time for `buildPath` on each track, printed in
milliseconds.

## The three benchmark tracks

| Track   | Points | Car start (x, y) | Car heading         | Point radius |
|---------|--------|-------------------|----------------------|--------------|
| Track 1 | 15     | (0, 0)            | 0 rad (0°)          | 3–6 m        |
| Track 2 | 50     | (-5, -5)          | π/2 rad (90°)       | 3–8 m        |
| Track 3 | 500    | (-7, 10)          | -1 rad (~-57°)      | 3–10 m       |

All points are scattered randomly in a full circle around the car start
position (not just in front of it), so part of the problem is filtering
to candidates that satisfy the cone and distance constraints.

## Reading the plots

Every run writes one SVG per track (`track_1_plot.svg`, etc.) — open in a
browser. Grey dots are the full candidate set, the dark marker is the car
(with a short line showing its heading), and the red line is the path your
code produced.
