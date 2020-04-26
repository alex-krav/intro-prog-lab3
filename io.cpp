#include "io.h"
#include <ios>
#include <iomanip>
#include <string>

using namespace std;

void draw_grid(const Grid& graph, vector<Point>* path)
{
    int field_width = 3;
    for (int y = 0; y != graph.height; ++y) {
        for (int x = 0; x != graph.width; ++x) {
            Point id{ x, y };
            cout << left << setw(field_width);
            if (graph.walls.find(id) != graph.walls.end()) {
                cout << string(field_width, '#');
            }
            else if (path != nullptr && find(path->begin(), path->end(), id) != path->end()) {
                cout << '@';
            }
            else {
                cout << '.';
            }
        }
        cout << '\n';
    }
}

void add_rect(Grid& grid, int x1, int y1, int x2, int y2) {
    for (int x = x1; x < x2; ++x) {
        for (int y = y1; y < y2; ++y) {
            grid.walls.insert(Point{ x, y });
        }
    }
}

Grid build_grid() {
    Grid grid(30, 15);
    add_rect(grid, 3, 3, 5, 12);
    add_rect(grid, 13, 4, 15, 15);
    add_rect(grid, 21, 0, 23, 7);
    add_rect(grid, 23, 5, 26, 7);
    return grid;
}
