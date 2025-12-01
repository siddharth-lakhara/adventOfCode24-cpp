#include <iostream>
#include <vector>
#include <string>
using namespace std;

enum Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

struct Coordinates {
    int x;
    int y;
};

pair<vector<string>, Coordinates> read_map() {
    Coordinates c;
    vector<string> map;

    int x = 0;
    string line;
    while (getline(cin, line)) {
        map.push_back(line);

        int foundPos = line.find('^');
        if (foundPos != string::npos) {
            c.x = x;
            c.y = foundPos;
        }

        x++;
    }

    return {map, c};
}

void solve_part1() {
    Direction curr_direction = Direction::UP;
    long unique_steps = 0;

    auto [grid, coords] = read_map();
    const int GRID_H = grid.size();
    const int GRID_W = grid[0].size();
    grid[coords.x][coords.y] = '.';

    while (coords.x >= 0 && coords.x < GRID_W && coords.y >= 0 && coords.y < GRID_H) {
        if (grid[coords.x][coords.y] == '.') {
            grid[coords.x][coords.y] = 'X';
            unique_steps++;
        }

        if (curr_direction == Direction::UP) {
            if (coords.x>0 && grid[coords.x-1][coords.y] == '#') {
                curr_direction = Direction::RIGHT;
            } else {
                coords.x--;
            }
        } else if (curr_direction == Direction::DOWN) {
            if (coords.x < GRID_H-1 && grid[coords.x+1][coords.y] == '#') {
                curr_direction = Direction::LEFT;
            } else {
                coords.x++;
            }
        } else if (curr_direction == Direction::LEFT) {
            if (coords.y > 0 && grid[coords.x][coords.y - 1] == '#') {
                curr_direction = Direction::UP;
            } else {
                coords.y--;
            }
        } else {
            if (coords.y < GRID_W-1 && grid[coords.x][coords.y+1] == '#') {
                curr_direction = Direction::DOWN;
            } else {
                coords.y++;
            }
        }
    }

    cout << "Answer: " << unique_steps << endl;
}

void solve_part2() {
}

int main() {
    solve_part1();
    // solve_part2();
    return 0;
}