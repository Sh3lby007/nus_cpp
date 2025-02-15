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

void to_upper_all(FILE *in, FILE *out) {
  int c;
  if (in == NULL || out == NULL) return;

  // Read input file character by character
  while ((c = fgetc(in)) != EOF) {
    // Convert lowercase to uppercase using toupper()
    // Non-lowercase chars remain unchanged
    fputc(toupper(c), out);
  }
}
/*
Implement the function to_upper(FILE *in, FILE *out) that
copies the text from in to out, while capitalising the first
letter of each word.
*/
void to_upper_first(FILE *in, FILE *out) {
  int c;
  int is_start_of_word = 1;  // Start the first word with a capital

  // Check if file pointers are valid
  if (in == NULL || out == NULL) {
    return;
  }

  // Read input file character by character
  while ((c = fgetc(in)) != EOF) {
    // If it's a whitespace character, next non-whitespace will be start of word
    if (isspace(c)) {
      is_start_of_word = 1;
      fputc(c, out);  // Write the whitespace unchanged
    }
    // If it's not a whitespace character
    else {
      if (is_start_of_word && isalpha(c)) {
        // Capitalize first letter of word
        fputc(toupper(c), out);
      } else {
        // Keep other characters unchanged
        fputc(c, out);
      }
      is_start_of_word = 0;  // No longer at start of word
    }
  }
}
/*
Implement the function reverse(FILE *in, FILE *out) that
takes a text file and outputs the reverse of each line to
out. You may assume the lines are no more than 500 characters long.
*/
void reverse(FILE *in, FILE *out) {
  char line[501];  // 500 chars + 1 for null terminator
  int i, len;

  // Check if file pointers are valid
  if (in == NULL || out == NULL) {
    return;
  }

  // Read the file line by line
  while (fgets(line, sizeof(line), in) != NULL) {
    // Find length of the line
    len = strlen(line);

    // If last character is newline, handle it separately
    int has_newline = 0;
    if (len > 0 && line[len - 1] == '\n') {
      has_newline = 1;
      len--;  // Don't include newline in reversal
    }

    // Write characters in reverse order
    for (i = len - 1; i >= 0; i--) {
      fputc(line[i], out);
    }

    // Add back the newline if it was present
    if (has_newline) {
      fputc('\n', out);
    }
  }
}

/*
Implement the function to_upper(FILE *in, FILE *out) that
takes in a text file and outputs the file with the first
letter of each sentence captialised.
*/
void to_upper(FILE *in, FILE *out) {
  int c;
  int next;
  int capitalize_next_letter = 1;

  // Check if file pointers are valid
  if (in == NULL || out == NULL) {
    return;
  }

  // Read file character by character
  while ((c = fgetc(in)) != EOF) {
    if (isalpha(c) && capitalize_next_letter) {
      // Only capitalize lowercase letters
      if (islower(c)) {
        c = toupper(c);
      }
      capitalize_next_letter = 0;
    }

    fputc(c, out);

    if (c == '.') {
      // Look ahead for the next non-whitespace character
      while ((next = fgetc(in)) != EOF && isspace(next)) {
        fputc(next, out);
      }
      if (next != EOF) {
        // Push back the non-whitespace character we found
        ungetc(next, in);
      }
      capitalize_next_letter = 1;
    }
  }
}
/*
Implement the function interleave(FILE *in1, FILE *in2, FILE *out)
that takes in two text files and interleave the lines to the out file.
*/

void interleave(FILE *in1, FILE *in2, FILE *out) {
  char line1[501], line2[501];  // 500 chars + 1 for null terminator
  int in1_has_line, in2_has_line;

  // Check if file pointers are valid
  if (in1 == NULL || in2 == NULL || out == NULL) {
    return;
  }

  // Read and write lines alternately until both files are exhausted
  while (1) {
    // Try to read a line from each file
    in1_has_line = (fgets(line1, sizeof(line1), in1) != NULL);
    in2_has_line = (fgets(line2, sizeof(line2), in2) != NULL);

    // If both files are exhausted, exit
    if (!in1_has_line && !in2_has_line) {
      break;
    }

    // Write line from first file if available
    if (in1_has_line) {
      fputs(line1, out);
    }

    // Write line from second file if available
    if (in2_has_line) {
      fputs(line2, out);
    }
  }
}

/*
Implement a function copy(FILE *in, FILE *out) that copy the
contents of in to out.
*/

void copy(FILE *in, FILE *out) {
  int c;

  // Check if file pointers are valid
  if (in == NULL || out == NULL) {
    return;
  }

  // Read and write character by character
  while ((c = fgetc(in)) != EOF) {
    fputc(c, out);
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
    // to_upper_all(input, stdout);
    // rewind(input);
    // to_upper_first(input, stdout);
    // rewind(input);
    reverse(input, stdout);
    fclose(input);
  }
}