#include <iostream>
#include <string>
#include <vector>
using namespace std;

void testA() {
  cout << "Testing Part A:\n";
  string s = "T'was Good";
  for (int i = 0; i < s.size(); i++) {
    if (s[i] >= 'a') {
      s[i] -= 32;
    } else {
      s[i] += 32;  // "T", "apostophe", "space" and "G" are smaller than 'a
    }
  }
  cout << s << endl;
  // tGWAS@gOOD
}

int f(int &x) {
  x += x;
  return x / 2;
}

int g(int &x, int &y) {
  if (x > y) {
    x -= f(y) + y;
  } else {
    y -= x + f(x);
  }
  cout << x << "," << y << endl;
  return y - x;
}

void testC() {
  cout << "Testing Part C:\n";
  vector<int> v = {7, 1, 2, 0, 6, 5, 4, 3};
  vector<int> w;
  /*
  1st loop i = 0, 0 < 8 which is true, push_back(0) into
  vector w, i then becomes v[0] = 7
  2nd loop i = 7, 7 < 8 which is true, push_back(7) into
  vector w, i then becomes v[7] = 4
  3rd loop i = 4, 4 < 8 which is true, push_back(4) into
  vector w, i then becomes v[4] = 0
  4th loop, i = 0, back to 1st loop which means this will continue infinitely
  Answer sheet:  Vector v does not contain a value that is larger than its size.
  */
  for (int i = 0; i < v.size(); i = v[i]) {
    cout << i << endl;
    w.push_back(i);
  }
  for (int j = 0; j < w.size(); j++) {
    cout << w[j] << " ";
  }
}

void testD() {
  cout << "Testing Part D:\n";
  int n = 0;
  for (int i = 1; i < 12; i += 3) {
    /*
    i   n
    1   0
    4   1
    9   7
    */
    cout << i << "," << n << endl;
    /*
    In if else conditions, without braces { }, only ONE
    statement belongs to the if or else. Any subsequent
    statements are always executed regardless of the condition.
    */
    if (i % 2 == 0)
      i += 2;
    else
      n /= i;
    n += i;  // not part of else condition, runs every loop
  }
  // 7
  cout << n;
}
/*
Implement the function int s11(int n) that takes in a
positive integer n and returns the value of the alternating series s11(n).
*/
int s11(int n) {
  int result = 0;
  for (int i = 1; i <= n; i++) {
    if (i % 2)      // for odd numbers
      result += i;  // add odd numbers (1, 3, 5, ...)

    else            // for even numbers
      result -= i;  // subtract even numbers (-2, -4, -6, ...)
  }
  return result;
}
/*
Implement the function int s(int i, int j, int n) which takes
in three positive integers i, j and n. The function returns
the value of sij(n). In other words, s(1, 1, n) returns the
same result as s11(n)
*/
int s(int i, int j, int n) {
  // i: number of consecutive positive terms
  // j: number of consecutive negative terms
  // n: the upper limit
  int result = 0;
  for (int c = 0; c < n; c++) {
    if (c % (i + j) < i) {
      result += c + 1;
    } else {
      result -= c + 1;
    }
  }
  return result;
}

/*
Implement the function reverse which takes in vector of
integers, and modifies it by re-versing the values. For
example, a vector {1, 2, 3, 4, 5} will become {5, 4, 3, 2, 1}
*/

void reverse(vector<int> &v) {
  vector<int> copy;
  for (int i = v.size() - 1; i >= 0; i--) {
    copy.push_back(v[i]);
  }
  v = copy;
}
/*
Implement the function compact that takes in a vector of
integers, and compacts the non-zero values to the left. In
other words, all non-zero values are moved to the left
(index 0) and the remaining values are zeroed, retaining the
original length of the vector.
*/

void compact_ai(vector<int> &v) {
  int writePos = 0;
  for (int i = 0; i < v.size(); i++) {
    if (v[i] != 0) {
      v[writePos] = v[i];
      writePos++;
    }
  }
  while (writePos < v.size()) {
    v[writePos++] = 0;
  }
}

void compact(vector<int> &v) {
  vector<int> copy;
  for (int i = 0; i < v.size(); i++) {
    if (v[i] != 0) {
      copy.push_back(v[i]);
    }
  }
  while (copy.size() < v.size()) {
    copy.push_back(0);
  }
  v = copy;
}
/*
Suppose a vector of integers represents the row of tiles,
with 0 meaning an empty space. Implement the function
slide_left which takes in a vector of integers and perform
the sliding move on the vector as described above.
*/

void slide_left(vector<int> &v) {
  // First compact all numbers to left
  compact(v);

  // Now merge adjacent equal numbers
  for (int i = 0; i < v.size() - 1; i++) {
    if (v[i] != 0 && v[i] == v[i + 1]) {
      v[i] *= 2;     // double the first number
      v[i + 1] = 0;  // zero out second number
      i++;           // skip next number (can't merge twice)
    }
  }
  // Compact again to fill gaps from merging
  compact(v);
}

/*
Implement the function slide_right which takes in a vector of
integers and perform the sliding behaviour towards the right side.
*/
void slide_right(vector<int> &v) {
  reverse(v);
  slide_left(v);
  reverse(v);
}

int main() {
  int x = 8;
  int y = 2;
  y += g(x, y);
  /*
  First call g(8, 2)
  x is more than y so x = 8 - (f(2) + y)
  f(2): y becomes 4, returns 2
  since y is passed by reference, y changes to 4 as well
  therefore x = 8 - (2 + 4) = 2, y: 4
  prints 2, 4 in function g
  back to main, y = 4 + (y-x) = 6
  prints 2, 6 in main()
  */
  cout << x << "," << y << endl;
  x += g(x, y);
  /*
  Second call g(2, 6)
  x is not more than y so y = y - (x + f(x))
  f(2) : x becomes 4, returns 2
  since x is passed by reference, x changes to 4 as well
  therefore y = 6 - (2 + 2) = 2
  why x value didnt change to 4 and could be because of the
  sequence of x, it comes before f(x) and hence retains the original value
  prints 4, 2 in function g
  back to main x = 4 + (y - x) = 4 + (2 - 4) = 2
  prints 2, 2 in  main()
  */
  cout << x << "," << y << endl;
  testA();
  //   testC();
  testD();
}