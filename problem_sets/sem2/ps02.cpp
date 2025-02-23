#include <cstdio>
#include <iostream>

using namespace std;

/******************************************
Task 1.
******************************************/
// used to count the number of times fibonacci is called
int __call_count = 0;

int fibonacci_m(int N, int known_result[]) {
  // Do not remove the following line
  __call_count++;

  // Put your code below
  if (N <= 2) {
    known_result[N] = 1;
    return 1;
  }

  // Check if we already know the result
  if (known_result[N] != 0) {
    return known_result[N];
  }

  // Calculate and store the result for future use
  known_result[N] =
      fibonacci_m(N - 1, known_result) + fibonacci_m(N - 2, known_result);
  return known_result[N];
}

/******************************************
Task 2.
******************************************/
int polynomial(int xValue, int termArray[], int nTerm) {
  if (nTerm == 0) {
    return 0;
  }
  return termArray[0] * xValue +
         xValue * polynomial(xValue, termArray + 1, nTerm - 1);
}

void printPolynomial(int termArray[], int nTerm) {
  int i;

  for (i = 0; i < nTerm; i++) {
    if (i > 0) {
      cout << "+ ";
    }
    cout << termArray[i];
    switch (i) {
      case 0:
        cout << "X";
        break;
      default:
        cout << "X^" << (i + 1);
    }
    cout << " ";
  }

  cout << endl;
}

/******************************************
Task 3.
******************************************/
struct Point {
  int X, Y;
};

// Compare two points: returns true if a should come after b
bool compare(const Point& a, const Point& b) {
  if (a.X != b.X) {
      return a.X > b.X; // Sort by X-coordinate
  } else {
      return a.Y > b.Y; // If X is equal, sort by Y-coordinate
  }
}

// Recursive Bubble Sort implementation
void sort(Point a[], int n) {
  if (n <= 1) return; // Base case: array of size 1 or less is already sorted

  // Perform one pass of Bubble Sort
  for (int i = 0; i < n - 1; i++) {
      if (compare(a[i], a[i + 1])) {
          // Swap the elements if they are in the wrong order
          Point temp = a[i];
          a[i] = a[i + 1];
          a[i + 1] = temp;
      }
  }

  // Recursively sort the remaining n-1 elements
  sort(a, n - 1);
}

int main() {
  // Task 1
  int N;
  int known[50] = {0};

  //   cout << "N = ";
  //   cin >> N;

  //   printf("Fibonacci(%d) is %d\n", N, fibonacci_m(N, known));
  //   printf("Fibonacci() called %d times\n", __call_count);

  //   Task 2
  int poly[] = {3, 2, 1};

  // Test cases A
  printPolynomial(poly, 3);
  cout << "When X = 2, = " << polynomial(2, poly, 3) << endl;
  cout << "When X = 3, = " << polynomial(3, poly, 3) << endl << endl;

  // Test cases B
  int poly2[] = {7, 5, 3, 2};
  printPolynomial(poly2, 4);
  cout << "When X = 11, = " << polynomial(11, poly2, 4) << endl;
  cout << "When X = 13, = " << polynomial(13, poly2, 4) << endl;

// task 3
  Point ptArray[5] = { {11, 34}, {5, 73}, {11, 19}, {13, 5}, {11, 68} };

  sort(ptArray, 5);

  // The output should match the order given in the question
  for (int i = 0; i < 5; i++) {
      printf("(%d, %d)\n", ptArray[i].X, ptArray[i].Y);
  }

  return 0;
}
