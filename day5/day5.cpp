#include <iostream>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

unordered_map<int, unordered_set<int>> read_page_order_rules() {
    unordered_map<int, unordered_set<int>> page_order_rules;
    string line;

    while (getline(cin, line)) {
        if (line.empty()) {
            break;
        }

        stringstream ss(line);
        string buf;
        
        getline(ss, buf, '|');
        int page1 = atoi(buf.c_str());

        getline(ss, buf, '|');
        int page2 = atoi(buf.c_str());

        if (page_order_rules.find(page2) == page_order_rules.end()) {
            page_order_rules[page2] = unordered_set<int>();
        }
        page_order_rules[page2].insert(page1);
    }

    return page_order_rules;
}

vector<vector<int>> read_page_orders() {
    vector<vector<int>> page_orders;
    string line;
    while (getline(cin, line)) {
        stringstream ss(line);
        string buf;
        vector<int> page_order;
        while (getline(ss, buf, ',')) {
            page_order.push_back(atoi(buf.c_str()));
        }
        page_orders.push_back(page_order);
    }
    return page_orders;
}

bool is_correct_page_order(vector<int>& page_order, unordered_map<int, unordered_set<int>>& page_order_rules) {
    unordered_set<int> unallowed_nums;
    for (int page: page_order) {
        if (unallowed_nums.find(page) != unallowed_nums.end()) {
            return false;
        }
        
        if (page_order_rules.find(page) != page_order_rules.end()) {
            for (int rule_page : page_order_rules[page]) {
                unallowed_nums.insert(rule_page);
            }
        }

    }

    return true;
}

void solve_part1() {
    unordered_map<int, unordered_set<int>> page_order_rules = read_page_order_rules();
    vector<vector<int>> page_orders = read_page_orders();

    long sum_mid_page_nums = 0;
    for (vector<int> page_order : page_orders) {
        if (is_correct_page_order(page_order, page_order_rules)) {
            sum_mid_page_nums += page_order.at(page_order.size()/2);
        }
    }

    cout << sum_mid_page_nums << "\n";
}

void solve_part2() {
    
}

int main()
{
    solve_part1();
    // solve_part2();
    return 0;
}