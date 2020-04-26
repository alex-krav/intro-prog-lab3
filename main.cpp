#include "algo.h"
#include "io.h"

using namespace std;

int main() {
    Grid grid = build_grid();
    Point start{ 1, 4 };
    Point goal{ 8, 5 };
    unordered_map<Point, Point> came_from;
    //search(grid, start, goal, came_from, heuristic);
    search(grid, start, goal, came_from);
    vector<Point> path = reconstruct_path(start, goal, came_from);
    draw_grid(grid, &path);

    return 0;
}