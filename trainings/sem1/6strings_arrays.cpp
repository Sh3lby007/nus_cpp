#include <iostream>
/*
Uncle Soo thinks he does not need to explicitly pass in the
size of the array into the function because he can use sizeof
to find the size of the array.He wrote some code to test out his idea:
*/

/*
1. When arrays are passed to functions, they "decay" into pointers
2. int arr[] = int* arr whereby only the address is passed
3. Hence we cant use sizeof to find array length in a function
4. We need to explicitly pass the array size as a paramter
*/
// void test(int arr[]) { printf("%lu", sizeof(arr)); }
void test(int* arr, int size) {
  /*
  Since arr decayed to a pointer, the size of a pointer is
  usually 8 bytes on a 64 bit system and 4bytes on a 32 bit system
  */
  printf("size of arr: %lu\n", sizeof(arr));
  printf("test size: %d\n", size);
}

/*
 Write a function sum_int which takes an array of integers
 and its size, and returns the sum of all its elements.
*/
int sum_int(int arr[], int size) {
  // printf("pointer arr print: %p\n", arr);
  int sum = 0;
  for (int i = 0; i < size; i++) {
    // printf("each element of arr:%d\n", arr[i]);
    sum += arr[i];
  }
  return sum;
}

/*
Write a function max that takes in an array of int and its
size, and returns the maximum value found in the array.
*/
int max(int arr[], int size) {
  int max_value = 0;
  for (int i = 0; i < size; i++) {
    if (arr[i] > max_value) {
      max_value = arr[i];
    }
  }
  return max_value;
}

/*
Write a function to_int which takes in a string of digits
(the characters are all '0' - '9') and returns the number
represented in the string as an int type. Hint: What is the
ASCII code for character '0'?
*/

int to_int(char str[]) {
  int result = 0;
  int i = 0;
  /*
  ASCII of '0' is 48, use that to convert each digit char to
  its numeric value by subtracting '0' which if the char is
  '1', it will be 49 - 48 which then becomes int type 1.
  To properly show number in base 10, we then have to multiply
  by 10 and continue down the next char.
  */
  while (str[i] != '\0') {
    result = result * 10 + (str[i] - '0');
    printf("each char arr value: %c\n", str[i]);
    // printf("result value %d\n", result);
    i++;
  }
  return result;
}
/*
Write a function to_upper that takes as input a string, and
converts all its lowercase characters to uppercase.
Hint: The ASCII table might help.
*/
// ASCII values for lower case alphabets (a-z):97 - 122
// ASCII values for upper case alphabets (A-Z):65 - 92
// Difference between upper and lower case = 97 - 65 = 32!
void to_upper(char str[]) {
  /*
  1. Check if char is lowercase between a to z
  2. if yes, subtract 32 to make it uppercase
  3. if no, leave it unchanged
  */
  int i = 0;
  while (str[i] != '\0') {
    if (str[i] >= 'a' && str[i] <= 'z') {
      str[i] = str[i] - 32;
    }
    i++;
  }
}
/*
Write a function num_words that takes in a sentence as a
string, and returns the number of words in the sentence. You
may assume that the words are separated by exactly one space
and the sentence does not begin or end with a space. Note:
const char is required in the function parameter to allow us
to pass string literals into the function.
*/

int num_words(const char str[]) {
  int count = 1;  // Starts at 1 because words = spaces + 1
  int i = 0;

  // Handle empty string
  if (str[0] == '\0') {
    return 0;
  }

  while (str[i] != '\0') {
    if (str[i] == ' ') {
      count++;
    }
    i++;
  }
  return count;
}

int main(void) {
  /*
  1. Since arr[0] is a long integer, it is 8 bytes of 64-bit
  and 4 bytes of 32 bit systems, so the size will either be
  4 or 8
  2. For consecutive elements in the array, the difference
  between them will therefore be sizeof(long) either 4 or 8
  3. %d is used for printing size, %p is used for printing pointers
  */
  long arr[10];
  printf("%d %p %p\n", (int)sizeof(arr[0]), &arr[0], &arr[1]);

  /*
  1. x is an array of 10 integers, sizeof(x) will be 10 times of sizeof(int)
  which is usually 4 on a 64 bit system,
  */
  int x[10] = {0};
  printf("size of x in main: %lu\n", sizeof(x));
  test(x, sizeof(x));

  int sumArr[] = {1, 2, 3, 4, 5};
  //   printf("%d\n", sumArr[0]);
  sum_int(sumArr, 5);

  int numbers[5] = {3, 7, 2, 9, 1};
  int result = max(numbers, sizeof(numbers));  // result = 9
  printf("max number in numbers arr: %d\n", result);

  char charInt[] = "12345";
  int toInt = to_int(charInt);
  printf("string to int: %d\n", toInt);

  char text[] = "Hello World 123!";
  to_upper(text);
  printf("to_upper function: %s\n", text);

  printf("number of words: %d\n", num_words("Lorem ipsum dolor sit amet."));
  return 0;
}