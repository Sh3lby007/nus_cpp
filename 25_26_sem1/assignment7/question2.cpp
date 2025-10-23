#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int solution() {
  int N;
  cin >> N;

  priority_queue<int> maxHeap;

  priority_queue<int, vector<int>, greater<int>> minHeap;

  for (int i = 0; i < N; i++) {
    int num;
    cin >> num;

    maxHeap.push(num);

    minHeap.push(maxHeap.top());
    maxHeap.pop();

    if (maxHeap.size() < minHeap.size()) {
      maxHeap.push(minHeap.top());
      minHeap.pop();
    }
  }

  int M;
  cin >> M;

  for (int i = 0; i < M; i++) {
    string operation;
    cin >> operation;

    if (operation == "QUERY") {
      cout << maxHeap.top() << endl;

    } else if (operation == "ADD") {
      int b;
      cin >> b;

      if (maxHeap.empty() || b <= maxHeap.top()) {
        maxHeap.push(b);
      } else {
        minHeap.push(b);
      }

      if (maxHeap.size() > minHeap.size() + 1) {
        minHeap.push(maxHeap.top());
        maxHeap.pop();
      } else if (minHeap.size() > maxHeap.size()) {
        maxHeap.push(minHeap.top());
        minHeap.pop();
      }

    } else if (operation == "REMOVE") {
      int median = maxHeap.top();
      maxHeap.pop();

      if (minHeap.size() > maxHeap.size()) {
        maxHeap.push(minHeap.top());
        minHeap.pop();
      }
    }
  }

  return 0;
}

int main() {
  solution();
  return 0;
}