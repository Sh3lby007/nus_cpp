#include <cmath>
#include <cstdio>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

struct Point {
  int row;
  int col;
};

/*
Return num of days to kill the colony
Base case
*/
int days_to_kill(int pop, int kill, double grow) {
  if (pop <= 0) {
    return 0;
  }
  return 1 + days_to_kill((pop - kill) * (1 + grow), kill, grow);
}

vector<Point> extract_block(vector<vector<bool>> board, int n) {
  vector<Point> result;
  for (int i = 0; i < board.size(); i++) {
    for (int j = 0; j < board[0].size(); j++) {
      if (board[i][j] == n) {
        Point p = {i, j};
        result.push_back(p);
      }
    }
  }
  return result;
}

vector<Point> extract_block(vector<vector<bool>> board, int n) {
  vector<Point> p;
  for (int i = 0; i < board.size(); i++) {
    for (int j = 0; j < board[i].size(); j++) {
      if (board[i][j] == n) {
        p.push_back({i, j});
      }
    }
  }
  return p;
}
// use hypot {2,4}, {2,5}, {2,6}, {3,5}
Point get_centre(vector<Point> blk) {
  double minAvgDist = -1;  // Set to -1 as a flag indicating "not set yet"
  Point center;

  // For each point in the block
  for (int i = 0; i < blk.size(); i++) {
    double totalDist = 0;

    // Calculate distance to all other points
    for (int j = 0; j < blk.size(); j++) {
      if (i != j) {  // Skip comparing a point to itself
        // Calculate Euclidean distance using hypot
        double distance =
            hypot(blk[i].row - blk[j].row, blk[i].col - blk[j].col);
        totalDist += distance;
      }
    }

    // Calculate average (divide by number of other points)
    double avgDist = totalDist / (blk.size() - 1);

    // Update minimum if this is the first point or if we found a smaller
    // average
    if (minAvgDist == -1 || avgDist < minAvgDist) {
      minAvgDist = avgDist;
      center = blk[i];
    }
  }

  return center;
}

vector<Point> get_move(vector<Point> o, vector<Point> m) {
  vector<Point> v;
  for (int i = 0; i < o.size(); i++) {
    v.push_back({m[i].row - o[i].row, m[i].col - o[i].col});
  }
  return v;
}

/*
3D
To order a Point, we can first use the natural ordering of
row, followed by col. if row is the same. Without ordering,
the entire vector has to be searched for each point, which
results in O(n2) where n is the size of the block. With
ordering, only the same index of both vectors need to be
compared, so it only needs O(n).
*/