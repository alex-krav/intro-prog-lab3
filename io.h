#ifndef IO_H
#define IO_H

#include "maze.h"

using namespace std;

void draw_grid(const Grid& graph, int field_width, vector<Point>* path = nullptr);
void add_rect(Grid& grid, int x1, int y1, int x2, int y2);
Grid build_grid();

Grid read_grid_from_file(string in, int field_width);
void save_grid_to_file(string out, const Grid& graph, int field_width, vector<Point>* path = nullptr);

#endif;