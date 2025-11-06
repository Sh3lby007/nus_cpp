#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;

void solution() {
  int Q;
  cin >> Q;

  map<string, int> freq;  // frequency of each item

  while (Q--) {
    string op;
    cin >> op;

    if (op == "INSERT") {
      string item;
      cin >> item;
      freq[item]++;
    } else if (op == "DELETE") {
      string item;
      cin >> item;
      if (freq.count(item) && freq[item] > 0) {
        freq[item]--;
        if (freq[item] == 0) {
          freq.erase(item);
        }
      }
    } else if (op == "QUERY") {
      int k;
      cin >> k;

      // Build list of (frequency, item_name) pairs
      vector<pair<int, string>> items;
      for (auto& p : freq) {
        if (p.second > 0) {
          items.push_back({p.second, p.first});
        }
      }

      // Sort by frequency (descending), then by name (ascending)
      sort(items.begin(), items.end(),
           [](const pair<int, string>& a, const pair<int, string>& b) {
             if (a.first != b.first) {
               return a.first > b.first;  // higher frequency first
             }
             return a.second < b.second;  // alphabetically earlier
           });

      // Flatten the list and find k-th item
      int pos = 0;
      for (auto& p : items) {
        int count = p.first;
        string name = p.second;

        if (pos + count >= k) {
          cout << name << "\n";
          break;
        }
        pos += count;
      }
    }
  }
}

int main() {
  solution();
  return 0;
}