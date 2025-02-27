#include <cstdio>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

/*
1A
Time Complexity: O(b)
Returns lowest common multiple (LCM) of a and b.
*/
int boo(int a, int b) {
  int x;
  for (x = a; x % b; x += a) {
  }
  return x;
}

/*
1B
Returns 2n
*/
int foo(int n) {
  int s = 1;
  while (n > 0) {
    for (int i = s; i > 0; i--)
      s += 1;
    n = 1;
  }
  return s;
}

/*
1C
Returns even numbers in the vector v. Filters out the odd numbers.
*/
vector<int> bar(vector<int> v) {
  if (v.empty())
    return {};
  int i = v.back();
  v.pop_back();
  v = bar(v);
  if (i % 2 == 0)
    v.push_back(i);
  return v;
}

/*
Q2
Base case n = 0
loan_left(1000000, 0.005, 6000, 1) = 999000.00
*/
double loan_left(double prin, double intr, double pymt, int n) {
  if (n == 0) {
    return prin;
  } else {
    double amtLeft = prin + (prin * intr) - pymt;
    if (amtLeft < 0) {
      amtLeft = 0;
    }
    return loan_left(amtLeft, intr, pymt, n - 1);
  }
}

// 3A
int get_score(char c, vector<vector<char>> scores) {
  for (int i = 0; i < scores.size(); i++) {
    for (char letter : scores[i]) {
      if (letter == c) {
        return i + 1;
      }
    }
  }
  return -1;
}

/*
came up idea but doesnt fit question limitation
unordered_map<char, int> convert_scores(vector<vector<char>> scores) {
  unordered_map<char, int> scoreMap;  // Use unordered_map for O(1) lookups
  for (int i = 0; i < scores.size(); i++) {
    for (char letter : scores[i]) {
      scoreMap[letter] = i + 1;  // Map letter to its score (i + 1)
    }
  }
  return scoreMap;  // Return the populated map
}
*/

/*
3B
Propose a new representation that works in O(1) time:
Use a vector for the scores and the index is directly addressed by the
character, i.e. ‘A’ will be mapped to index 0, ‘B’ to 1, and so on. To
retrieve, simply minus ‘A’ from the letter to get the index. Implement the
function convert_scores , filling in the return type:
*/
vector<int> convert_scores(vector<vector<char>> scores) {
  vector<int> v;
  for (char c = 'A'; c <= 'Z'; c++) {
    v.push_back(get_score(c, scores));
  }
  return v;
}

// 3C
bool update_board(vector<vector<char>>& board, string word, int row, int col) {
  bool flag = false;
  vector<char> v = board[row];
  for (int i = 0; i < word.size(); i++) {
    if (v[col + i] == '\0')
      v[col + i] = word[i];
    else if (v[col + i] == word[i])
      flag = true;
    else
      return false;
  }
  if (flag)
    board[row] = v;
  return flag;
}
/*
3D
To transpose the board will take O(n2) for an n×n board, which is slower than
directly modifying a column which only takes O(n).
*/
