#include <climits>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

void solution() {
  int N, K;
  cin >> N >> K;

  vector<char> operators(N);
  vector<int> operands(N);

  // Read instructions
  for (int i = 0; i < N; i++) {
    cin >> operators[i] >> operands[i];
  }

  int bestResult = 0;
  int minDifference = abs(K - 0);

  // Try all possible combinations using bitmask
  // Bit i represents whether instruction i is applied
  int totalCombinations = 1 << N;  // 2^N combinations

  for (int mask = 0; mask < totalCombinations; mask++) {
    int current = 0;

    // Apply instructions based on the mask
    for (int i = 0; i < N; i++) {
      if (mask & (1 << i)) {
        // Apply instruction i
        char op = operators[i];
        int operand = operands[i];

        if (op == '+') {
          current += operand;
        } else if (op == '-') {
          current -= operand;
        } else if (op == '*') {
          current *= operand;
        } else if (op == '/') {
          current /= operand;  // Integer division
        }
      }
    }

    // Check if this result is better
    int difference = abs(current - K);

    if (difference < minDifference ||
        (difference == minDifference && current < bestResult)) {
      minDifference = difference;
      bestResult = current;
    }
  }

  cout << bestResult << endl;
}

int main() {
  solution();
  return 0;
}