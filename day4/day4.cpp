#include <iostream>
#include <vector>
using namespace std;

vector<vector<char>> grid;
int grid_h;
int grid_w;
const string SEARCH_TERM = "XMAS";

void read_grid()
{
    string line;
    while (getline(cin, line))
    {
        vector<char> line_vector(line.begin(), line.end());
        grid.push_back(line_vector);
    }
    grid_w = grid.at(0).size();
    grid_h = grid.size();
}

bool search_up(int grid_x, int grid_y, int search_idx)
{
    if (search_idx >= SEARCH_TERM.length())
    {
        return true;
    }
    else if (grid_x < 0)
    {
        return false;
    }
    else if (grid.at(grid_x).at(grid_y) == SEARCH_TERM.at(search_idx))
    {
        return search_up(grid_x - 1, grid_y, search_idx + 1);
    }
    else
    {
        return false;
    }
}

bool search_down(int grid_x, int grid_y, int search_idx)
{
    if (search_idx >= SEARCH_TERM.length())
    {
        return true;
    }
    else if (grid_x >= grid_h)
    {
        return false;
    }
    else if (grid.at(grid_x).at(grid_y) == SEARCH_TERM.at(search_idx))
    {
        return search_down(grid_x + 1, grid_y, search_idx + 1);
    }
    else
    {
        return false;
    }
}

bool search_right(int grid_x, int grid_y, int search_idx)
{
    if (search_idx >= SEARCH_TERM.length())
    {
        return true;
    }
    else if (grid_y >= grid_w)
    {
        return false;
    }
    else if (grid.at(grid_x).at(grid_y) == SEARCH_TERM.at(search_idx))
    {
        return search_right(grid_x, grid_y + 1, search_idx + 1);
    }
    else
    {
        return false;
    }
}

bool search_left(int grid_x, int grid_y, int search_idx)
{
    if (search_idx >= SEARCH_TERM.length())
    {
        return true;
    }
    else if (grid_y < 0)
    {
        return false;
    }
    else if (grid.at(grid_x).at(grid_y) == SEARCH_TERM.at(search_idx))
    {
        return search_left(grid_x, grid_y - 1, search_idx + 1);
    }
    else
    {
        return false;
    }
}

bool search_left_up(int grid_x, int grid_y, int search_idx)
{
    if (search_idx >= SEARCH_TERM.length())
    {
        return true;
    }
    else if (grid_x < 0 || grid_y < 0)
    {
        return false;
    }
    else if (grid.at(grid_x).at(grid_y) == SEARCH_TERM.at(search_idx))
    {
        return search_left_up(grid_x - 1, grid_y - 1, search_idx + 1);
    }
    else
    {
        return false;
    }
}

bool search_left_down(int grid_x, int grid_y, int search_idx)
{
    if (search_idx >= SEARCH_TERM.length())
    {
        return true;
    }
    else if (grid_x >= grid_h || grid_y < 0)
    {
        return false;
    }
    else if (grid.at(grid_x).at(grid_y) == SEARCH_TERM.at(search_idx))
    {
        return search_left_down(grid_x + 1, grid_y - 1, search_idx + 1);
    }
    else
    {
        return false;
    }
}

bool search_right_up(int grid_x, int grid_y, int search_idx)
{
    if (search_idx >= SEARCH_TERM.length())
    {
        return true;
    }
    else if (grid_x < 0 || grid_y >= grid_w)
    {
        return false;
    }
    else if (grid.at(grid_x).at(grid_y) == SEARCH_TERM.at(search_idx))
    {
        return search_right_up(grid_x - 1, grid_y + 1, search_idx + 1);
    }
    else
    {
        return false;
    }
}

bool search_right_down(int grid_x, int grid_y, int search_idx)
{
    if (search_idx >= SEARCH_TERM.length())
    {
        return true;
    }
    else if (grid_x >= grid_h || grid_y >= grid_w)
    {
        return false;
    }
    else if (grid.at(grid_x).at(grid_y) == SEARCH_TERM.at(search_idx))
    {
        return search_right_down(grid_x + 1, grid_y + 1, search_idx + 1);
    }
    else
    {
        return false;
    }
}

int initiateXmasSearch(int grid_x, int grid_y)
{
    int count = 0;
    if (search_up(grid_x, grid_y, 0))
    {
        count++;
    }
    if (search_down(grid_x, grid_y, 0))
    {
        count++;
    }
    if (search_right(grid_x, grid_y, 0))
    {
        count++;
    }
    if (search_left(grid_x, grid_y, 0))
    {
        count++;
    }
    if (search_left_up(grid_x, grid_y, 0))
    {
        count++;
    }
    if (search_left_down(grid_x, grid_y, 0))
    {
        count++;
    }
    if (search_right_up(grid_x, grid_y, 0))
    {
        count++;
    }
    if (search_right_down(grid_x, grid_y, 0))
    {
        count++;
    }
    return count;
}

bool check_diagonal_for_mas(string diagonal) {
    return diagonal == "MAS" || diagonal == "SAM";
}

bool search_x_mas (int grid_x, int grid_y) {
    if (grid_x -1 < 0 || grid_x + 1 >= grid_h || grid_y - 1 < 0 || grid_y +1 >= grid_w) {
        return false;
    }

    string diagonal1 = "";
    diagonal1 += grid.at(grid_x - 1).at(grid_y - 1);
    diagonal1 += grid.at(grid_x).at(grid_y);
    diagonal1 += grid.at(grid_x + 1).at(grid_y + 1);
    bool is_diagonal1_mas = check_diagonal_for_mas(diagonal1);
    
    string diagonal2 = "";
    diagonal2 += grid.at(grid_x - 1).at(grid_y + 1);
    diagonal2 += grid.at(grid_x).at(grid_y);
    diagonal2 += grid.at(grid_x + 1).at(grid_y - 1);
    bool is_diagonal2_mas = check_diagonal_for_mas(diagonal2);

    return is_diagonal1_mas && is_diagonal2_mas;
}

void solve_part1()
{
    read_grid();

    int total = 0;
    for (int x = 0; x < grid_h; x++)
    {
        for (int y = 0; y < grid_w; y++)
        {
            if (grid.at(x).at(y) == 'X')
            {
                total += initiateXmasSearch(x, y);
            }
        }
    }

    cout << "Answer: " << total << "\n";
}

void solve_part2()
{
    read_grid();

    int total = 0;
    for (int x = 0; x < grid_h; x++)
    {
        for (int y = 0; y < grid_w; y++)
        {
            if (grid.at(x).at(y) == 'A') {
                if (search_x_mas(x, y))
                    total++;
            }
                
        }
    }

    cout << "Answer: " << total << "\n";
}

int main()
{
    // solve_part1();
    solve_part2();
    return 0;
}