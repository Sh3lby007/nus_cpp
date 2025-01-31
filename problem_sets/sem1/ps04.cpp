#include <iostream>
#include <string>
#include <vector>

using namespace std;

//--------//
// TASK 1 //
//--------//

char shift_char(char c, int n) {
  // If not an alphabet, return unchanged
  if (!isalpha(c)) {
    return c;
  }
  /*
  1. This checks if the character is uppercase using the isupper() function
  2. Stores this information in isUpper to remember for later
  3. We need this because we want to return the same case we received
  */
  bool isUpper = isupper(c);

  /*
  1. If isUpper is true, base = 'A' (ASCII value 65)
  2. If isUpper is false, base = 'a' (ASCII value 97)
  3. This helps us work with the right part of the ASCII table
  */
  char base = isUpper ? 'A' : 'a';
  // Converting letter to number (0-25):
  /*
  1. First tolower(c) converts any uppercase to lowercase
  2. Then we subtract 'a' to get position in alphabet
  Example:
  If c is 'C', tolower(c) gives 'c'
  'c' - 'a' = 2 (because 'c' is third letter)
  So 'c' becomes position 2
  */
  int position = tolower(c) - 'a';
  /*
  Handles n value more than 26
  First line: n % 26
  If n = 27, becomes 1
  If n = -27, becomes -1
  */
  n = n % 26;
  /*
  Add current position and shift
  Add 26 to handle negative numbers
  % 26 to wrap around alphabet
  Example:

  If we have 'z' (position 25) and shift 1:
  25 + 1 + 26 = 52
  52 % 26 = 0 (wraps to 'a')
  */
  position = (position + n + 26) % 26;
  // Converting back to character:
  // cout << "position value: " << position << endl;
  // cout << "base value: " << base << endl;
  return base + position;
}

string &rotate(string &s, int n) {
  int len = s.length();

  // Handle empty string and no rotation cases
  if (len == 0 || n == 0) {
    return s;
  }

  // Normalize n to be within string length
  n = n % len;  // get remainder
  if (n < 0) {  // if negative
    n += len;   // make positive
  }

  // Perform rotation
  string temp = s;
  for (int i = 0; i < len; i++) {
    s[i] = temp[(i + n) % len];
  }

  return s;
}

//--------//
// TASK 2 //
//--------//

string &caeser(string &s, int n) {
  // For each character in the string
  for (int i = 0; i < s.length(); i++) {
    // Use shift_char from Task 1 which handles all our requirements:
    // - Case preservation
    // - Non-letter preservation
    // - Alphabet wrapping
    s[i] = shift_char(s[i], n);
  }
  return s;
}

//--------//
// TASK 3 //
//--------//

string &substitute(string &s, const string key) {
  // Process each character in input string
  for (int i = 0; i < s.length(); i++) {
    // Skip if not a letter
    if (!isalpha(s[i])) {
      continue;
    }
    // Store whether original char is uppercase
    bool isUpper = isupper(s[i]);
    // Get position in alphabet (0-25) of current char
    int pos = tolower(s[i]) - 'a';
    // Get substitution character from key at that position
    char newChar = key[pos];
    // Put back in original case
    s[i] = isUpper ? toupper(newChar) : newChar;
  }
  return s;
}

string &unsubstitute(string &s, const string key) {
  // Create reverse mapping array where:
  // reverse[0] tells us what 'a' maps to
  // reverse[1] tells us what 'b' maps to, etc.
  char reverse[26];

  // Fill the reverse mapping
  for (int i = 0; i < 26; i++) {
    // If key[i] maps to letter 'a'+i
    // Then 'a'+i maps to letter at position key[i]-'a'
    int keyCharIndex = key[i] - 'a';
    reverse[keyCharIndex] = 'a' + i;
  }

  // Process each character in input string
  for (int i = 0; i < s.length(); i++) {
    // Skip if not a letter
    if (!isalpha(s[i])) {
      continue;
    }
    // Store whether original char is uppercase
    bool isUpper = isupper(s[i]);
    // Get position in alphabet (0-25) of current char
    int pos = tolower(s[i]) - 'a';
    // Get original character using reverse mapping
    char origChar = reverse[pos];
    // Put back in original case
    s[i] = isUpper ? toupper(origChar) : origChar;
  }
  return s;
}

//--------//
// TASK 4 //
//--------//

string &vigenere(string &s, vector<int> key) {
  if (s.empty() || key.empty()) return s;

  int key_index = 0;

  for (int i = 0; i < s.length(); i++) {
    if (!isalpha(s[i])) {
      // For non-letters, increment key position but don't apply the shift
      key_index = (key_index + 1) % key.size();
      continue;
    }

    bool is_upper = isupper(s[i]);
    int value = tolower(s[i]) - 'a';

    value = value + key[key_index];
    value = ((value % 26) + 26) % 26;

    s[i] = (is_upper ? 'A' : 'a') + value;

    // Move to next key position
    key_index = (key_index + 1) % key.size();
  }

  return s;
}
string &unvigenere(string &s, vector<int> key) {
  if (s.empty() || key.empty()) return s;

  // Create inverse key (negative of each number)
  vector<int> inverse_key;
  for (int k : key) {
    inverse_key.push_back(-k);
  }

  // Apply vigenere with inverse key
  return vigenere(s, inverse_key);
}

//--------//
// TASK 5 //
//--------//

void freq(string s) {
  // Create array to store frequency of each letter (a-z)
  int frequency[26] = {0};  // Initialize all to 0

  // Count frequency of each letter
  for (char c : s) {
    if (isalpha(c)) {
      // Convert to lowercase and increment corresponding count
      frequency[tolower(c) - 'a']++;
    }
  }

  // Print frequencies in required format
  for (int i = 0; i < 26; i++) {
    cout << (char)('a' + i) << ":" << frequency[i];
    // Add space after each frequency except the last one
    if (i < 25) cout << " ";
  }
}

// Main Function
int main(void) {
  string text = "Lorem ipsum dolor sit amet, consectetur adipiscing elit!";
  string key = "phqgiumeaylnofdxjkrcvstzwb";
  vector<int> vkey = {7, 5, -6, 22, -13, 6};

  // Uncomment to test the different functions
  // cout << shift_char('c', 2) << endl;
  // cout << shift_char('c', -2) << endl;

  // cout << rotate(text, 3) << endl;
  // cout << rotate(text, -3) << endl;

  // cout << caeser(text, 3) << endl;
  // cout << caeser(text, -3) << endl;

  // cout << substitute(text, key) << endl;
  // cout << unsubstitute(text, key) << endl;

  // cout << vigenere(text, vkey) << endl;
  // cout << unvigenere(text, vkey) << endl;

  // freq(text);
  return 0;
}
