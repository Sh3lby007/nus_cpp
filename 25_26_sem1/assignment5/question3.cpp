#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int solution() {
  int N, D;
  cin >> N >> D;

  vector<long long> W(N), A(N), B(N);
  for (int i = 0; i < N; i++) {
    cin >> W[i] >> A[i] >> B[i];
  }

  // Create indices sorted by weight
  vector<int> indices(N);
  for (int i = 0; i < N; i++)
    indices[i] = i;
  sort(indices.begin(), indices.end(),
       [&](int i, int j) { return W[i] < W[j]; });

  vector<bool> paired(N, false);
  long long total_cost = 0;

  // Greedy pairing: for each item, try to pair with nearest valid item
  for (int idx = 0; idx < N; idx++) {
    int i = indices[idx];
    if (paired[i])
      continue;

    long long best_cost = A[i];  // cost if pushed alone
    int best_pair = -1;

    // Look for valid pairing partner
    for (int jdx = idx + 1; jdx < N; jdx++) {
      int j = indices[jdx];
      if (paired[j])
        continue;
      if (W[j] - W[i] > D)
        break;  // sorted, so no more valid pairs

      long long pair_cost = B[i] + B[j];
      if (pair_cost < best_cost) {
        best_cost = pair_cost;
        best_pair = j;
      }
    }

    if (best_pair != -1) {
      paired[i] = paired[best_pair] = true;
      total_cost += best_cost;
    } else {
      paired[i] = true;
      total_cost += A[i];
    }
  }

  cout << total_cost << "\n";
  return 0;
}

int main() {
  solution();
  return 0;
}