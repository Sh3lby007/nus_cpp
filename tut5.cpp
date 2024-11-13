#include <iostream>
using namespace std;
// Question 1: Track the code below

// Code below to initialize the functions first before calling them in main
void printArray(int list[], int numElem);
void passElement(int num);
void changeElements(int list[]);
void copyArray(int list1[], int list2[], int numElem);

int main(void) {
  int list1[5] = {11, 22, 33, 44, 55};
  int list2[5] = {99, 99, 99, 99, 99};
  // print out list 1 in one line
  printArray(list1, 5);
  /*
   passElement function does nothing to change list1 as the
   function just returns and doesnt change the first element value
  */
  passElement(list1[0]);
  // prints out list1 again with the original value
  printArray(list1, 5);
  // Changes the 3rd element value to 77 and 5th element to 88 for list2 array
  changeElements(list2);
  // prints the new value of list2 array 99, 99 , 77, 99, 88
  printArray(list2, 5);
  // list2 array takes on list1 arr values
  copyArray(list2, list1, 5);
  /*
  list2 array at this point has the same values as list1,
  then prints out list1 array values
  */
  printArray(list2, 5);
  return 0;
}

void printArray(int list[], int numElem) {
  int i;
  for (i = 0; i < numElem; i++) cout << list[i] << " ";
  cout << endl;

  return;
}
void passElement(int num) {
  num = 1234;
  return;
}
void changeElements(int list[]) {
  list[2] = 77;
  list[4] = 88;
  return;
}
void copyArray(int list1[], int list2[], int numElem) {
  int i;
  for (i = 0; i < numElem; i++) list1[i] = list2[i];
  return;
}