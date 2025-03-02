// Part A//
#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<string> paths(int row, int col) {
  // Your answer here
  vector<string> result;
  if (row == 1 and col == 0) return {"N"};
  if (row == 0 and col == 1) return {"E"};
  if (row > 0)
    for (string p : paths(row - 1, col)) result.push_back("N" + p);
  if (col > 0)
    for (string p : paths(row, col - 1)) result.push_back("E" + p);
  return result;
}

// Part B
vector<string> paths_2(int row, int col) {
  // Your answer here
  vector<string> result;
  if (row == 1 and col == 0) return {"N"};
  if (row == 0 and col == 1) return {"E"};
  if (row == 1 and col == 1) return {"NE", "EN"};
  if (row > 0) {
    for (string p : paths_2(row - 1, col)) result.push_back("N" + p);
    if (col > 0)
      for (string p : paths_2(row - 1, col - 1)) result.push_back("EN" + p);
  }
  return result;
}

// Part C
int points(vector<vector<int>> grid, string path) {
  // Your answer here
  int row = grid.size() - 1;
  int col = 0;
  int result = grid[row][col];
  for (char c : path) {
    if (c == 'N') row -= 1;
    if (c == 'E') col += 1;
    result += grid[row][col];
  }
  return result;
}

// Part D
int max_points(vector<vector<int>> grid) {
  // Your answer here
  int max = 0;
  for (string path : paths(grid.size() - 1, grid[0].size() - 1)) {
    int pts = points(grid, path);
    if (pts > max) max = pts;
  }
  return max;
}