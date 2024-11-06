// Lecture 7 Strings and Vectors
#include <iostream>
#include <vector>

using namespace std;
/*
Implement the function int days_of_month(int m) using a switch...case
statement that return the number of days of the given month of the year
 */
int days_of_month(int m) {
  switch (m) {
    case 4:
    case 6:
    case 9:
    case 11:
      return 30;
      /*
     When cases are written consecutively without any statements between them
     (like case 4: case 6: case 9: case 11:), it creates a "fall-through"
     effect. This means that any of these cases will execute the same code that
     follows.
     */
    case 2:
      return 28;
    case 1:
    case 3:
    case 5:
    case 7:
    case 10:
    case 12:
      return 31;
    default:
      return -1;
  }
}

/*
Implement the function bool find(int x, vector<int> v) which returns true if the
integer x is an element of the vector v, and false otherwise.
*/
bool find(int x, vector<int> v) {
  /*
  Just like arrays, elements in vectors must belong to
  the same type and it cannot be changed after declaration
  */
  for (int i = 0; i < v.size(); i++) {
    if (v[i] == x) {
      return true;
    }
  }
  return false;
}

/*
The function void invert(vector<bool> &v) takes in a vector of bool, and inverts
the elements, i.e. true becomes false, and vice versa. Provide an implementation
of the function invert.
*/
void invert(vector<bool> &v) {
  /*
  1. Takes vector by reference(&) to modify the original vector.
  2. Invert each element in the vector using the logical NOT operator(!)
  3. All elements are looped through and no return value as the function type is
  void
*/
  for (int i = 0; i < v.size(); i++) {
    v[i] = !v[i];
  }
}

/*
The logical operator and returns true only if both inputs
are true. The function vector<bool> And(vector<bool> v1, vector<bool> v2) takes
as input two vectors of equal length, and returns a new vector where each
element is a logical and of the two vectors. i.e., vi = true if v1i and v2i are
both true, for all elements i.
*/
vector<bool> And(vector<bool> v1, vector<bool> v2) {
  /*
  1. Create new vector to store result
  2. Use logical AND(&&) operator to combine element
  3. Process all element and return new result vector
  */
  vector<bool> result;
  for (int i = 0; i < v1.size(); i++) {
    // push_back adds new element to the back of the vector
    result.push_back(v1[i] && v2[i]);
  }
  return result;
}

int main() {
  vector<bool> invertFn = {true, false, true, false, true, false};

  // Test And function
  vector<bool> v1 = {true, true, false, true};
  vector<bool> v2 = {true, false, false, true};
  vector<bool> result = And(v1, v2);

  cout << boolalpha;  // Makes bool print as true/false instead of 1/0
  cout << "AND result: ";
  for (bool b : result) {
    cout << b << " ";
  }
  cout << endl;
  cout << "days in month 1:" << days_of_month(1) << endl;
  cout << "Finding 1: " << find(1, vector<int>{5, 2, 6, 1, 3, 7}) << endl;
  cout << "Finding 7: " << find(7, vector<int>{5, 2, 6, 1, 3, 7}) << endl;
  cout << "Finding 0: " << find(0, vector<int>{5, 2, 6, 1, 3, 7}) << endl;
  return 0;
}