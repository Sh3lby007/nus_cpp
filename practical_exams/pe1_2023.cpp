#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

// returns the smaller of a or b
int min(int a, int b) {
  return a < b ? a : b;
}

int jump(int d_o, int d_t) {
  if (d_t == 0)
    return 0;
  int j1 = d_o / 2 + 1;
  int j2 = d_t / 2 + 1;
  if (j1 > d_t)
    return 1 + jump(d_o + j2, d_t - j2);
  else
    return 1 + min(jump(d_o + j1, d_t - j1), jump(d_o + j2, d_t - j2));
}

// Q2
void print_grid(vector<vector<int>> grid) {
  for (vector<int> row : grid) {
    for (int col : row)
      cout << setw(2) << col << " ";
    cout << endl;
  }
}

void outline(vector<vector<int>>& grid, int key, int set) {
  for (int row = 0; row < grid.size(); row++) {
    for (int col = 0; col < grid[row].size(); col++) {
      if (grid[row][col] == key) {
        if (grid[row - 1][col] == 0)
          grid[row - 1][col] = set;
        if (grid[row + 1][col] == 0)
          grid[row + 1][col] = set;
        if (grid[row][col - 1] == 0)
          grid[row][col - 1] = set;
        if (grid[row][col + 1] == 0)
          grid[row][col + 1] = set;
      }
    }
  }
}

struct Point {
  int row, col;
};

int shortest(vector<vector<int>> grid, Point start, Point end) {
  grid[start.row][start.col] = 1;
  int i;
  for (i = 1; grid[end.row][end.col] == 0; i++) {
    outline(grid, i, i + 1);
  }
  return i;
}

int main() {
  for (int i = 1; i <= 20; i++)
    cout << "jump(0, " << i << ") >> " << jump(0, i) << endl;

  // Q2

  vector<vector<int>> g = {
      {0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 5, 0, 0, 0, 6, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 5, 5, 5, 5, 5, 0, 0},
      {0, 0, 5, 1, 1, 1, 5, 0, 0}, {0, 0, 0, 5, 5, 5, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0}};
  outline(g, 5, 8);
  print_grid(g);
  cout << endl;

  vector<vector<int>> maze = {
      {-1, -1, -1, -1, -1, -1, -1, -1}, {-1, 0, 0, 0, 0, 0, 0, -1},
      {-1, 0, 0, 0, -1, -1, 0, -1},     {-1, 0, -1, 0, -1, 0, 0, -1},
      {-1, 0, -1, 0, 0, 0, 0, -1},      {-1, 0, 0, -1, -1, 0, 0, -1},
      {-1, 0, 0, 0, 0, -1, 0, -1},      {-1, 0, 0, -1, 0, 0, 0, -1},
      {-1, -1, -1, -1, -1, -1, -1, -1}};

  cout << shortest(maze, {7, 1}, {4, 4}) << endl;
  cout << shortest(maze, {2, 1}, {7, 6}) << endl;
  cout << shortest(maze, {1, 6}, {4, 3}) << endl;
  return 0;
}