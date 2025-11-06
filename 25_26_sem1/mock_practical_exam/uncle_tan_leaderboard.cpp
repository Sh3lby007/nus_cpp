#include <iostream>
#include <map>
#include <set>
#include <stack>
#include <string>
#include <vector>
using namespace std;

// Custom comparator for leaderboard ranking
// Sort by: score descending, then id ascending
struct LeaderboardComp {
  bool operator()(const pair<int, string>& a,
                  const pair<int, string>& b) const {
    if (a.first != b.first) {
      return a.first > b.first;  // Higher score comes first
    }
    return a.second < b.second;  // Lexicographically smaller id comes first
  }
};

// Snapshot structure to save state for SNAP/UNDO
struct Snapshot {
  map<string, int> scores;
  set<pair<int, string>, LeaderboardComp> leaderboard;
};

void solution() {
  int Q;
  cin >> Q;

  map<string, int> scores;  // id -> score
  set<pair<int, string>, LeaderboardComp> leaderboard;  // (score, id) sorted
  stack<Snapshot> checkpoints;  // Stack for SNAP/UNDO

  for (int i = 0; i < Q; i++) {
    string op;
    cin >> op;

    if (op == "ADD") {
      string id;
      int delta;
      cin >> id >> delta;

      // Remove old entry from leaderboard if exists
      if (scores.count(id)) {
        leaderboard.erase({scores[id], id});
      }

      // Update score
      scores[id] += delta;

      // Insert new entry into leaderboard
      leaderboard.insert({scores[id], id});

    } else if (op == "SNAP") {
      // Create checkpoint: save current state
      Snapshot snap;
      snap.scores = scores;
      snap.leaderboard = leaderboard;
      checkpoints.push(snap);

    } else if (op == "UNDO") {
      if (checkpoints.empty()) {
        cout << "EMPTY" << endl;
      } else {
        // Restore to last checkpoint
        Snapshot snap = checkpoints.top();
        checkpoints.pop();
        scores = snap.scores;
        leaderboard = snap.leaderboard;
      }

    } else if (op == "TOP") {
      int k;
      cin >> k;

      // Output top k players
      int count = 0;
      bool first = true;
      for (auto& entry : leaderboard) {
        if (count >= k) break;
        if (!first) cout << " ";
        cout << entry.second;  // Print id
        first = false;
        count++;
      }
      cout << endl;

    } else if (op == "SCORE") {
      string id;
      cin >> id;

      // Output score (0 if not exists)
      if (scores.count(id)) {
        cout << scores[id] << endl;
      } else {
        cout << 0 << endl;
      }
    }
  }
}

int main() {
  solution();
  return 0;
}
