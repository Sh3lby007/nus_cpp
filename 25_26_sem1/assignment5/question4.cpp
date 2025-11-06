#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

void solution() {
  int N, Q, K;
  cin >> N >> Q >> K;
  string S;
  cin >> S;

  // Rolling hash parameters
  const long long BASE = 31;
  const long long MOD = 1e9 + 7;

  // Precompute BASE^K mod MOD
  long long base_k = 1;
  for (int i = 0; i < K; i++) {
    base_k = (base_k * BASE) % MOD;
  }

  // Count all K-length substrings in S
  unordered_map<long long, int> hash_count;

  if (N >= K) {
    // Initial hash
    long long hash_val = 0;
    for (int i = 0; i < K; i++) {
      hash_val = (hash_val * BASE + (S[i] - 'a' + 1)) % MOD;
    }
    hash_count[hash_val]++;

    // Rolling hash
    for (int i = K; i < N; i++) {
      long long remove_val = ((S[i - K] - 'a' + 1) * base_k) % MOD;
      hash_val = (hash_val - remove_val + MOD) % MOD;
      hash_val = (hash_val * BASE) % MOD;
      hash_val = (hash_val + (S[i] - 'a' + 1)) % MOD;
      hash_count[hash_val]++;
    }
  }

  // Process queries
  for (int q = 0; q < Q; q++) {
    string query;
    cin >> query;

    // Compute hash of query
    long long query_hash = 0;
    for (int i = 0; i < K; i++) {
      query_hash = (query_hash * BASE + (query[i] - 'a' + 1)) % MOD;
    }

    cout << hash_count[query_hash] << "\n";
  }
}

int main() {
  solution();
  return 0;
}