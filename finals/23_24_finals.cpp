#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Part A
void testA() {
  cout << "Testing Part A:\n";
  string s = "Merry X'mas";
  string t = "Happy B'day";
  for (int i = 0; i < s.size(); i++) {
    if (s[i] < t[i]) cout << s[i];
    if (t[i] < s[i]) cout << t[i];
    /*
    if string s and t has the same character, both if statement will
    not execute therefore nothing will be printed for 'y', 'space',
    'apostrophe' and 'a'
    Output will be HappBds
    */
  }
  cout << "\n\n";
}

// Part B
int* f(int* x, int& y) {
  printf("%d %d\n", *x, y);
  *x *= y;
  y += 1;
  return x;
}

void testB() {
  cout << "Testing Part B:\n";
  int a = 3;
  int b = 2;
  /*
  This is a nested call, so inner f executes first:
  Inner f(&a, b): x points to a (value 3)
  y references b (value 2)
  prints: 3 2
  *x *= y: a becomes 3 * 2 = 6
  y += 1: b becomes 3
  returns pointer to a

  Outer f(pointer_to_a, b):
  x points to a (value 6)
  y references b (value 3
  prints: 6 3
  *x *= y: a becomes 6 * 3 = 18
  y += 1: b becomes 4
  returns pointer to a
*/
  int* c = f(f(&a, b), b);
  printf("%d %d %d\n\n", a, b, *c);
  /*
  b is passed by reference, so changes to y affect b
  The pointer returned by inner f(&a, b) points to a
  Both function calls modify the same variable a
  c ends up pointing to a
  */
}

// Part C
void testC() {
  cout << "Testing Part C:\n";
  vector<int> v = {8, 9, 6, 7, 4, 5, 4, 3, 8, 2, 0, 1};
  int n = v[0];
  for (int i = 1; i < v.size(); i++) {
    if (v[i] < n) {
      v[0] = v[i];
      v[i] = n;
      n = v[0];
      cout << n << endl;
    }
  }
  cout << "\n";  // 6 \n 4 \n 3 \n 2 \n 0
}

// Part D
void testD() {
  cout << "Testing Part D:\n";
  int j = 9;
  for (int i = 1; i < j; i++) {
    if (j % i == 0) {
      j += 1;
      continue;  // ignore everything and go next loop
    }
    printf("%d %d\n", i, j);
    /* j    i
1st    11   3
2st    10   4
3st    9    5
3st    8    6
    */
    j -= 1;
    if (j % i == 0) {
      i -= 1;
    }
  }
  cout << "\n";
}

/*
To play the game, players need to roll a die. Suppose the function
double random() returns a real number between zero (inclusive) and
one (exclusive) with uniform probability, i.e., [0,1). Using
random() , implement the function int dice(int n) that takes in a
positive integer n, and simulates a roll of a die with n sides. The
function returns a random integer between 1 (inclusive) and n
(inclusive) with uniform probability, i.e., [1, n].
*/
int dice(int n) {
  /*
  Understand the question and requirement
  1. You have a random() function that gives [0,1]
  2. We need a dice function that returns [1,n] both inclusive
  3. n represents the number of sides on a die
  4. Experiement with small test cases
  random() = 0.1  →  0.1 * 6 = 0.6
  random() = 0.5  →  0.5 * 6 = 3.0
  random() = 0.99 →  0.99 * 6 = 5.94
  5. If we get values less than 1, int type will always round down to 0, so we
  need to add 1 to the result
  */
  return random() * n + 1;
}

/*
Implement the function that takes as input a board, and returns true
if the board conforms to this rule, and false otherwise.
*/
bool is_valid_ai(vector<int> board) {
  for (int i = 0; i < board.size(); i++) {
    // For each position i
    // board[i] gives us where position i jumps to
    // board[board[i]] gives us where the destination jumps to

    if (board[board[i]] != board[i]) {
      /* board = {0, 1, 7, 3, 4, 5, 6, 10, 4, 9, 10, 8, 12, 13}
      e.g: i = 2:
  - board[2] = 7 (position 2 jumps to 7)
  - board[board[2]] = board[7] = 10 (position 7 jumps to 10)
  - 10 != 7, return false
      */
      // If this is true, it means:
      // 1. We found position i
      // 2. It jumps to position board[i]
      // 3. Position board[i] jumps somewhere else
      // Therefore, a destination is also a source
      return false;
    }
  }
  return true;
}

bool is_valid_mine(vector<int> board) {
  int pos;
  for (int i = 0; i < board.size(); i++) {
    pos = board[i];
    if (pos != i) {             // if this position has a jump
      if (board[pos] != pos) {  // if destination points somewhere else
        return false;           // mark as invalid
      }
    }
  }
  return true;
}

/*
The function update takes in a board, a player and the outcome
of a die roll, and updates the player’s position after moving
according to the die roll. Decide on the appropriate types for
the function and provide an implementation.
*/

void update_hard(vector<int> board, int& player, int roll) {
  // First move player forward
  player += roll;

  // If player goes beyond board end
  if (player >= board.size()) {
    // Calculate backwards movement
    /*
    For a board of size n:
    If player rolls to position n+k (k spaces past the end)
    They should end up k spaces back from the end
    So: final_pos = (n-1) - k
    Where k = (original_pos - (n-1))
    Substituting: final_pos = (n-1) - (original_pos - (n-1))
    Simplifies to: final_pos = 2(n-1) - original_pos
    Further simplifies to: final_pos = 2(n - player - 1)

    The key aspects to understand are:

    Pass player by reference (&) to modify the actual position
    Handle bouncing back when going past board end
    Apply any jumps at the final position
    Make sure to use board[] only with valid indices
    */
    player = 2 * (board.size() - player - 1);
  }

  // Apply any jump at final position
  player = board[player];
}

void update_easy(vector<int> board, int& player, int roll) {
  // First move forward
  player += roll;

  // If past board end, work backwards
  if (player >= board.size()) {
    int board_end = board.size() - 1;
    int steps_remaining = player - board_end;
    // Move back from end
    player = board_end - steps_remaining;
  }
  /*
  Board size: 10 (positions 0-9)
  Player at: 7
  Roll: 5

  1. Move forward: 7 + 5 = 12
  2. We passed position 9 (end)
  3. board_end = 9
  4. steps_remaining = 12 - 9 = 3
  5. final_position = 9 - 3 = 6
  */
  // Apply jump
  player = board[player];
}

/*
Implement the function which takes as input a board, and returns
true if the board is can be flipped, and false otherwise.
*/

bool can_flip(vector<int> board) {
  for (int i = 0; i < board.size(); i++) {
    if (board[i] != i && board[i] != -1) {  // Found a jump
      if (board[board[i]] == -1) {          // Destination already marked
        return false;
      }
      board[board[i]] = -1;  // Mark destination as used
    }
  }
  return true;
}

/*
Implement the function void flip(vector<int> & board) which
takes as input a valid board that can be flipped, and flips
all the jumps on the board.
*/
void flip(vector<int>& board) {
  // Make copy of original board
  vector<int> old = board;

  for (int i = 0; i < old.size(); i++) {
    if (old[i] != i) {    // if position i has a jump in original board
      int dest = old[i];  // get original destination
      board[i] = i;       // reset source position
      board[dest] = i;    // make destination jump back to source
    }
  }
  /*
  1. Must make a copy of original board first
  2. Use the copy to find original jumps
  3. Reset source positions to point to themselves
  4. Make destinations point back to sources
  5. Order matters - need to keep original jumps intact while processing
*/
}
int main() {
  // Test all parts
  testA();
  testB();
  testC();
  testD();

  return 0;
}