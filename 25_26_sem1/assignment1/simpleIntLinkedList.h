#pragma once

class ListNode {
 private:
  int _item;
  ListNode* _next;

 public:
  ListNode(int);
  int content() { return _item; };
  friend class List;
};

class List {
 private:
  int _size;
  ListNode* _head;

 public:
  List() {
    _size = 0;
    _head = nullptr;
  };

  ~List();
  int headItem();
  void insertHead(int);
  void removeHead();
  int tailItem();
  void insertTail(int);
  void removeTail();
  bool isEmpty();
  int count(int);
  int alternatingSum();
};
