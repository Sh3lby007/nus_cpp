#include <iostream>
#include <vector>
using namespace std;

// PARTITION: Rearrange array around pivot
// Returns: final position of pivot
int partition(vector<int>& arr, int low, int high) {
  int pivot = arr[high];  // Choose last element as pivot
  int i = low - 1;        // i tracks position of last small element

  // Scan through array from low to high-1
  for (int j = low; j < high; j++) {
    // If current element is small (≤ pivot)
    if (arr[j] <= pivot) {
      i++;                   // Move boundary
      swap(arr[i], arr[j]);  // Put small element on left
    }
  }

  // Put pivot in its correct position
  swap(arr[i + 1], arr[high]);
  return i + 1;  // Return pivot's final position
}

// QUICKSELECT: Find K-th smallest element recursively
int quickSelect(vector<int>& arr, int low, int high, int k) {
  // BASE CASE: Only one element left
  if (low == high) {
    return arr[low];
  }

  // PARTITION: Rearrange and get pivot position
  int pivotIndex = partition(arr, low, high);

  // DECISION: Where is K-th element?

  // Case 1: Pivot IS the K-th smallest
  if (pivotIndex == k - 1) {
    return arr[pivotIndex];  // Found it!
  }
  // Case 2: K-th is in LEFT partition
  else if (k - 1 < pivotIndex) {
    return quickSelect(arr, low, pivotIndex - 1, k);
  }
  // Case 3: K-th is in RIGHT partition
  else {
    return quickSelect(arr, pivotIndex + 1, high, k);
  }
}

int main() {
  int n, k;
  cin >> n >> k;

  vector<int> arr(n);
  for (int i = 0; i < n; i++) {
    cin >> arr[i];
  }

  // Call QuickSelect (indices are 0-based, so 0 to n-1)
  int result = quickSelect(arr, 0, n - 1, k);
  cout << result << endl;

  return 0;
}