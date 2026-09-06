# Final Project: Cone Path Traversal

## The problem

You're given:

- A list of points scattered around the car (world frame, units are meters)
- The car's current state: position `(x, y)` and heading

Your job: write a function that builds a path through as many of those points
as it can, starting from the car and always moving forward, that is also as
short and as straight as you can reasonably make it.

Concretely:

1. Start at the car's position and heading.
2. Find the next point that lies ahead of your current direction of travel.
3. Move to it. Your direction of travel now points from where you just were
   to where you just went.
4. Repeat, extending the path forward, until nothing is left ahead of you.
5. Return the points in the order you visited them.

There's no single "correct" path here - this is a real path-planning
problem, not a puzzle with one right answer. The test runner checks a few
properties any reasonable solution should have (below), and reports a
runtime and a curviness score so you can see the shape of the trade-off
you're making.

## What "ahead" means

Heading is in radians, using the standard math convention: 0 radians points
along `+x`, and the angle increases counter-clockwise (so `pi/2` points
along `+y`). A point is "ahead" of your current position and heading if it
lies in the half-plane your heading vector points into - don't assume that
means "larger x". It depends entirely on your current heading, which
changes every time you move.

## What you're implementing

Everything you need to touch lives in `src/solution.cpp`:

```cpp
std::vector<Point> buildPath(const std::vector<Point>& points, const CarState& car);
```

- `points` - the full candidate list. Points not in your path may be
  behind the car, off to the side, or just unreachable in an all-forward
  path.
- `car` - starting `x`, `y`, `heading` (radians).
- Return value - the ordered sequence of points making up your path.
  Don't include the car's own starting position in the returned vector.

Don't change the function signature - the test runner calls it directly
and won't compile if you do.

## Building and running

```
mkdir build && cd build
cmake ..
cmake --build .
./run_tests
```

## What the test runner checks

**Test A - Forward sanity.** A small, hand-built case where every point is
already directly ahead of the last. If your algorithm can't pass this,
nothing else will work - start here.

**Test B - Length check.** Runs on all three benchmark tracks. Confirms
your path didn't stop early: for every point *not* in your path, checks
that it isn't sitting ahead of your path's last segment. If it is, your
path quit too soon.

**Test C - Curviness score.** Not pass/fail - a number from 0 (perfectly
straight) to 1 (the path reverses direction on every segment), averaged
over all the turns in your path. A shorter, straighter path scores closer
to 0.

**Runtime.** Wall-clock time for `buildPath` on each track, printed in
milliseconds. Track 3 has 500 points - this is where an inefficient
approach (e.g. rescanning every remaining point from scratch, over and
over) starts to show.

## The three benchmark tracks

| Track   | Points | Car start (x, y) | Car heading            |
|---------|--------|-------------------|-------------------------|
| Track 1 | 15     | (0, 0)            | 0 rad (0 deg)           |
| Track 2 | 50     | (-5, -5)          | pi/2 rad (90 deg)       |
| Track 3 | 500    | (-7, 10)          | -1 rad (~-57.3 deg)     |

Points on every track are scattered randomly all the way around the car -
not just in front of it - so part of the problem is figuring out which
points are even usable before you start chaining them together.

## Reading the plots

Every run of `./run_tests` writes an SVG file per track (`track_1_plot.svg`,
`track_2_plot.svg`, `track_3_plot.svg`) - open them in a browser. Grey dots
are the full candidate set, the dark marker is the car (with a short line
showing its heading), and the red line is the path your code produced. The
view auto-scales to the spread of that track's points, so a tight cluster
of 15 points and a wide spread of 500 will each fill the frame.
