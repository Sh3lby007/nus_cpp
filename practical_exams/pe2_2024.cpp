#include <stdio.h>

#include <iostream>
#include <set>
#include <string>
#include <vector>

using namespace std;

struct Pipe {
  bool up = false;
  bool down = false;
  bool left = false;
  bool right = false;
};

bool empty(Pipe p) { return not(p.up or p.down or p.left or p.right); }

struct Point {
  int row, col;
  bool operator<(const Point &other) const {
    return row < other.row or (row == other.row and col < other.col);
  }
};

vector<vector<Pipe>> convert(vector<string> rep) {
  vector<vector<Pipe>> b;
  for (string s : rep) {
    b.push_back(vector<Pipe>());
    vector<Pipe> &v = b.back();
    for (char c : s) {
      Pipe p;
      if (c == 'L' or c == 'J' or c == 'I' or c == 'k' or c == '4' or
          c == '^' or c == '+')
        p.up = true;
      if (c == 'r' or c == '7' or c == 'I' or c == 'k' or c == '4' or
          c == 'T' or c == '+')
        p.down = true;
      if (c == 'L' or c == 'r' or c == '-' or c == 'k' or c == '^' or
          c == 'T' or c == '+')
        p.right = true;
      if (c == '7' or c == 'J' or c == '-' or c == '4' or c == '^' or
          c == 'T' or c == '+')
        p.left = true;
      v.push_back(p);
    }
  }
  return b;
}

Point one_spill(vector<vector<Pipe>> grid, Point p) {
  Pipe pipe = grid[p.row][p.col];

  while (!empty(pipe)) {
    printf("%d, %d, %d\n", p.row, p.col, empty(pipe));
    if (pipe.up) {
      p.row -= 1;
      grid[p.row][p.col].down = false;
    } else if (pipe.down) {
      p.row += 1;
      grid[p.row][p.col].up = false;
    } else if (pipe.right) {
      p.col += 1;
      grid[p.row][p.col].left = false;
    } else if (pipe.left) {
      p.col -= 1;
      grid[p.row][p.col].right = false;
    } else
      p.row += 1;
    pipe = grid[p.row][p.col];
  }
  return p;
}

void spill(vector<vector<Pipe>> &grid, int row, int col, set<Point> &pts,
           set<Point> &visited) {
  Pipe p = grid[row][col];
  if (empty(p)) {
    pts.insert({row, col});
    return;
  }
  if (visited.count({row, col})) {
    return;
  }
  visited.insert({row, col});
  if (p.up) spill(grid, row - 1, col, pts, visited);
  if (p.down) spill(grid, row + 1, col, pts, visited);
  if (p.right) spill(grid, row, col + 1, pts, visited);
  if (p.left) spill(grid, row, col - 1, pts, visited);
}

set<Point> all_spills(vector<vector<Pipe>> grid, Point p) {
  set<Point> points, visited;
  spill(grid, 0, 0, points, visited);
  return points;
}

int main() {
  vector<vector<Pipe>> board =
      convert({"r--T--7", "k  +  4", "I  ^  I", "L-   -J"});

  vector<vector<Pipe>> loops = convert({"r-T-7", "kT+-4", "I k I", "L-^-J"});

  vector<vector<Pipe>> grid = {
      {{0, 1, 0, 1}, {0, 0, 1, 1}, {0, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}},
      {{1, 1, 0, 0}, {0, 0, 0, 0}, {1, 1, 0, 1}, {0, 1, 1, 0}, {0, 0, 0, 0}},
      {{1, 0, 0, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}},
      {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}};

  // Test for part A
  Point p = one_spill(grid, {0, 0});
  printf("Part A: (%d, %d)\n", p.row, p.col);

  // Add deadend at (1, 1)
  grid[1][1].right = true;
  grid[1][2].left = true;

  printf("Part B:");
  set<Point> s = all_spills(grid, {0, 0});
  for (Point p : s) {
    printf(" (%d, %d)", p.row, p.col);
  }

  // Uncomment to test with loops
  // Add loop
  grid[2][1].left = grid[2][1].right = true;
  grid[2][2].left = grid[2][2].up = true;

  printf("\nPart C:");
  set<Point> s2 = all_spills(grid, {0, 0});
  for (Point p : s2) {
    printf(" (%d, %d)", p.row, p.col);
  }
}