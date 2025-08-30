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

long count_unique_steps(vector<string>& grid, Coordinates coords) {
    long unique_steps = 0;

    while ()
    return unique_steps;
}

void solve_part1() {
    Direction curr_direction = Direction::UP;
    auto [map, coords] = read_map();

    count_unique_steps(map, coords)
}

void solve_part2() {
}

int main() {
    solve_part1();
    // solve_part2();
    return 0;
}