#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Structure to hold participant data
struct Participant {
  string name;
  int scoreA;      // First round score
  int scoreB;      // Second round score
  int inputOrder;  // Original input position (for stable sort)
};

// COMPARISON FUNCTION
// Returns true if p1 should come BEFORE p2 in ranking
bool shouldComeBefore(const Participant& p1, const Participant& p2) {
  // 1. Compare by second round score (B) - DESCENDING
  if (p1.scoreB != p2.scoreB) {
    return p1.scoreB > p2.scoreB;  // Higher B comes first
  }

  // 2. If B is tied, compare by first round score (A) - DESCENDING
  if (p1.scoreA != p2.scoreA) {
    return p1.scoreA > p2.scoreA;  // Higher A comes first
  }

  // 3. If both A and B are tied, use input order - ASCENDING
  return p1.inputOrder < p2.inputOrder;  // Earlier input comes first
}

// PARTITION for QuickSort with custom comparison
int partition(vector<Participant>& arr, int low, int high) {
  Participant pivot = arr[high];  // Choose last element as pivot
  int i = low - 1;

  for (int j = low; j < high; j++) {
    // Use custom comparison: if arr[j] should come before pivot
    if (shouldComeBefore(arr[j], pivot)) {
      i++;
      swap(arr[i], arr[j]);
    }
  }

  swap(arr[i + 1], arr[high]);
  return i + 1;
}

// QUICKSORT - Recursive sorting
void quickSort(vector<Participant>& arr, int low, int high) {
  if (low < high) {
    // Partition and get pivot position
    int pivotIndex = partition(arr, low, high);

    // Recursively sort left and right partitions
    quickSort(arr, low, pivotIndex - 1);   // Sort left
    quickSort(arr, pivotIndex + 1, high);  // Sort right
  }
}

int main() {
  int n;
  cin >> n;

  vector<Participant> participants(n);

  // Read input and store with input order
  for (int i = 0; i < n; i++) {
    cin >> participants[i].name >> participants[i].scoreA >>
        participants[i].scoreB;
    participants[i].inputOrder = i;  // Track original position
  }

  // Sort using QuickSort
  quickSort(participants, 0, n - 1);

  // Output the sorted names
  for (int i = 0; i < n; i++) {
    cout << participants[i].name << endl;
  }

  return 0;
}
/**
 *
 * ## **Detailed Walkthrough**

Let's trace through the sample input:

### **Input:**
```
5
Terry 1000 1010  → inputOrder = 0
John  1111 1010  → inputOrder = 1
May   1111 2105  → inputOrder = 2
Jadie 1521 2030  → inputOrder = 3
Pablo 1000 1010  → inputOrder = 4
```

### **How shouldComeBefore Works:**

**Compare Terry vs May:**
```
Terry: A=1000, B=1010, order=0
May:   A=1111, B=2105, order=2

B different? YES (1010 vs 2105)
1010 > 2105? NO
→ Terry does NOT come before May
→ May comes before Terry
```

**Compare Terry vs John:**
```
Terry: A=1000, B=1010, order=0
John:  A=1111, B=1010, order=1

B different? NO (both 1010)
A different? YES (1000 vs 1111)
1000 > 1111? NO
→ Terry does NOT come before John
→ John comes before Terry
```

**Compare Terry vs Pablo:**
```
Terry: A=1000, B=1010, order=0
Pablo: A=1000, B=1010, order=4

B different? NO
A different? NO
inputOrder: 0 < 4? YES
→ Terry comes before Pablo
```

### **After QuickSort:**

The array will be sorted as:
```
[May, Jadie, John, Terry, Pablo]
 */
