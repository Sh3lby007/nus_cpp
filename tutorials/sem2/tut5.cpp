#include <cstdio>
#include <iostream>
#include <map>

using namespace std;

struct NUSModule {
  string moduleCode;
  int credits;
  string grade;
  bool isSU;
};

void make_module(NUSModule& module, string code, int credits, string grade) {
  module.moduleCode = code;
  module.credits = credits;
  module.grade = grade;
  module.isSU = false;
}

void set_su(NUSModule& module, bool su) {
  module.isSU = su;
}

int credits_obtained(const vector<NUSModule>& modules) {
  int credits = 0;
  for (int i = 0; i < modules.size(); i++) {
    if (modules[i].grade == "F") {
      continue;
    }
    if (modules[i].isSU &&
        (modules[i].grade == "D+" || modules[i].grade == "D")) {
      continue;
    }
    credits += modules[i].credits;
  }
  return credits;
}

double calculate_cap(const vector<NUSModule>& modules,
                     const map<string, double>& points) {
  double totalCap = 0;
  double totalCredits = 0;
  for (int i = 0; i < modules.size(); i++) {
    if (modules[i].isSU) {
      continue;
    }
    totalCap += points.at(modules[i].grade) * modules[i].credits;
    totalCredits += modules[i].credits;
  }
  return totalCap / totalCredits;
}

template <typename K, typename T>
vector<K> get_keys(map<K, T> m) {
  vector<K> keyVector;
  for (const auto& pair : m) {
    keyVector.push_back(pair.first);
  }
  return keyVector;
}

template <typename K, typename T>
vector<T> get_values(map<K, T> m) {
  vector<T> valueVector;
  for (const auto& pair : m) {
    valueVector.push_back(pair.second);
  }
  return valueVector;
}

int main() {
  // Test for NUSModule functions
  NUSModule tic1001, tic1101, tba2102, tic2301, tic1231;

  // Create grade to points mapping
  map<string, double> grade2points = {{"A+", 5.0}, {"A", 5.0}, {"A-", 4.5},
                                      {"B+", 4.0}, {"B", 3.5}, {"B-", 3.0},
                                      {"C+", 2.5}, {"C", 2.0}, {"D+", 1.5},
                                      {"D", 1.0},  {"F", 0.0}};

  // Initialize modules
  make_module(tic1001, "TIC1001", 4, "A");
  make_module(tic1101, "TIC1101", 4, "B-");
  make_module(tba2102, "TBA2102", 3, "C");
  set_su(tba2102, true);
  make_module(tic2301, "TIC2301", 4, "D");
  set_su(tic2301, true);
  make_module(tic1231, "TIC1231", 2, "F");

  // Create modules vector
  vector<NUSModule> modules = {tic1001, tic1101, tba2102, tic2301, tic1231};

  // Test credits_obtained
  int total_credits = credits_obtained(modules);
  cout << "Total credits obtained: " << total_credits << endl;
  cout << "Expected: 11" << endl;

  // Test calculate_cap
  double cap = calculate_cap(modules, grade2points);
  cout << "CAP: " << cap << endl;
  cout << "Expected: 3.200000" << endl;

  // Test get_keys and get_values
  cout << "\nTesting get_keys and get_values:" << endl;

  // Create a test map
  map<string, int> testMap = {{"apple", 5}, {"banana", 3}, {"cherry", 10}};

  // Test get_keys
  vector<string> keys = get_keys(testMap);
  cout << "Keys: ";
  for (const auto& key : keys) {
    cout << key << " ";
  }
  cout << endl;

  // Test get_values
  vector<int> values = get_values(testMap);
  cout << "Values: ";
  for (const auto& value : values) {
    cout << value << " ";
  }
  cout << endl;

  return 0;
}