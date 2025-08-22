#include <iostream>
#include <regex>
#include <string>
using namespace std;

const regex PATTERN("mul\\((\\d+),(\\d+)\\)");
const regex PATTERN_2("mul\\((\\d+),(\\d+)\\)|don't\\(\\)|do\\(\\)");

void solve_part1() {
    string memory;
    string line;
    while (getline(cin, line)) {
        memory += line;
    }

    long long sum = 0L;
    auto match_begin = sregex_iterator(memory.begin(), memory.end(), PATTERN);
    auto match_end = sregex_iterator();
    
    for (sregex_iterator it = match_begin; it != match_end; it++) {
        smatch match = *it;
        
        int first_num = std::stoi(match[1].str());
        int second_num = std::stoi(match[2].str());
        
        sum += (long long) first_num * (long long) second_num;

        // cout << "Match: mul(" << first_num << "," << second_num << ") -> " << first_num * second_num << "\n";
    }
    cout << "Sum: " << sum << endl;
}

void solve_part2() {
    string memory;
    string line;
    while (getline(cin, line)) {
        memory += line;
    }

    long sum = 0;
    auto match_begin = sregex_iterator(memory.begin(), memory.end(), PATTERN_2);
    auto match_end = sregex_iterator();
    bool is_parsing_enabled = true;
    
    for (sregex_iterator it = match_begin; it != match_end; it++) {
        smatch match = *it;
        string match_substr = match.str().substr(0,3);
        // cout << "Match found: " << match.str() << "\n";

        if (match_substr == "mul") {
            if (!is_parsing_enabled) {
                continue;
            }
            int first_num = std::stoi(match[1].str());
            int second_num = std::stoi(match[2].str());

            sum += (long)first_num * second_num;

            // cout << "Match: mul(" << first_num << "," << second_num << ") -> " << first_num * second_num << "\n";
        }
        else if (match_substr == "don") {
            is_parsing_enabled = false;
        }
        else {
            is_parsing_enabled = true;
        }
    }
    cout << "Sum: " << sum << endl;
}

int main() {
    // solve_part1();
    solve_part2();
    return 0;
}