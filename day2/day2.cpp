#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

// Check if a report is safe without removing any levels
bool is_safe_report(const vector<int>& levels) {
    if (levels.size() < 2) {
        return true;
    }

    bool is_increasing = levels[1] > levels[0];
    for (int i = 1; i < levels.size(); i++) {
        int diff = levels[i] - levels[i - 1];
        if (!is_increasing) {
            diff *= -1;
        }

        if (!(diff >= 1 && diff <= 3)) {
            return false;
        }
    }
    return true;
}

// Check if a report is safe with the Problem Dampener (removing one level)
bool is_safe_with_dampener(const vector<int>& levels) {
    // First check if it's already safe without removing any level
    if (is_safe_report(levels)) {
        return true;
    }

    // Try removing each level one by one
    for (int i = 0; i < levels.size(); i++) {
        vector<int> modified_levels;
        for (int j = 0; j < levels.size(); j++) {
            if (j != i) {
                modified_levels.push_back(levels[j]);
            }
        }
        if (is_safe_report(modified_levels)) {
            return true;
        }
    }

    return false;
}

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

        if (is_safe_report(levels)) {
            safe_count++;
        }
    }

    cout << safe_count << endl;
}

void solve_part2() {
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

        if (is_safe_with_dampener(levels)) {
            safe_count++;
        }
    }

    cout << safe_count << endl;
}

int main() {
    // solve_part1();
    solve_part2();
    return 0;
}