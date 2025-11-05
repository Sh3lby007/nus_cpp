#include <iostream>
using namespace std;

// Node structure - each "stamp" in the collection
struct Node {
  int data;    // The stamp number
  Node* next;  // Pointer to the next stamp

  Node(int val) : data(val), next(nullptr) {}
};

// Linked List class
class LinkedList {
 private:
  Node* head;  // Points to the first node

 public:
  LinkedList() : head(nullptr) {}

  // Add a stamp to the end of the list
  void append(int value) {
    Node* newNode = new Node(value);

    // If list is empty, new node becomes head
    if (head == nullptr) {
      head = newNode;
      return;
    }

    // Otherwise, traverse to the end and add
    Node* current = head;
    while (current->next != nullptr) {
      current = current->next;
    }
    current->next = newNode;
  }

  // Remove duplicates and return statistics
  void removeDuplicates(int& total_duplicates, int& distinct_with_duplicates) {
    total_duplicates = 0;
    distinct_with_duplicates = 0;

    // If list is empty or has only one node, nothing to do
    if (head == nullptr || head->next == nullptr) {
      return;
    }

    Node* current = head;

    // Traverse the list
    while (current != nullptr && current->next != nullptr) {
      int duplicates_of_current = 0;

      // Check if next node has the same value
      while (current->next != nullptr && current->data == current->next->data) {
        // Found a duplicate!
        Node* duplicate = current->next;
        current->next = duplicate->next;  // Bypass the duplicate node
        delete duplicate;                 // Free memory

        duplicates_of_current++;
        total_duplicates++;
      }

      // If we found any duplicates for this value
      if (duplicates_of_current > 0) {
        distinct_with_duplicates++;
      }

      // Move to next unique value
      current = current->next;
    }
  }

  // Print all stamps
  void print() {
    Node* current = head;
    bool first = true;

    while (current != nullptr) {
      if (!first)
        cout << " ";
      cout << current->data;
      first = false;
      current = current->next;
    }
    cout << endl;
  }

  // Destructor to free memory
  ~LinkedList() {
    Node* current = head;
    while (current != nullptr) {
      Node* next = current->next;
      delete current;
      current = next;
    }
  }
};

int main() {
  int n;
  cin >> n;

  LinkedList list;

  // Build the linked list
  for (int i = 0; i < n; i++) {
    int stamp;
    cin >> stamp;
    list.append(stamp);
  }

  // Remove duplicates and get statistics
  int total_duplicates = 0;
  int distinct_with_duplicates = 0;
  list.removeDuplicates(total_duplicates, distinct_with_duplicates);

  // Output results
  list.print();                      // Line 1: Unique stamps
  cout << total_duplicates << endl;  // Line 2: Total duplicates removed
  cout << distinct_with_duplicates
       << endl;  // Line 3: Distinct values with duplicates

  return 0;
}