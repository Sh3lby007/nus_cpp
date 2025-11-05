#include "simpleIntLinkedList.h"
#include <iostream>
using namespace std;

ListNode::ListNode(int n) {
  _item = n;
  _next = NULL;
}

List::~List() {
  while (_size != 0) {
    removeHead();
  }
};

/*
Returns the value of the current head of this List.
Pre-conditions: List is not empty <<Meta: Otherwise the value returned is
invalid>> Post-conditions: None
*/
int List::headItem() {
  if (_head != NULL) {
    return _head->_item;
  } else {
    return 0;
  }
}

/*
Inserts the value n as the new head of this List.
Pre-conditions: None
Post-conditions: None <<Meta: Apart from the trivial one, which can be omitted>>
*/
void List::insertHead(int n) {
  ListNode* aNewNode = new ListNode(n);
  aNewNode->_next = _head;
  _head = aNewNode;
  _size++;
};

/*
Deletes the current head of this List.
Pre-conditions: List is not empty
Post-conditions: None
*/
void List::removeHead() {
  if (_size > 0) {
    ListNode* temp = _head;
    _head = _head->_next;
    delete temp;
    _size--;
  }
}

/*
Deletes the current tail of this List.
Pre-conditions: List is not empty
Post-conditions: None
*/
void List::removeTail() {
  if (_size > 0) {
    ListNode *prev = NULL, *temp = _head;
    while (temp->_next != NULL) {
      prev = temp;
      temp = temp->_next;
    }
    if (prev != NULL) {
      prev->_next = NULL;
    }
    delete temp;
    _size--;
  }
}

/*
<<Write your comments here, using the same format as above functions>>
Pre-conditions:
Post-conditions:
*/
int List::tailItem() {
  if (_head == nullptr) {
    return 0;  // or throw an exception
  }
  ListNode* current = _head;
  while (current->_next != nullptr) {
    current = current->_next;
  }
  return current->_item;
}

/*
write comments here
*/
void List::insertTail(int n) {
  ListNode* newNode = new ListNode(n);
  if (_head == nullptr) {
    _head = newNode;
    return;
  }
  ListNode* current = _head;
  while (current->_next != nullptr) {
    current = current->_next;
  }
  current->_next = newNode;
}

/*
write comments here
*/
bool List::isEmpty() {
  return _head == nullptr;
}

/*
write comments here
*/
int List::count(int n) {
  int count = 0;
  ListNode* current = _head;
  while (current != nullptr) {
    if (current->_item == n) {
      count++;
    }
    current = current->_next;
  }
  return count;
}

/*
write comments here
*/
int List::alternatingSum() {
  int sum = 0;
  int position = 0;
  ListNode* current = _head;
  while (current != nullptr) {
    if (position % 2 == 0) {
      sum += current->_item;
    } else {
      sum -= current->_item;
    }
    current = current->_next;
    position++;
  }
  return sum;
}
