#include <cmath>
#include <cstdio>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

// 1A
int boo(int n) {
  int a = 0;
  while (n > 0) {
    int i = 0;
    while (i <= n % 10) {
      a += 1;
      i += 1;
    }
    n /= 10;
  }
  return a;
}
// 1B
int foo(int n, int m) {
  int s = 0;
  while (n > 0) {
    s += 1;
    if (s == m) s = 0;
    n = 1;
  }
  return s;
}

// 1C
void bar(int n) {
  if (n == 1) return;
  int i = 2;
  while (foo(n, i)) i += 1;
  cout << i << " ";
  bar(n / i);
}

// 2A
int infected(double r0, int day) {
  if (day == 0)
    return 1;
  else
    return ceil((1 + r0) * infected(r0, day - 1));
}

// Question 3
struct Point {
  int row;
  int col;
};
// 3A
Point new_point(Point p, char dir) {
  switch (dir) {
    case 'u':
      p.row -= 1;
      break;
    case 'd':
      p.row += 1;
      break;
    case 'l':
      p.col -= 1;
      break;
    case 'r':
      p.col += 1;
      break;
  }
  return p;
}
vector<vector<int>> puzzle = {
    {4, 1, 7, 2}, {8, 10, 5, 3}, {9, 6, 0, 14}, {12, 13, 15, 11}};
// 3B
void move(vector<vector<int>>& puzzle, char dir) {
  int temp;
  for (int i = 0; i < puzzle.size(); i++) {
    for (int j = 0; j < puzzle[i].size(); j++) {
      if (puzzle[i][j] == 0) {
        Point p = new_point({i, j}, dir);
        puzzle[i][j] = puzzle[p.row][p.col];
        puzzle[p.row][p.col] = 0;
        return;
      }
    }
  }
}

// 3C
void move(vector<Point>& puzzle, char dir) {
  Point p = new_point(puzzle[0], dir);
  // find the replacement number
  for (int i = 0; i < puzzle.size(); i++) {
    if (puzzle[i].row == p.row and puzzle[i].col == p.col) {
      puzzle[i] = puzzle[0];
      puzzle[0] = p;
      return;
    }
  }
}

/*
3D
Both representative takes O(n×m) to make a move for a puzzle of n×m size as both
need a linear search through all the tiles to find either the blank tile or the
target tile. For 3C representation, we know where the blank tile is ( puzzle[0]
) but we needed to search for the target tile. For 3B representation, we had to
search for the blank tile, then the target tile is just next to it. If both
representations are used at the same time, then we know where the blank tile is
from one representation, and then locate the target tile from the other, all in
O(1) time.
In other words, if we can save the location of the blank tile somewhere, then
the first representation only needs O(1) time as it can directly access the
blank tile and swap with the target tile.
*/

int main() {
  cout << infected(1, 2) << endl;
  return 0;
}
