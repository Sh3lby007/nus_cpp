#include <iostream>
#include <map>
using namespace std;

int main() {
  int s, n;
  cin >> s >> n;

  // multimap: key = agar size (t), value = growth (x)
  // multimap keeps elements sorted by key and allows duplicates
  multimap<int, int> agars;

  for (int i = 0; i < n; i++) {
    int t, x;
    cin >> t >> x;
    agars.insert({t, x});
  }

  int jeremySize = s;
  int absorbed = 0;

  // Keep trying to absorb agars until we can't anymore
  while (absorbed < n) {
    // Find the largest agar that Jeremy can absorb (t < jeremySize)
    // This is the largest element with key < jeremySize
    auto it = agars.lower_bound(jeremySize);

    // lower_bound gives first element >= jeremySize
    // We want the largest element < jeremySize, so go back one
    if (it == agars.begin()) {
      // No agar smaller than Jeremy's size
      cout << "No" << endl;
      return 0;
    }

    // Go back to get the largest agar smaller than jeremySize
    --it;

    // Absorb this agar
    int growth = it->second;
    jeremySize += growth;
    absorbed++;

    // Remove this agar from the map
    agars.erase(it);
  }

  // Successfully absorbed all agars
  cout << "Yes" << endl;
  return 0;
}