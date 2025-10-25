#include <iostream>
#include <map>
#include <vector>
using namespace std;

int main() {
  int n;
  cin >> n;

  vector<pair<int, int>> movies(n);  // {start, end}
  map<int, int> startToIndex;        // start time -> 1-based index

  // Read all movies and store them
  for (int i = 0; i < n; i++) {
    int start, end;
    cin >> start >> end;
    movies[i] = {start, end};
    startToIndex[start] = i + 1;  // 1-based index
  }

  // For each movie, find the next movie to watch
  for (int i = 0; i < n; i++) {
    int endTime = movies[i].second;

    // Find the first movie with start time >= endTime
    auto it = startToIndex.lower_bound(endTime);

    if (it == startToIndex.end()) {
      // No movie found
      cout << -1 << endl;
    } else {
      // Found the next movie
      cout << it->second << endl;
    }
  }

  return 0;
}