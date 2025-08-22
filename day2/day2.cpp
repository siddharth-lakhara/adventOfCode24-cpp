#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <sstream>
using namespace std;

void solve_part1() {
    string line;
    int safe_count = 0;

    string report;
    while (getline(cin, report)) {
        stringstream ss(report);

        int level;
        vector<int> levels;
        while (ss >> level) {
            levels.push_back(level);
        }

        if (levels.size() < 2) {
            safe_count++;
            continue;
        }

        bool is_safe = true;
        bool is_increasing = levels[1] > levels[0];
        for (int idx=1; idx<levels.size(); idx++) {
            int diff = levels[idx] - levels[idx-1];
            if (!is_increasing) {
                diff *= -1;
            }

            if (!(diff >= 1 && diff <= 3)) {
                is_safe = false;
                break;
            }
        }
        if (is_safe) {
            safe_count++;
        }
    }
    
    cout << safe_count << endl;
}

void solve_part2() {
}

int main() {
    solve_part1();
    // solve_part2();
    return 0;
}