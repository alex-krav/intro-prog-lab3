#ifndef ALGO_H
#define ALGO_H

#include "maze.h"

void search(Grid graph, Point start, Point goal, unordered_map<Point, Point>& came_from, int(*heuristic_func)(Point a, Point b) = nullptr);
int heuristic(Point a, Point b);
vector<Point> reconstruct_path(Point start, Point goal, unordered_map<Point, Point> came_from);

#endif;