#include "algo.h"
#include "io.h"

using namespace std;

int main(int argc, char* argv[])
{
    if (argc < 3) {
        cerr << "Usage: " << argv[0] << " INPUT_FILE, OUTPUT_FILE" << endl;
        return 1;
    }
    string in = argv[1], out = argv[2];

    cout << "reading file: " << in << endl;
    Grid grid = read_grid_from_file(in, 2);
    int fw = grid.width > 10 ? 3 : 2;
    draw_grid(grid, fw, nullptr);

    Point start = get_xy_coord(grid, "\nEnter (x,y) coordinates of start <,> separated: ");
    Point goal = get_xy_coord(grid, "\nEnter (x,y) coordinates of goal <,> separated: ");

    cout << "\nDijkstra search:" << endl;
    unordered_map<Point, Point> came_from;
    search(grid, start, goal, came_from);
    vector<Point> path = reconstruct_path(start, goal, came_from);
    draw_grid(grid, fw, &path);

    cout << "\nA* search:" << endl;
    came_from.clear();
    search(grid, start, goal, came_from, heuristic);
    path = reconstruct_path(start, goal, came_from);
    draw_grid(grid, fw, &path);

    cout << "\nsaving result to: " << out << endl;
    draw_grid(grid, fw, &path, out);

    return 0;
}