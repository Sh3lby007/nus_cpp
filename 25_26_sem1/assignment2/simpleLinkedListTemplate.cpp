#pragma once

#ifndef SIMPLELINKEDLISTTEMPLATEHPP
#define SIMPLELINKEDLISTTEMPLATEHPP

#include "simpleLinkedListTemplate.h"
#include <iostream>
using namespace std;

template <class T>
ListNode<T>::ListNode(T n) {
  _item = n;
  _next = NULL;
}

template <class T>
void List<T>::insertHead(T n) {
  ListNode<T>* aNewNode = new ListNode<T>(n);
  aNewNode->_next = _head;
  _head = aNewNode;
  _size++;
};

template <class T>
void List<T>::removeHead() {
  if (_size > 0) {
    ListNode<T>* temp = _head;
    _head = _head->_next;
    delete temp;
    _size--;
  }
}

template <class T>
void List<T>::print(bool withNL) {
  ListNode<T>* temp = _head;
  while (temp) {
    cout << temp->_item;
    if (withNL)
      cout << endl;
    else
      cout << " ";
    temp = temp->_next;
  }
  cout << endl;
}

template <class T>

bool List<T>::exist(T n)

{
  ListNode<T>* current = _head;

  // Traverse the list

  while (current != NULL) {
    if (current->_item == n) {
      return true;
    }

    current = current->_next;
  }

  return false;
}

template <class T>

T List<T>::extractMin()

{
  // modify this

  // if there are duplicates minimas in the list, return the leftmost one (the
  // one closest to the _head)

  if (_size == 0) {
    return T();
  }

  ListNode<T>* minNode = _head;

  ListNode<T>* prevMinNode = NULL;

  ListNode<T>* current = _head->_next;

  ListNode<T>* prev = _head;

  while (current != NULL) {
    if (current->_item < minNode->_item) {
      minNode = current;

      prevMinNode = prev;
    }

    prev = current;

    current = current->_next;
  }

  T minItem = minNode->_item;

  if (prevMinNode == NULL) {
    _head = _head->_next;

  } else {
    prevMinNode->_next = minNode->_next;
  }

  delete minNode;

  _size--;

  return minItem;
}

template <class T>

void List<T>::reverseOp()

{
  // modify this

  if (_size <= 1) {
    return;
  }

  ListNode<T>* prev = NULL;

  ListNode<T>* current = _head;

  ListNode<T>* next = NULL;

  while (current != NULL) {
    next = current->_next;

    current->_next = prev;

    prev = current;

    current = next;
  }

  _head = prev;
}

// You may define any further functions for the List class below.

// Remember to modify the List class above accordingly
#endif
