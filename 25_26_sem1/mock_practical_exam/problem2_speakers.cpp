#include <iostream>
#include <set>
#include <string>
using namespace std;

void solution() {
  int Q;
  long long L;
  cin >> Q >> L;

  set<long long> schedule;  // Stores start times of scheduled speeches

  for (int i = 0; i < Q; i++) {
    string op;
    cin >> op;

    if (op == "INSERT") {
      long long S;
      cin >> S;

      // Check if new speech [S, S+L-1] clashes with any existing speech
      // It clashes with speech starting at T if: S-L < T < S+L

      // Find first speech with start time > S-L
      auto it = schedule.upper_bound(S - L);

      // Check if this speech starts before S+L
      if (it != schedule.end() && *it < S + L) {
        // Clash detected
        cout << "N" << endl;
      } else {
        // No clash, add the speech
        schedule.insert(S);
        cout << "Y" << endl;
      }
    } else if (op == "REMOVE") {
      long long S;
      cin >> S;

      // Check if speech starting at S exists
      if (schedule.count(S)) {
        schedule.erase(S);
        cout << "Y" << endl;
      } else {
        cout << "N" << endl;
      }
    }
  }

  // Output final schedule in increasing order
  bool first = true;
  for (long long startTime : schedule) {
    if (!first) cout << " ";
    cout << startTime;
    first = false;
  }
  cout << endl;
}

int main() {
  solution();
  return 0;
}
