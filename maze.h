#ifndef MAZE_H
#define MAZE_H

#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <array>
#include <iostream>
#include <functional>
#include <string>

using namespace std;

class Point {
    friend bool operator == (Point a, Point b) {
        return a.x == b.x && a.y == b.y;
    }

    friend bool operator != (Point a, Point b) {
        return !(a == b);
    }

    friend bool operator < (Point a, Point b) {
        return (a.x < b.x) && (a.y < b.y);
    }

    friend basic_iostream<char>::basic_ostream& operator<<(basic_iostream<char>::basic_ostream& out, const Point& point) {
        out << '(' << point.x << ',' << point.y << ')';
        return out;
    }

public:
    int x, y;
};

namespace std {
    template <> struct hash<Point> {
        size_t operator()(const Point& id) const noexcept {
            string s = to_string(id.x) + ";" + to_string(id.y);
            return hash<string>()(s);
        }
    };
}

class Grid {
    static constexpr array<Point, 4> DIRS =
        { Point{1, 0}, Point{0, -1}, Point{-1, 0}, Point{0, 1} };

public:
    int width, height;
    unordered_set<Point> walls;

    Grid() {}

    Grid(int width_, int height_):
        width(width_), height(height_) {}

    bool in_bounds(Point id) const {
        return 0 <= id.x && id.x < width
            && 0 <= id.y && id.y < height;
    }

    bool passable(Point id) const {
        return walls.find(id) == walls.end();
    }

    vector<Point> neighbors(Point id) const {
        vector<Point> results;

        for (Point dir : DIRS) {
            Point next{ id.x + dir.x, id.y + dir.y };
            if (in_bounds(next) && passable(next)) {
                results.push_back(next);
            }
        }

        return results;
    }

    int cost(Point from_node, Point to_node) const {
        return 1;
    }
};

#endif 