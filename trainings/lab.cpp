#include <iostream>

using namespace std;

/*
Write a function int volume that takes as inputs three
positive integers representing the length, width and height
of a box, and computes and returns the volume of the box.

You may assume that the volume of the box does not exceed the
maximum value representable in the int data type.
*/

int volume(int length, int width, int height) {
  return length * width * height;
}

/*
Alexandra has n candles. He burns them one at a time and
carefully collects all unburnt residual wax. Out of the
residual wax of exactly k (where k > 1) candles, he can roll
out a new candle

Consider the case of n=5, k=3

After burning the first 3 candles, Alexandra has enough
residual wax to roll out the 6th candle. After burning this
new candle with candles 4 and 5, he has enough residual wax
to roll out the 7th candle. Burning the 7th candle would not
result in enough residual wax to roll out anymore new candle.
Therefore, in total he can burn 7 candles.

Implement a function int candles(int n, int k) that takes as
input two positive integers n and k, and returns the total
number of candles that can be burn.
*/

int candles(int n, int k) {
  int count = 0;
  while (n > k) {
    n = n - k;
    n = n + 1;
    count = count + k;
  }
  count = count + n;
  return count;
}

/*
 Define a function double calculatePi( int n ) which returns
 the approximation of π by using n number of terms.
*/

double calculatePi(int nTerms) {
  double pi = 0;
  double denom = 1;
  for (int i = 1; i <= nTerms; i++) {
    double term = 4.0 / denom;
    if (i % 2 == 0) {  // even term
      pi = pi - term;
    } else {  // odd term
      pi = pi + term;
    }
    denom = denom + 2;
  }
  return pi;
}
/*
Starting from 1, each player count out the next integer in
sequence. If the integer is divisible by 7, or contains the
digit 7, say "Up!" instead of the number. Whoever makes a mistake loses.

Implement the function int sevens(int n) which takes in a the
last integer of the sequence to stop at, and returns the
number of seven-ish integers from 1 to n (inclusive).
*/
int sevens(int n) {
  int count = 0;

  for (int i = 1; i <= n; ++i) {
    if (i % 7 == 0) {
      count++;
    } else {
      int num = i;
      while (num > 0) {
        if (num % 10 == 7) {
          count++;
          break;
        }
        num /= 10;
      }
    }
  }
  return count;
}

int main() {
  cout << calculatePi(1) << endl;
  cout << sevens(1000) << endl;
  return 0;
}
