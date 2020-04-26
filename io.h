#ifndef IO_H
#define IO_H

#include "maze.h"

using namespace std;

void draw_grid(const Grid& grid, int field_width, vector<Point>* path = nullptr, string filename = "");
void add_rect(Grid& grid, int x1, int y1, int x2, int y2);
Grid build_grid();

Grid read_grid_from_file(string in, int field_width);
void draw_grid(basic_iostream<char>::basic_ostream& out, const Grid& grid, int field_width, vector<Point>* path = nullptr, string filename = "");
Point get_xy_coord(Grid grid, string mes);

#endif;