#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>
using namespace std;

int solution() {
  int N, M;
  cin >> N >> M;

  vector<long long> a(N), b(N);

  // Read left positions
  for (int i = 0; i < N; i++) {
    cin >> a[i];
  }

  // Read right positions
  for (int i = 0; i < N; i++) {
    cin >> b[i];
  }

  // Read query positions
  vector<long long> p(M);
  for (int i = 0; i < M; i++) {
    cin >> p[i];
  }

  // Process each query
  vector<long long> results;

  for (int j = 0; j < M; j++) {
    long long pos = p[j];
    long long minWidth = LLONG_MAX;
    bool found = false;

    // Check each pillar pair
    for (int i = 0; i < N; i++) {
      // Check if position is between this pair of pillars
      if (a[i] <= pos && pos <= b[i]) {
        found = true;
        long long width = b[i] - a[i];
        minWidth = min(minWidth, width);
      }
    }

    if (found) {
      results.push_back(minWidth);
    } else {
      results.push_back(-1);
    }
  }

  // Output results
  for (int i = 0; i < M; i++) {
    if (i > 0)
      cout << " ";
    cout << results[i];
  }
  cout << endl;

  return 0;
}

int main() {
  solution();
  return 0;
}