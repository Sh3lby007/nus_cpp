#include <iostream>
#include <vector>
using namespace std;

/*
Strings and vectors include the member functions .insert and .
erase . As shown in lecture, they can be fairly complicated
to use because they have to be used in conjunction with the
and .end functions. However, it is not entirely necessary to
depend on these functions to insert and erase ele- ments from
a string/vector. We can always write our own insert and erase
function to suit our needs as such:
*/

/*
vector<int> my_vector = {0, 1, 2, 3, 4, 5};
insert(my_vector, 2, 10);  // inserts into index 2
erase(my_vector, 5);       // removes element at index 5
for (int i = 0; i < my_vector.size(); i++) {
  cout << my_vector[i] << " ";
}
*/
// This will result in an output of 0 1 10 2 3 5.

/*
Provide an implementation for the function insert using only
the member functions .push_back, .pop_back and .size.
*/

void insert(vector<int> &v, int pos, int val) {
  /*
  1. push_back method adds an element to the end of array
  2. Shift element to the right, starting from the last
  element of the original vector
  3. Loop will stop if i < pos e.g i is 1 and pos is 2
  4. Lastly put val param at pos value.
  */
  v.push_back(0);
  for (int i = v.size() - 1; i > pos; i--) {
    v[i] = v[i - 1];
  }
  v[pos] = val;
  /*
Say we have a vector: [10, 20, 30, 40]
And we want to insert 99 at position 1
Step by step:

First, we add a 0 at the end:

[10, 20, 30, 40, 0]

Then we shift elements to the right, starting from the back:

i = 4: Copy 40 right → [10, 20, 30, 40, 40]
i = 3: Copy 30 right → [10, 20, 30, 30, 40]
i = 2: Copy 20 right → [10, 20, 20, 30, 40]
Stop because i = 1 (our insertion position)

Finally, put 99 at position 1:

[10, 99, 20, 30, 40]

Think of it like making space in a row of lockers:

1. First you add an empty locker at the end
2. Then everyone moves their stuff one locker to the right
3. Finally, you put your stuff in the empty spot that was created

The for loop goes backwards (from right to left) because if
we went left to right, we'd overwrite values we still need to move!
  */
}

/*
Provide an implementation for the function erase using only
the member functions .push_back, .pop_back and .size.
*/
void erase(vector<int> &vec, int pos) {
  for (int i = pos + 1; i < vec.size(); i++) {
    vec[i - 1] = vec[i];
  }
  vec.pop_back();
  /*
Say we have a vector: [10, 20, 30, 40, 50]
And we want to erase the element at position 1 (which is 20)
Step by step:

Shift elements to the left:

i = 2: Copy 30 left → [10, 30, 30, 40, 50]
i = 3: Copy 40 left → [10, 30, 40, 40, 50]
i = 4: Copy 50 left → [10, 30, 40, 50, 50]


Pop the last element since it's duplicated:

Final result: [10, 30, 40, 50]

Think of it like removing a book from a shelf:

1. Starting from where you removed the book, slide all books
to the left to fill the gap
2.The last position will have a duplicate book, so you remove it

Notice this solution:

1.Goes left to right (unlike insert which went right to left)
2.Is simpler than insert (no need to make space first)
3.Uses one less operation per element (just shifting left vs
insert which needed shifting right and initial push)
  */
}

/*
The function void mutate takes in a vector of int, and sets
each element to the sum of its neighbours, with the ends wrapping around.
*/

/*
For example
Original:  [0, 1, 2, 3, 4, 5]
Mutate to: [6, 2, 4, 6, 8, 4]
            ↑  ↑  ↑  ↑  ↑  ↑
           1+5 0+2 1+3 2+4 3+5 4+0
Provide an implementation for the function void mutate .
*/
void mutate(vector<int> &vec) {  // MY SOLUTION
  vector<int> next(vec.size());

  int size = vec.size();
  for (int i = 0; i < size; i++) {
    if (i == 0) {  // 1st element of array need to wrap
      next[i] = vec[i + 1] + vec[size - 1];
    } else if (i == size - 1) {  // Last element of array wrap
      next[i] = vec[0] + vec[i - 1];
    } else {  // Other elements dont need wrap
      next[i] = vec[i - 1] + vec[i + 1];
    }
  }
  for (int i = 0; i < size; i++) {
    vec[i] = next[i];
  }
}

void mutateAI(vector<int> &v) {  // AI solution
  // Save original vector since we'll be modifying it
  vector<int> original = v;

  int n = v.size();
  for (int i = 0; i < n; i++) {
    // For each position, get left and right neighbors
    // For left: if i=0, use last element (n-1), else use i-1
    // For right: if i=last (n-1), use first element (0), else use i+1
    int left = (i == 0) ? original[n - 1] : original[i - 1];
    int right = (i == n - 1) ? original[0] : original[i + 1];

    // Set current element to sum of neighbors
    v[i] = left + right;
  }
}