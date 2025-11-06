#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>
using namespace std;

void solution() {
  int n;
  cin >> n;
  vector<long long> heights(n);

  for (int i = 0; i < n; i++) {
    cin >> heights[i];
  }

  stack<int> st;  // stack to store indices
  long long maxArea = 0;

  for (int i = 0; i < n; i++) {
    // While current height is less than height at top of stack
    while (!st.empty() && heights[i] < heights[st.top()]) {
      long long h = heights[st.top()];
      st.pop();

      long long w = st.empty() ? i : i - st.top() - 1;
      maxArea = max(maxArea, h * w);
    }
    st.push(i);
  }

  // Process remaining elements in stack
  while (!st.empty()) {
    long long h = heights[st.top()];
    st.pop();

    long long w = st.empty() ? n : n - st.top() - 1;
    maxArea = max(maxArea, h * w);
  }

  cout << maxArea << endl;
}