#include <cmath>  //for sqrt()
#include <cstdio>
#include <cstdlib>  //for random number generator, rand()
#include <iostream>
#include <vector>

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
void mat_mul(int A[][P], int B[][N], int C[][N]) {
  for (int i = 0; i < M; i++) {
    for (int j = 0; j < N; j++) {
      C[i][j] = dot_product(A, B, i, j);
    }
  }
}

/******************************************
Task 3.
******************************************/

#define MAXROW 20
#define MAXCOL 20

// Use 9 to represent a mine
#define MINE 9

// Purpose: Display (print) a minefield of nRow x nCol
//          Mines are printed as "M"
//          Non-Mines are printed as a single digit, representing
//             number of near-by mines
void print_field(vector<vector<int>>& field) {
  for (int i = 0; i < field.size(); i++) {
    for (int j = 0; j < field[0].size(); j++) {
      if (field[i][j] == MINE) {
        cout << "M";
      } else {
        cout << field[i][j];
      }
    }
    cout << "\n";
  }
}

// Purpose: Update the count in the 8 neighbouring cells of [row][col]
void update_neighbour(vector<vector<int>>& field, int row, int col) {
  for (int i = row - 1; i <= row + 1; i++) {
    for (int j = col - 1; j < col + 1; j++) {
      // Skip if:
      // 1. Out of bounds (i < 0 or j < 0)
      // 2. Out of bounds (i >= size or j >= size)
      // 3. It's the mine position itself field[i][j]
      if ((i < 0) || (i >= field.size()) || (j < 0) || (j >= field[0].size()) ||
          field[i][j] >= MINE) {
        continue;
      }
      field[i][j]++;
    }
  }
}

// Purpose: Add nMine mines randomly in a field of nRow X nCol
// Note:    Does not use the "halo" approach.
void plant_mine(vector<vector<int>>& field, int nMine) {
  int rows = field.size();
  int cols = field[0].size();

  for (int i = 0; i < nMine; i++) {
    int row = rand() % rows;
    int col = rand() % cols;

    // if location already contains a mine, then try again
    if (field[row][col] == MINE) {
      i--;
      continue;
    }

    printf("Planting mine at [%d][%d]\n", row, col);
    field[row][col] = MINE;
    update_neighbour(field, row, col);
  }
}

// Purpose: Add nMine mines randomly in a field of nRow X nCol
// Note:    Use the "halo" approach to simplify border checking
void plant_mine_halo(vector<vector<int>>& field, int nMine) {
  // Step 1: Get dimensions of original field
  int nRow = field.size();
  int nCol = field[0].size();

  // Step 2: Create halo by copying original field
  vector<vector<int>> halo = field;  // Direct copy of original field

  // Step 3: Add the halo borders to each existing row
  for (int row = 0; row < halo.size(); row++) {
    halo[row].insert(halo[row].begin(), 0);  // Add 0 at start of row
    halo[row].push_back(0);                  // Add 0 at end of row
  }

  // Step 4: Add top and bottom rows to complete the halo
  vector<int> row(halo[0].size(), 0);  // Create a row of zeros
  halo.insert(halo.begin(), row);      // Insert at top
  halo.push_back(row);                 // Add at bottom

  // Step 5: Plant mines with halo offset
  for (int i = 0; i < nMine; i++) {
    // +1 because of halo border
    int row = (rand() % nRow) + 1;  // Random row within inner field
    int col = (rand() % nCol) + 1;  // Random col within inner field

    // Check if location already has mine
    if (halo[row][col] >= MINE) {
      i--;  // Try again
      continue;
    }

    // Debug message
    printf("Planting mine at [%d][%d]\n", row, col);

    // Step 6: Update neighbors without boundary checking
    for (int j = row - 1; j <= row + 1; j++) {
      for (int k = col - 1; k <= col + 1; k++) {
        // Since we have halo, no need to check boundaries!
        if (j == row && k == col) {
          halo[j][k] = MINE;  // Place mine
        } else {
          halo[j][k]++;  // Increment neighbor count
        }
      }
    }
  }

  // Step 7: Transfer back to original field
  for (int i = 0; i < nRow; i++) {
    for (int j = 0; j < nCol; j++) {
      // Copy from halo (offset by 1) back to field
      field[i][j] = halo[i + 1][j + 1];
    }
  }
}

int main() {
  // Declare a line
  Line l;
  Line l2;

  // Read a line
  // readLine(l);

  // Print a line
  // printLine(l);

  // Simple test of length
  // cout << "Length V1: " << length(&l) << endl;

  // Simple test of length2, notice how "l" is passed to the function
  // cout << "Length V2: " << length2(l) << endl;

  // Simple test of compareLine, should get 3 different answers
  l2 = l;
  // cout << "Compare result = " << compareLine(l, l2) << endl;

  l2.start.X--;
  // cout << "Compare result = " << compareLine(l, l2) << endl;

  l2 = l;
  l2.start.X++;
  // cout << "Compare result = " << compareLine(l, l2) << endl;

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

  // Task 3
  vector<int> row(MAXCOL, 0);
  vector<vector<int>> field(MAXROW, row);

  // before initialization
  print_field(field);

  // plant the mines
  plant_mine(field, 10);
  plant_mine_halo(field, 10);

  // after initialization
  print_field(field);
  return 0;
}