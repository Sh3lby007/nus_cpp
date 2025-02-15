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
int n) that takes array primes and two integers max and n, and
performs the sieve as described above with n up to and
including max, i.e., it "crosses out" all multiples of n
*/
void sieve_primes(bool primes[], int size, int n) {
  /*
  Purpose is to turn multiples of n to false
  1. Starts from n*2 (first multiple after n)
  2. Marks each multiple as not prime (false)
  3. Keeps going until reaching size
  4. Increments by n each time (to get next multiple)
  */
  for (int multiple = n * 2; multiple <= size; multiple += n) {
    cout << "multiple value:" << multiple << endl;
    primes[multiple] = false;
  }
}

/*
Define the function print_primes(int n) which takes in an
integer n (n > 1) and prints a list of prime numbers from 2
to n inclusive. Within this function, you should declare a
boolean array primes that is suitably sized to accommodate
numbers up to and including the input n, and use the
above-defined functions to achieve the task.

For example, calling print_primes(50) will result in the output:
2 3 5 7 11 13 17 19 23 29 31 37 41 43 47
*/

void print_primes(int n) {
  // Declare bool array primes to accomodate numbers up to n
  bool primes[n + 1];
  // initialize all numbers as potentially prime:
  init_primes(primes, n);

  /*
   Apply sieve for each number from 2 to sqrt(n). We only
   need to go up to sqrt(n) because any larger factors would
   have been caught by smaller factors already
  */
  for (int i = 2; i * i <= n; i++) {
    if (primes[i] == true) {
      sieve_primes(primes, n, i);
    }
  }

  for (int i = 2; i <= n; i++) {
    if (primes[i] == true) {
      cout << i << " ";
    }
  }

  /*
  Use n+1 size array to include number n
  Only need to sieve up to sqrt(n)
  Only sieve if the number is still marked as prime
  Print only the numbers still marked as true
  */
}

/*
Your task is to write a function game_of_life(bool cells[]
int size, int num_gen), which takes as inputs an array cells
of length size representing the row of cells, and the number
of generations to play. The function will print the output of
each generation from 1 to n using underscore (_) as blank and
X as a cell.
*/

void game_of_life(bool cells[], int size, int num_gen) {
  /*
  Rules:
  1. Live cell (X) → Dies in next generation
  2. Dead cell (_) → Becomes alive if exactly ONE neighbor is alive
  3. Need to print each generation
  4. Cells wrap around (edges connect)

  A. We need:
   - Print current generation
   - Calculate next generation based on rules
   - Store next generation
   - Repeat for num_gen times

B. Functions needed:
   - print_generation (for neat output)
   - calculate_next_gen (for rules logic)
  */

  bool next[size];  // temp array for next generation

  // 1. Print current state with correct formatting
  for (int gen = 1; gen < num_gen; gen++) {
    for (int i = 0; i < size; i++) {
      printf("%c", cells[i] ? 'X' : '_');
    }
    printf("\n");
  }

  // 2. Calculate next generation
  for (int i = 0; i < size; i++) {
    /*
    i == 0 is a condition, which checks if its the first
    position of the cells array, if true then wrap to last
    element, hence 15 - 1 = 14 is the last array element. If
    not the first element, take previous position for e.g.
    i = 1, left value will be the first element as 1 - 1 = 0
    which accesses the first element
    */
    int left = (i == 0) ? cells[size - 1] : cells[i - 1];
    /*
    i == size - 1 is a condition, which checks if its the last
    position of the cells array, if true then wrap to first
    element, hence cells[0] which acceses the first array element. If not the
    last element, take next position for e.g. i = 1, right value will be the 3rd
    element as 1 + 1 = 2, cells[2] which accesses the 3rd element
    */
    int right = (i == size - 1) ? cells[0] : cells[i + 1];
    /*
    Since value of left or right will either be 0(false) or
    1(true), hence can store count of alive neighbours
    */
    int live_neighbours = left + right;

    /* Rules recap:
    Rule 1: If cell is alive (X/1), it dies
    Rule 2: If cell is dead (_/0) and has exactly ONE live
    neighbor, it becomes alive
    */
    if (cells[i]) {     // Cell is currently alive
      next[i] = false;  // live cell dies
    } else {            // Cell is currently dead
      // Becomes alive only if exactly 1 neighbour
      next[i] = (live_neighbours == 1);
    }
  }

  /* Crucial Part
  We need to copy next back to cells so we can:
  1. Print the new state correctly
  2. Use it to calculate the next generation
  */
  for (int i = 0; i < size; i++) {
    cells[i] = next[i];
  }
}