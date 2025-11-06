#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

void solution() {
  int N, K;
  cin >> N >> K;

  vector<char> ops(N);
  vector<int> nums(N);

  for (int i = 0; i < N; i++) {
    cin >> ops[i] >> nums[i];
  }

  int bestValue = 0;
  int bestDist = abs(0 - K);

  // Try all 2^N combinations using bitmask
  for (int mask = 0; mask < (1 << N); mask++) {
    int current = 0;

    // Apply instructions according to the mask
    for (int i = 0; i < N; i++) {
      if (mask & (1 << i)) {
        // Apply instruction i
        if (ops[i] == '+') {
          current += nums[i];
        } else if (ops[i] == '-') {
          current -= nums[i];
        } else if (ops[i] == '*') {
          current *= nums[i];
        } else if (ops[i] == '/') {
          current /= nums[i];
        }
      }
    }

    // Check if this result is better
    int dist = abs(current - K);
    if (dist < bestDist || (dist == bestDist && current < bestValue)) {
      bestDist = dist;
      bestValue = current;
    }
  }

  cout << bestValue << endl;
}

int main() {
  solution();
  return 0;
}
