#include "algo.h"
#include "io.h"

using namespace std;

int main() {
    string in = "input/input1.txt", out = "output1.txt";
    Grid grid = read_grid_from_file(in, 2);
    int fw = grid.width > 10 ? 3 : 2;
    draw_grid(grid, fw, nullptr);
    cout << endl;

    Point start{ 1, 5 };
    Point goal{ 6, 1 };
    unordered_map<Point, Point> came_from;

    search(grid, start, goal, came_from, heuristic);
    //search(grid, start, goal, came_from);
    vector<Point> path = reconstruct_path(start, goal, came_from);

    draw_grid(grid, fw, &path);
    draw_grid(grid, fw, &path, out);

    return 0;
}