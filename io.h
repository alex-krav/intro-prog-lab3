#ifndef IO_H
#define IO_H

#include "maze.h"

using namespace std;

void draw_grid(const Grid& graph, vector<Point>* path = nullptr);
void add_rect(Grid& grid, int x1, int y1, int x2, int y2);
Grid build_grid();

#endif;