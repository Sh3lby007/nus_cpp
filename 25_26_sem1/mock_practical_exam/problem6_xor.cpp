#include <iostream>
#include <vector>
using namespace std;

void solution() {
  int N;
  cin >> N;

  vector<int> A(N);
  for (int i = 0; i < N; i++) {
    cin >> A[i];
  }

  int maxXor = 0;

  // Try all 2^N subsets using bitmask
  for (int mask = 0; mask < (1 << N); mask++) {
    int currentXor = 0;

    // Calculate XOR of all elements in this subset
    for (int i = 0; i < N; i++) {
      if (mask & (1 << i)) {
        currentXor ^= A[i];
      }
    }

    maxXor = max(maxXor, currentXor);
  }

  cout << maxXor << endl;
}

int main() {
  solution();
  return 0;
}
