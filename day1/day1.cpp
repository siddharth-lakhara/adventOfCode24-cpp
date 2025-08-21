#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;

void solve_part1() {
    vector<int> list1, list2;
    
    int num1, num2;
    while (cin >> num1 >> num2) {
        list1.push_back(num1);
        list2.push_back(num2);
    }
    
    sort(list1.begin(), list1.end());
    sort(list2.begin(), list2.end());

    long sum=0L;
    for (int idx=0; idx<list1.size(); idx++) {
        sum += abs(list1.at(idx) - list2.at(idx));
    }

    cout << "Answer: " << sum << "\n";
}

void solve_part2()
{
    vector<int> list1;
    unordered_map<int, int> counter;

    int num1, num2;
    while (cin >> num1 >> num2)
    {
        list1.push_back(num1);
        
        if (counter.find(num2) == counter.end()) {
            counter.insert({ num2, 0 });
        }
        counter[num2] += 1;
    }

    long score = 0L;
    for (int idx = 0; idx < list1.size(); idx++)
    {
        int num = list1.at(idx);
        int multiplier = counter.find(num) != counter.end() ? counter[num] : 0 ;
        score += (num*multiplier);
    }

    cout << "Answer: " << score << "\n";
}

int main() {
    // solve_part1();
    solve_part2();
    return 0;
}