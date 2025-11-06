#include <iostream>

#include <vector>

using namespace std;

int solution() {
  int n, k;

  cin >> n >> k;

  vector<int> arr(n);

  for (int i = 0; i < n; i++) {
    cin >> arr[i];
  }

  int left = 0;

  int currentSum = 0;

  int maxLength = 0;

  int bestStart = -1;

  for (int right = 0; right < n; right++) {
    currentSum += arr[right];

    while (currentSum > k && left <= right) {
      currentSum -= arr[left];

      left++;
    }

    if (currentSum == k) {
      int length = right - left + 1;

      if (length > maxLength) {
        maxLength = length;

        bestStart = left;
      }
    }
  }

  if (bestStart == -1) {
    cout << "Unlucky" << endl;

  } else {
    cout << bestStart << endl;
  }

  return 0;
}