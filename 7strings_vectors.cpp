// Lecture 7 Strings and Vectors
#include <iostream>
#include <vector>
using namespace std;

bool find(int x, vector<int> v) {
  for (int i = 0; i < v.size(); i++) {
    if (v[i] == x) {
      return true;
    }
  }
  return false;
}

int main() {
  cout << boolalpha;  // Makes bool print as true/false instead of 1/0
  cout << "Finding 1: " << find(1, vector<int>{5, 2, 6, 1, 3, 7}) << endl;
  cout << "Finding 7: " << find(7, vector<int>{5, 2, 6, 1, 3, 7}) << endl;
  cout << "Finding 0: " << find(0, vector<int>{5, 2, 6, 1, 3, 7}) << endl;
  return 0;
}