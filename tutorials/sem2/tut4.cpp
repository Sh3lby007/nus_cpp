#include <cstdio>
#include <iostream>

using namespace std;

/******************************************
Task 1.
******************************************/

bool isPrime(int num) {
  if (num < 2) return false;
  if (num == 2) return true;
  if (num % 2 == 0) return false;

  for (int i = 3; i * i <= num; i += 2) {
    if (num % i == 0) return false;
  }
  return true;
}

int linearSearch(int a[], int N, int X) {
  int idxOfX = -1, i;

  for (i = 0; (i < N) && (idxOfX == -1); i++) {
    if (a[i] == X) idxOfX = i;
    // if ((a[i] % 7) == 0) idxOfX = i; look for the first number divisible by 7
    // if (isPrime(a[i])) idxOfX = i; look for the first prime number
  }

  return idxOfX;
}

/******************************************
Task 2.
******************************************/

struct SResult {
  string studentID;  // student id is a string with "A1234" format
  int score;         // score received by students
};

void counting_sort(int score[], int N, int final[]) {
  // Note: For clarity, we use both freq[] and cfreq[]
  //       They can be combined, i.e. only 1 array if you want
  int freq[11] = {0}, cfreq[11] = {0};
  int i, curScore;

  // 1. Compute Frquency
  for (i = 0; i < N; i++) {
    freq[score[i]]++;
  }

  // 2. Compute Cumulative Frequency
  cfreq[0] = freq[0];
  for (i = 1; i < 11; i++) {
    cfreq[i] = cfreq[i - 1] + freq[i];
  }

  // 3. Produce Final Position
  for (i = 0; i < N; i++) {
    // Note the next two lines can be combined as:
    //  final[ cfreq[ score[i] ] - 1 ] = score[i];
    curScore = score[i];
    final[cfreq[curScore] - 1] = curScore;
    cfreq[curScore]--;
  }
}

void counting_sort_new(SResult input[], int N, SResult final[]) {
  int freq[11] = {0}, cfreq[11] = {0};
  int i;

  // Let's track with this example:
  // input = [{"A1001", 7}, {"A1002", 3}, {"A1003", 7}, {"A1004", 5}]

  // 1. Compute Frequency
  for (i = 0; i < N; i++) {
    freq[input[i].score]++;
  }
  // After step 1:
  // freq[3] = 1 (one student with score 3)
  // freq[5] = 1 (one student with score 5)
  // freq[7] = 2 (two students with score 7)

  // 2. Compute Cumulative Frequency
  cfreq[0] = freq[0];
  for (i = 1; i < 11; i++) {
    cfreq[i] = cfreq[i - 1] + freq[i];
  }
  // After step 2:
  // cfreq[3] = 1 (1 student has score ≤ 3)
  // cfreq[5] = 2 (2 students have score ≤ 5)
  // cfreq[7] = 4 (4 students have score ≤ 7)

  // 3. Produce Final Position
  for (i = N - 1; i >= 0; i--) {  // Note: going backwards for stability
    final[cfreq[input[i].score] - 1] = input[i];
    cfreq[input[i].score]--;
  }
  // Final positions filled from right to left:
  // ["A1002: 3", "A1004: 5", "A1001: 7", "A1003: 7"]
}

void counting_sort_stable(SResult scoreArr[], int N, SResult final[]) {
  // Initialize frequency and cumulative frequency arrays for scores 0-10
  int freq[11] = {0}, cfreq[11] = {0};
  int i;

  // Step 1: Count frequency of each score
  for (i = 0; i < N; i++) {
    freq[scoreArr[i].score]++;
  }

  // Step 2: Calculate cumulative frequency
  cfreq[0] = freq[0];
  for (i = 1; i < 11; i++) {
    cfreq[i] = cfreq[i - 1] + freq[i];
  }

  // Step 3: Place elements in final array
  // Important: Go from right to left to maintain stability
  for (i = N - 1; i >= 0; i--) {
    // Get current score and place the entire record
    int curScore = scoreArr[i].score;
    final[cfreq[curScore] - 1] = scoreArr[i];
    cfreq[curScore]--;
  }
}
int main() {
  // Task 1
  int array[] = {100, 42, 38, 72, 19, -7, 2, 14, 77, 89};

  //   For normal linear search
  int target;
  cout << "Target = ";
  cin >> target;
  cout << "Index (-1 == not found) is ";
  cout << linearSearch(array, 10, target) << endl;

  // Used for finding first prime in array, remove last param of function
  // cout << linearSearch(array, 10) << endl;

  // Task 2

  int sample[] = {10, 5, 7, 3, 5, 7, 7, 9, 2, 5, 7, 3};
  int sorted[12] = {0};
  int i;

  counting_sort(sample, 12, sorted);

  for (i = 0; i < 12; i++) {
    cout << sorted[i] << " ";
  }
  cout << endl;
  return 0;
}
