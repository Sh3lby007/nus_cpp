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

// Question 2 (3 parts)

/*
Define a function void init_primes(bool primes[], int n) that
takes in the array primes together together with an integer
n, and initialize the representation of all the numbers from
2 to n to be prime. That is to say, since no sieve is
performed yet, we assume all numbers to be primes in the beginning.
*/

void init_primes(bool primes[], int n) {
  /*
  1. We're working with a boolean array where each index represents a number
  2. We want to mark all numbers from 2 to n as prime (true
  3. Index 0 and 1 should be false as they're not prime numbers
  */

  // First set everything to false
  /*
  Alternative solution (more efficient but same result):
  primes[0] = primes[1] = false;  // 0 and 1 are not prime
  */
  for (int i = 0; i <= n; i++) {
    primes[i] = false;
  }

  // Then set all numbers from 2 to n to be true
  for (int i = 2; i <= n; i++) {
    primes[i] = true;
  }
}

/*
Define a function void sieve_primes(bool primes[], int size,
int n) that takes rray primes and two integers max and n, and
performs the sieve as described above with n up to and
including max, i.e., it "crosses out" all multiples of n
*/