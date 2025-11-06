#include <deque>
#include <iostream>
#include <map>
#include <string>
using namespace std;

// Global data structures
deque<int> numbers;  // stores numbers in order (most recent first)
map<int, int, greater<int>>
    countMap;  // key=value, value=count, sorted descending

void updateTopThree() {
  // countMap is already sorted in descending order
  // No need to do anything - we'll query it when needed
}

void addNumber(int num) {
  numbers.push_front(num);
  countMap[num]++;
}

void removeNumber() {
  if (!numbers.empty()) {
    int removed = numbers.front();
    numbers.pop_front();

    countMap[removed]--;
    if (countMap[removed] == 0) {
      countMap.erase(removed);
    }
  }
}

void queryNumbers() {
  if (numbers.empty()) {
    cout << endl;
    return;
  }

  for (int i = 0; i < numbers.size(); i++) {
    if (i > 0)
      cout << ", ";
    cout << numbers[i];
  }
  cout << endl;
}

void getMax(int k) {
  // Get the k-th largest distinct number (1-indexed)
  if (countMap.size() < k) {
    cout << "None" << endl;
    return;
  }

  auto it = countMap.begin();
  for (int i = 1; i < k; i++) {
    it++;
  }
  cout << it->first << endl;
}

int solution() {
  int n;
  cin >> n;

  // Read n numbers
  for (int i = 0; i < n; i++) {
    int num;
    cin >> num;
    addNumber(num);
  }

  int m;
  cin >> m;
  cin.ignore();  // ignore newline after m

  // Process m commands
  for (int i = 0; i < m; i++) {
    string command;
    getline(cin, command);

    if (command == "QUERY") {
      queryNumbers();
    } else if (command == "REMOVE") {
      removeNumber();
    } else if (command == "MAX") {
      getMax(1);
    } else if (command == "MAX_2") {
      getMax(2);
    } else if (command == "MAX_3") {
      getMax(3);
    }
  }

  return 0;
}