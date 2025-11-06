#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

void solution() {
  int N, K;
  cin >> N >> K;
  string s;
  cin >> s;

  // Rolling hash parameters
  const long long BASE = 31;
  const long long MOD = 1e9 + 7;

  // Precompute BASE^K mod MOD
  long long base_k = 1;
  for (int i = 0; i < K; i++) {
    base_k = (base_k * BASE) % MOD;
  }

  // Map from hash value to the most recent index where it occurred
  unordered_map<long long, int> last_occurrence;

  // Compute initial hash for s[0..K-1]
  long long hash_val = 0;
  for (int i = 0; i < K; i++) {
    hash_val = (hash_val * BASE + (s[i] - 'a' + 1)) % MOD;
  }

  vector<int> result;

  // Process first window
  if (last_occurrence.count(hash_val)) {
    result.push_back(last_occurrence[hash_val]);
  } else {
    result.push_back(-1);
  }
  last_occurrence[hash_val] = 0;

  // Slide the window from position 1 to N-K
  for (int j = 1; j <= N - K; j++) {
    // Remove the leftmost character s[j-1]
    long long remove_val = ((s[j - 1] - 'a' + 1) * base_k) % MOD;
    hash_val = (hash_val - remove_val + MOD) % MOD;

    // Shift left (multiply by BASE)
    hash_val = (hash_val * BASE) % MOD;

    // Add the new rightmost character s[j+K-1]
    hash_val = (hash_val + (s[j + K - 1] - 'a' + 1)) % MOD;

    // Check if this hash was seen before
    if (last_occurrence.count(hash_val)) {
      result.push_back(last_occurrence[hash_val]);
    } else {
      result.push_back(-1);
    }

    // Update the last occurrence of this hash
    last_occurrence[hash_val] = j;
  }

  // Output results
  for (int i = 0; i < result.size(); i++) {
    if (i > 0)
      cout << " ";
    cout << result[i];
  }
  cout << "\n";
}

int main() {
  solution();
  return 0;
}