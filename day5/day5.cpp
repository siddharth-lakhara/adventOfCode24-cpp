#include <iostream>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <list>
using namespace std;

// maps page2 -> page1
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
        if (page_order_rules.find(page1) == page_order_rules.end()) {
            page_order_rules[page1] = unordered_set<int>();
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

void explore_curr_page_order(unordered_map<int, unordered_set<int>>& page_order_rules, unordered_set<int>& visited_nodes, int curr_node) {
    if (visited_nodes.find(curr_node) != visited_nodes.end()) {
        // curr_node is already visited
        return;
    }

    visited_nodes.insert(curr_node);
    unordered_set<int> page_orders = page_order_rules.at(curr_node);
    for (int child_page : page_orders) {
        explore_curr_page_order(page_order_rules, visited_nodes, child_page);

        for (auto p : page_order_rules.at(child_page)) {
            page_order_rules[curr_node].insert(p);
        }
    }
}

void explore_all_page_order_rules(unordered_map<int, unordered_set<int>>& page_order_rules, unordered_set<int>& visited_nodes) {
    for (auto it = page_order_rules.begin(); it != page_order_rules.end(); it++) {
        int node = it->first;
        if (visited_nodes.find(node) == visited_nodes.end()) {
            explore_curr_page_order(page_order_rules, visited_nodes, node);
        }
    }
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

bool is_correct_page_order_2(vector<int>& page_order, unordered_map<int, unordered_set<int>>& page_order_rules) {
    for (int i=0; i<page_order.size(); i++) {
        for (int j=0; j<i; j++) {
            int curr_page = page_order[i];
            int check_page = page_order[j];
            if (page_order_rules[check_page].find(curr_page) != page_order_rules[check_page].end()) {
                return false;
            }
        }
    }

    return true;
}

vector<int> fix_page_order(vector<int>& page_order, unordered_map<int, unordered_set<int>>& page_order_rules) {
    // create the subgraph from the bigger graph
    unordered_set<int> pages_in_update(page_order.begin(), page_order.end());

    unordered_map<int, unordered_set<int>> adj_list;
    unordered_map<int, int> in_degree;
    
    for (int page : page_order) {
        adj_list[page] = unordered_set<int>();
        in_degree[page] = 0;
    }
    
    for (int page : page_order) {
        unordered_set<int> dependent_pages = page_order_rules[page];
        for (int dep_page: dependent_pages) {
            if (pages_in_update.find(dep_page) != pages_in_update.end()) {
                adj_list[page].insert(dep_page);
                in_degree[dep_page]++;
            }
        }
    }
    
    // apply kahn's algorithm for topo sort
    list<int> fixed_order;
    list<int> queue;
    
    for (auto& pair : in_degree) {
        if (pair.second == 0) {
            queue.push_back(pair.first);
        }
    }
    
    // Process nodes in topological order
    while (!queue.empty()) {
        int current = queue.front();
        queue.pop_front();
        fixed_order.push_back(current);

        for (int neighbor : adj_list[current]) {
            in_degree[neighbor]--;
            if (in_degree[neighbor] == 0) {
                queue.push_back(neighbor);
            }
        }
    }
    
    return vector<int>(fixed_order.begin(), fixed_order.end());
}

void solve_part1() {
    unordered_map<int, unordered_set<int>> page_order_rules = read_page_order_rules();
    vector<vector<int>> page_orders = read_page_orders();

    long sum_mid_page_nums = 0;
    for (vector<int> page_order : page_orders) {
        if (is_correct_page_order(page_order, page_order_rules)) {
            sum_mid_page_nums += page_order.at(page_order.size() / 2);
        }
    }

    cout << sum_mid_page_nums << "\n";
}

void solve_part2() {
    unordered_map<int, unordered_set<int>> page_order_rules = read_page_order_rules();
    vector<vector<int>> page_orders = read_page_orders();

    long sum_mid_page_nums = 0;
    for (vector<int> page_order : page_orders) {
        if (!is_correct_page_order_2(page_order, page_order_rules)) {
            vector<int> correct_page_order = fix_page_order(page_order, page_order_rules);
            sum_mid_page_nums += correct_page_order.at(correct_page_order.size() / 2);
        }
    }

    cout << sum_mid_page_nums << "\n";
}

int main() {
    // solve_part1();
    solve_part2();
    return 0;
}