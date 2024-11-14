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
// Thiswillresultinanoutputof 0 1 10 2 3 5.

/*
Provide an implementation for the function insert using only
the member functions .push_back, .pop_back and .size.
*/

void insert(vector<int> &v, int pos, int val) {
  v.push_back(0);
  for (int i = v.size() - 1; i > pos; i--) {
    v[i] = v[i - 1];
  }
  v[pos] = val;
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
}