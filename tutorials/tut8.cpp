#include <ctype.h>
#include <stdio.h>

#include <iostream>
#include <vector>
using namespace std;

/*
Implement the function count(FILE *fp) that returns the number
of alphabatical letters in the file fp.
*/

int countLetter(FILE *fp) {
  /*
  1. Takes a FILE pointer as input
  2. Initializes a counter variable letter_count to 0
  3. Reads the file character by character using fgetc()
  4. Uses isalpha() to check if each character is an alphabetical letter
  5. Increments the counter for each letter found
  6. Returns the total count
  */
  int letter_count = 0;
  int file_char;

  if (fp == NULL) {
    return 0;
  }
  // Read file character by character
  while ((file_char = fgetc(fp)) != EOF) {
    // Check if character is an alphabetical letter using isalpha()
    if (isalpha(file_char)) {
      letter_count++;
    }
  }
  return letter_count;
}

/*
Implement the function count(FILE *fp) that takes as input a
text file and returns the number of words in the file.
*/

int countWords(FILE *fp) {
  /*
1. Takes a FILE pointer as input
2. Initializes a counter variable word_count to 0
3. Uses a flag in_word to keep track of whether we're
currently in a word
4. Reads the file character by character using fgetc()
5. For each character:
- If it's whitespace and we were in a word, mark that we're
no longer in a word
- If it's not whitespace and we weren't in a word, increment
word count and mark that we're now in a word
6. Returns the total count
  */
  int word_count = 0;
  int c;
  int in_word = 0;

  if (fp == NULL) {
    return 0;
  }

  while ((c = fgetc(fp)) != EOF) {
    if (isspace(c)) {
      if (in_word) {
        in_word = 0;
      }
    } else {
      if (!in_word) {
        word_count++;
        in_word = 1;
      }
    }
  }
  return word_count;
}
/*
Implement the function count(FILE *fp) that takes as input a
text file and returns the number of sentences in the file.
*/
int countSentence(FILE *fp) {
  /*
1. Takes a FILE pointer as input
2. Initializes a counter variable sentence_count to 0
3. Reads the file character by character using fgetc()
4. Increments the counter whenever it finds a period ('.')
5. Returns the total count
  */
  int sentence_count = 0;
  int c;

  if (fp == NULL) return 0;

  while ((c = fgetc(fp)) != EOF) {
    if (c == '.') {
      sentence_count++;
    }
  }
  return sentence_count;
}

/*
Implement the function to_upper(FILE *in, FILE *out) that
copies the text from in to out, while changing all lowercase
letters to uppercase.
*/

void to_upper(FILE *in, FILE *out) {
  int c;
  if (in == NULL || out == NULL) return;

  // Read input file character by character
  while ((c = fgetc(in)) != EOF) {
    // Convert lowercase to uppercase using toupper()
    // Non-lowercase chars remain unchanged
    fputc(toupper(c), out);
  }
}

int main() {
  // fopen returns file point or NULL if error
  FILE *fp = fopen("pop.txt", "r");  // "r" open for reading
  if (fp != NULL) {
    int letters = countLetter(fp);
    /*
    After calling countLetter function, the file pointer has
    reached the end of file, when countWords is called, it's
    starting from the end of the file, so when we printf the
    words variable, itvdoesnt find any words and return 0.
    */
    rewind(fp);  // Sets pointer to beginning
    int words = countWords(fp);
    rewind(fp);
    int sentences = countSentence(fp);
    printf("Number of letters: %d\n", letters);
    printf("Number of words: %d\n", words);
    printf("Number of sentences: %d\n", sentences);
    fclose(fp);  // Closes the file, return 0 on success, return EOF if error
    /*
    Why do we need to explicitly close a file?
     ̶ Flush contents from buffer.Written content might be
     cached in a buffer.
      ̶ Memory leak. fp is still in use by the program. Might
      run out of file pointers.
    */
  }

  FILE *input = fopen("pop.txt", "r");
  if (input != NULL) {
    to_upper(input, stdout);
    fclose(input);
  }
}