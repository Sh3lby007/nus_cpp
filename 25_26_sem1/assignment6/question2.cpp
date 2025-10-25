#include <iostream>
#include <set>
#include <string>
using namespace std;

int main() {
  int N, Q;
  cin >> N >> Q;

  set<int> sleeping;  // BST storing indices of sleeping cats

  for (int i = 0; i < Q; i++) {
    string operation;
    cin >> operation;

    if (operation == "SLEEP") {
      int x;
      cin >> x;
      sleeping.insert(x);
    } else if (operation == "WAKE") {
      int x;
      cin >> x;
      sleeping.erase(x);
    } else if (operation == "TRANSMIT") {
      int x, y;
      cin >> x >> y;

      // Check if any cat in range (x, y] is sleeping
      // We need to check if there's any sleeping cat with index > x and <= y

      if (x == y) {
        // Same cat, no transmission needed
        cout << "YES" << endl;
        continue;
      }

      // Find the first sleeping cat with index > x
      auto it = sleeping.upper_bound(x);

      // Check if this cat is within our range [x+1, y]
      if (it == sleeping.end() || *it > y) {
        // No sleeping cat in range (x, y]
        cout << "YES" << endl;
      } else {
        // Found a sleeping cat in the range
        cout << "NO" << endl;
      }
    }
  }

  return 0;
}