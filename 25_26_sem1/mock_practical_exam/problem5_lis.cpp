#include <algorithm>
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

  // dp[i] = length of longest increasing subsequence ending at index i
  vector<int> dp(N, 1);

  for (int i = 1; i < N; i++) {
    for (int j = 0; j < i; j++) {
      if (A[j] < A[i]) {
        dp[i] = max(dp[i], dp[j] + 1);
      }
    }
  }

  // Find the maximum length
  int maxLen = *max_element(dp.begin(), dp.end());
  cout << maxLen << endl;
}

int main() {
  solution();
  return 0;
}
