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

int main() {
  // Test all parts
  testA();
  testB();
  testC();
  testD();

  return 0;
}