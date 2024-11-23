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