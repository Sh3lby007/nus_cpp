#include <iostream>
#include <string>
#include <vector>
using namespace std;

bool isSafe(const vector<int>& queens, int row, int col, int N) {
  // Check if placing a queen at (row, col) is safe
  // queens[i] = j means there's a queen at (i, j)
  // queens[i] = -1 means no queen in row i yet

  for (int r = 0; r < N; r++) {
    if (queens[r] == -1) continue;  // No queen in this row

    int c = queens[r];

    // Check if (r, c) attacks (row, col)
    if (r == row || c == col ||                // Same row or column
        r - c == row - col ||                  // Same diagonal
        r + c == row + col) {                  // Same anti-diagonal
      return false;
    }
  }

  return true;
}

bool solve(vector<int>& queens, const vector<bool>& hasQueen, int currentRow,
           int N) {
  // Base case: all rows processed
  if (currentRow == N) {
    // Check if we have N queens
    int count = 0;
    for (int i = 0; i < N; i++) {
      if (queens[i] != -1) count++;
    }
    return count == N;
  }

  // If this row already has a queen, move to next row
  if (hasQueen[currentRow]) {
    return solve(queens, hasQueen, currentRow + 1, N);
  }

  // Try placing a queen in each column of current row
  for (int col = 0; col < N; col++) {
    if (isSafe(queens, currentRow, col, N)) {
      // Place queen
      queens[currentRow] = col;

      // Recursively try to place remaining queens
      if (solve(queens, hasQueen, currentRow + 1, N)) {
        return true;
      }

      // Backtrack
      queens[currentRow] = -1;
    }
  }

  return false;
}

void solution() {
  int N, M;
  cin >> N >> M;

  vector<int> queens(N, -1);      // queens[i] = column of queen in row i, -1 if none
  vector<bool> hasQueen(N, false);  // hasQueen[i] = true if row i has a queen

  // Read the board
  for (int i = 0; i < N; i++) {
    string row;
    cin >> row;
    for (int j = 0; j < N; j++) {
      if (row[j] == 'Q') {
        queens[i] = j;
        hasQueen[i] = true;
      }
    }
  }

  // Try to place remaining queens using backtracking
  if (solve(queens, hasQueen, 0, N)) {
    cout << "true" << endl;
  } else {
    cout << "false" << endl;
  }
}

int main() {
  solution();
  return 0;
}
