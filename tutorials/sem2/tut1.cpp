#include <cmath>  //for sqrt()
#include <cstdio>
#include <iostream>

using namespace std;

/******************************************
Task 1.
******************************************/

struct Point {
  int X, Y;
};

struct Line {
  // Consists of two points
  Point start, end;
};

// Purpose: Read X,Y coordinates into Point structure
// Output: The point structure referred by pptr is updated
// Return: None
void readPoint(Point& pRef) {
  cout << "Enter X and Y coordinate of a point: ";
  cin >> pRef.X >> pRef.Y;
}

// Purpose: Print X,Y coordinates of a Point structure
// Output: The point structure referred by pptr is printed
// Return: None
void printPoint(Point& pRef) {
  // An example of the more conveneint C-style printf()
  printf("(%d,%d)", pRef.X, pRef.Y);
}

// Purpose: Read two points of a straight line
// Output: The line structure lRef is updated
// Return: None
void readLine(Line& lRef) {
  cout << "Enter start point\n";
  readPoint(lRef.start);
  cout << "Enter end point\n";
  readPoint(lRef.end);
}

// Purpose: Print the two points of a line structure
// Output: The line structure lRef is printed
// Return: None
void printLine(Line& lRef) {
  printPoint(lRef.start);  // Using given printPoint()
  cout << " to ";
  printPoint(lRef.end);  // Using given printPoint()
  cout << endl;
}

// Purpose: Calculate the length of the line, line is passed by address
// Return: Length of the line
double length(Line* l) {
  int dx = l->end.X - l->start.X;
  int dy = l->end.Y - l->start.Y;
  return sqrt(dx * dx + dy * dy);
}

// Purpose: Calculate the length of the line, line is passed by reference
// Return: Length of the line
double length2(Line& l) {
  int dx = l.end.X - l.start.X;
  int dy = l.end.Y - l.start.Y;
  return sqrt(dx * dx + dy * dy);
}

// Purpose: Compare the length of line L1 vs line L2
// Return: an integer to indicate
//   -1 = L1 is shorter than L2
//    0 = L1 has the same length as L2
//    1 = L1 is longer than L2
int compareLine(Line& L1, Line& L2) {
  double len1 = length2(L1);
  double len2 = length2(L2);

  if (len1 < len2) return -1;
  if (len1 > len2) return 1;
  return 0;
}

/******************************************
Task 2.
******************************************/

// Defines for Readability
#define M 2
#define P 3
#define N 2

// Purpose: Perform the dot product at A[i][], B[][j]
//          Sum(A[i][k] * B[k][j]), for all k = 0...P-1
int dot_product(int A[][P], int B[][N], int i, int j) {
  // Initialize sum for the dot product
  int sum = 0;

  // Iterate through all corresponding elements
  for (int k = 0; k < P; k++) {
    // A[i][k] is element from row i of A
    // B[k][j] is element from column j of B
    sum += A[i][k] * B[k][j];

    // Optional: Debug print to see each multiplication
    // cout << "A[" << i << "][" << k << "]=" << A[i][k]
    //      << " * B[" << k << "][" << j << "]=" << B[k][j] << endl;
  }

  return sum;
}

// Purpose: Perform matrix multiplication for matrices A x B, result in C
void mat_mul(int A[][P], int B[][N], int C[][N]) {}

int main() {
  // Declare a line
  Line l;
  Line l2;

  // Read a line
  readLine(l);

  // Print a line
  printLine(l);

  // Simple test of length
  cout << "Length V1: " << length(&l) << endl;

  // Simple test of length2, notice how "l" is passed to the function
  cout << "Length V2: " << length2(l) << endl;

  // Simple test of compareLine, should get 3 different answers
  l2 = l;
  cout << "Compare result = " << compareLine(l, l2) << endl;

  l2.start.X--;
  cout << "Compare result = " << compareLine(l, l2) << endl;

  l2 = l;
  l2.start.X++;
  cout << "Compare result = " << compareLine(l, l2) << endl;

  // Task 2
  int matA[M][P] = {{1, 2, 3}, {4, 5, 6}};

  int matB[P][N] = {{1, 2}, {3, 4}, {5, 6}};

  int matC[M][N] = {{0}};  // just zeroes the whole matrix

  mat_mul(matA, matB, matC);

  // Simply print out the matrix for checking
  for (int i = 0; i < M; i++) {
    for (int j = 0; j < N; j++) {
      cout << matC[i][j] << " ";
    }
    cout << "\n";
  }

  return 0;
}