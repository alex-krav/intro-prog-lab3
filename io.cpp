#include "io.h"
#include <ios>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>
#include <iterator>

using namespace std;

void draw_grid(const Grid& grid, int field_width, vector<Point>* path)
{
    cout << string(field_width, ' ');
    for (int x = 0; x != grid.width; ++x) {
        cout << left << setw(field_width);
        cout << x;
    }
    cout << '\n';

    for (int y = 0; y != grid.height; ++y) {
        cout << left << setw(field_width);
        cout << y;
        for (int x = 0; x != grid.width; ++x) {
            Point id{ x, y };
            cout << left << setw(field_width);
            if (grid.walls.find(id) != grid.walls.end()) {
                cout << 'X';
            }
            else if (path != nullptr) {
                vector<Point>::iterator iter = find(path->begin(), path->end(), id);
                if (iter != path->end()) {
                    int index = distance(path->begin(), iter);
                    cout << hex << index;
                }
                else {
                    cout << ' ';
                }
            }
            else {
                cout << ' ';
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

void add_point(Grid& grid, int x, int y) {
    grid.walls.insert(Point{ x, y });
}

Grid build_grid() {
    Grid grid(30, 15);
    add_rect(grid, 3, 3, 5, 12);
    add_rect(grid, 13, 4, 15, 15);
    add_rect(grid, 21, 0, 23, 7);
    add_rect(grid, 23, 5, 26, 7);
    return grid;
}

Grid read_grid_from_file(string in, int field_width) {
    ifstream input(in);

    if (!input.is_open())
        throw runtime_error("Unable to open input file: " + in);
    else
    {
        Grid grid;
        int y = 0;
        bool first_line = true;
        string line;

        while (getline(input, line))
        {
            int x = 0;
            bool empty_line = true;
            stringstream ss(line);

            while (ss.good())
            {
                string field(field_width, '\0');
                ss.read(&field[0], field_width);
                if (field.find_first_not_of(' ') != std::string::npos 
                    && field.find_first_not_of('\0') != std::string::npos) {
                   add_point(grid, x, y);
                   if (first_line) ++x;
                   empty_line = false;
                }
                if (!first_line) ++x;
            }
            if (first_line) {
                grid.width = x;
                first_line = false;
            }
            if (!empty_line) ++y;
        }
        grid.height = y;
        input.close();
        return grid;
    }   
}

void save_grid_to_file(string out, const Grid& grid, int field_width, vector<Point>* path) {
    ofstream output(out, ios_base::trunc);

    if (output.is_open())
    {
        for(int y = 0; y != grid.height; ++y) {
            for (int x = 0; x != grid.width; ++x) {
                Point id{ x, y };
                output << left << setw(field_width);
                if (grid.walls.find(id) != grid.walls.end()) {
                    output << 'X';
                }
                else if (path != nullptr) {
                    vector<Point>::iterator iter = find(path->begin(), path->end(), id);
                    if (iter != path->end()) {
                        int index = distance(path->begin(), iter);
                        output << hex << index;
                    }
                    else {
                        output << ' ';
                    }
                }
                else {
                    output << ' ';
                }
            }
            output << '\n';
        }

        output.close();
    }
    else cerr << "Unable to open output file: " << out << endl;
}
