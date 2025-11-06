#include <deque>
#include <iostream>
#include <string>
using namespace std;

void solution() {
  int Q;
  cin >> Q;

  deque<int> queue;

  for (int i = 0; i < Q; i++) {
    string op;
    cin >> op;

    if (op == "PUSH") {
      int x;
      cin >> x;
      queue.push_back(x);
    } else if (op == "POP") {
      cout << queue.front() << endl;
      queue.pop_front();
    } else if (op == "POPMIDDLE") {
      int size = queue.size();
      int middleIndex = size / 2;  // 0-indexed middle

      // Output the middle element
      cout << queue[middleIndex] << endl;

      // Remove the middle element by rebuilding the deque
      deque<int> newQueue;
      for (int j = 0; j < size; j++) {
        if (j != middleIndex) {
          newQueue.push_back(queue[j]);
        }
      }
      queue = newQueue;
    }
  }

  // Output final queue
  bool first = true;
  for (int val : queue) {
    if (!first) cout << " ";
    cout << val;
    first = false;
  }
  cout << endl;
}

int main() {
  solution();
  return 0;
}
