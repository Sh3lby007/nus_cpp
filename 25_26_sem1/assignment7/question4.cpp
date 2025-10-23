#include <iostream>
#include <queue>
#include <vector>
using namespace std;

void solution() {
  int N;
  cin >> N;

  vector<long long> A(N);
  for (int i = 0; i < N; i++) {
    cin >> A[i];
  }

  long long candies = 0;
  int visited = 0;

  // Max-heap to store negative values we've taken
  priority_queue<long long> negativeHeap;

  for (int i = 0; i < N; i++) {
    candies += A[i];
    visited++;

    if (A[i] < 0) {
      negativeHeap.push(-A[i]);  // Store absolute value
    }

    // If we went negative, undo the worst negative house
    if (candies < 0 && !negativeHeap.empty()) {
      long long worstNegative = negativeHeap.top();
      negativeHeap.pop();
      candies += worstNegative;  // Undo it
      visited--;                 // Didn't actually visit it
    }
  }

  cout << visited << endl;
  return;
}

int main() {
  solution();
  return 0;
}