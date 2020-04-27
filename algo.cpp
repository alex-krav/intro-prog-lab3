#include "algo.h"
#include "data_structures.h"
#include <algorithm>
#include <cmath>

using namespace std;

void search(Grid graph, Point start, Point goal, unordered_map<Point, Point>& came_from, int (*heuristic_func)(Point a, Point b))
{
    int comp = 0, steps = 0;
    PriorityQueue<Point, int> frontier = PriorityQueue<Point, int>(less_comp<int>);
    frontier.push(start, 0);

    came_from[start] = start;
    unordered_map<Point, int> cost_so_far;
    cost_so_far[start] = 0;

    while (!frontier.empty()) {
        Point current = frontier.get();

        if (current == goal) {
            break;
        }

        for (Point next : graph.neighbors(current)) {
            int new_cost = cost_so_far[current] + graph.cost(current, next);
            if (cost_so_far.find(next) == cost_so_far.end()
                || new_cost < cost_so_far[next]) {
                cost_so_far[next] = new_cost;
                int heuristic_cost = (nullptr != heuristic_func) ? heuristic_func(next, goal) : 0;
                int priority = new_cost + heuristic_cost;
                frontier.push(next, priority);
                came_from[next] = current;
                ++steps;
            }
            ++comp;
        }
    }
    cout << dec << "comparisons: " << comp << ", steps: " << steps << endl;
}

int heuristic(Point a, Point b) {
    return abs(a.x - b.x) + abs(a.y - b.y);
}

vector<Point> reconstruct_path(Point start, Point goal, unordered_map<Point, Point> came_from)
{
    vector<Point> path;
    Point current = goal;
    while (current != start) {
        path.push_back(current);
        current = came_from[current];
    }
    path.push_back(start);
    reverse(path.begin(), path.end());
    return path;
}
