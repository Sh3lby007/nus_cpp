#include <iostream>
#include <map>
#include <set>
using namespace std;

void solution() {
  int Q;
  cin >> Q;

  // Map from tree ID to height
  map<int, int> idToHeight;

  // Multiset to store heights (allows duplicates, maintains sorted order)
  // This is essentially a balanced BST (typically Red-Black tree in STL)
  multiset<int> heights;

  for (int i = 0; i < Q; i++) {
    string operation;
    cin >> operation;

    if (operation == "ADD") {
      int id, h;
      cin >> id >> h;
      idToHeight[id] = h;
      heights.insert(h);

    } else if (operation == "REMOVE") {
      int id;
      cin >> id;
      if (idToHeight.find(id) != idToHeight.end()) {
        int h = idToHeight[id];
        heights.erase(heights.find(h));  // Remove one instance
        idToHeight.erase(id);
      }

    } else if (operation == "COUNT") {
      int a, b;
      cin >> a >> b;
      // Count elements in range [a, b]
      auto lower = heights.lower_bound(a);  // First element >= a
      auto upper = heights.upper_bound(b);  // First element > b
      int count = distance(lower, upper);
      cout << count << endl;

    } else if (operation == "KTH") {
      int k;
      cin >> k;
      if (k > (int)heights.size()) {
        cout << -1 << endl;
      } else {
        // k-th tallest means we need the k-th largest
        // In a sorted multiset, the k-th largest is at position (size - k)
        auto it = heights.rbegin();  // Start from largest
        advance(it, k - 1);          // Move to k-th largest
        cout << *it << endl;
      }
    }
  }
}

int main() {
  solution();
  return 0;
}