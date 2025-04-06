#include <iostream>
#include <stack>  // to use STL stack
#include <string>
#include <vector>
// #include "stack.cpp" // to use honemade stack

using namespace std;

//*************************
// Task 1: Matching bracket
//*************************
bool match_bracket(string expression) {
  stack<char> brackets;

  for (char c : expression) {
    if (c == '(' || c == '[' || c == '{') {
      brackets.push(c);
    } else if (c == ')' || c == ']' || c == '}') {
      if (brackets.empty()) {
        return false;
      }

      char top = brackets.top();
      brackets.pop();

      if ((c == ')' && top != '(') || (c == ']' && top != '[') ||
          (c == '}' && top != '{')) {
        return false;
      }
    }
  }

  return brackets.empty();
}

//******************
// Task 2: Token ADT
//******************
struct Token {
  bool is_operand;
  int operand;
  char operator_char;
};

Token make_token(int i) {
  Token t;
  t.is_operand = true;
  t.operand = i;
  t.operator_char = '\0';  // Not used for operands
  return t;
}

Token make_token(char op) {
  Token t;
  t.is_operand = false;
  t.operand = 0;  // Not used for operators
  t.operator_char = op;
  return t;
}

char get_optr(Token t) { return t.operator_char; }

int get_opnd(Token t) { return t.operand; }

bool is_opnd(Token t) { return t.is_operand; }
//***************************************
// START OF Helper functions. Do not edit

// Function to tokenize a expression into vector of tokens
vector<Token> tokenize(string expression) {
  vector<Token> output;
  string i;
  for (char c : expression) {
    // if c is a digit
    if (isdigit(c)) {
      i += c;
    } else {
      if (!i.empty()) {
        output.push_back(make_token(stoi(i)));
        i.clear();
      }
      // convert brackets to round
      switch (c) {
        case '[':
        case '{':
          c = '(';
          break;
        case ']':
        case '}':
          c = ')';
          break;
      }
      output.push_back(make_token(c));
    }
  }
  if (!i.empty()) output.push_back(make_token(stoi(i)));
  return output;
}

// This function maps the operator to an int
// so we can use the native comparison of int
// to compare the priority.
// You may use this function if you find it useful
int priority(Token t) {
  switch (get_optr(t)) {
    case '+':
    case '-':
      return 0;
    case '*':
    case '/':
      return 1;
    case '^':
      return 2;
  }
  return -1;
}

// Function to teach cout how to display vector of Token
ostream &operator<<(ostream &out, const Token &t) {
  if (is_opnd(t))
    out << get_opnd(t);
  else
    out << get_optr(t);
  return out;
}

ostream &operator<<(ostream &out, const vector<Token> &v) {
  for (Token t : v) out << t << " ";
  return out;
}
// END OF helper functions
//*************************

//*************************
// Task 3: Infix to Postfix
//*************************
vector<Token> in_to_post(vector<Token> infix) {
  vector<Token> output;
  stack<Token> operators;

  for (Token token : infix) {
    if (is_opnd(token)) {
      output.push_back(token);
    } else if (get_optr(token) == '(') {
      operators.push(token);
    } else if (get_optr(token) == ')') {
      while (!operators.empty() && get_optr(operators.top()) != '(') {
        output.push_back(operators.top());
        operators.pop();
      }
      if (!operators.empty()) {
        operators.pop();
      }
    } else {
      while (!operators.empty() && get_optr(operators.top()) != '(' &&
             priority(operators.top()) >= priority(token)) {
        output.push_back(operators.top());
        operators.pop();
      }

      operators.push(token);
    }
  }

  while (!operators.empty()) {
    output.push_back(operators.top());
    operators.pop();
  }

  return output;
}

//*********************************
// Task 4: Calculate the expression
//*********************************
#include <math.h>
int calculate(vector<Token> postfix) {
  stack<int> operands;

  for (Token token : postfix) {
    if (is_opnd(token)) {
      operands.push(get_opnd(token));
    } else {
      int b = operands.top();
      operands.pop();

      int a = operands.top();
      operands.pop();

      char op = get_optr(token);
      int result = 0;

      switch (op) {
        case '+':
          result = a + b;
          break;
        case '-':
          result = a - b;
          break;
        case '*':
          result = a * b;
          break;
        case '/':
          result = a / b;
          break;
        case '%':
          result = a % b;
          break;
        case '^':
          result = pow(a, b);
          break;
      }

      operands.push(result);
    }
  }

  return operands.top();
}

// Main function for local testing
int main(void) {
  cout << boolalpha;  // tell cout to display bool as true/false

  // Task 1
  cout << match_bracket("(1+[2-3]*{9/2})") << endl;
  cout << match_bracket("(1+[2-3]*9/2})") << endl;

  // You may edit the expression for testing
  // Remember only non-negative integers are supported
  string expression = "1+((2+3*4)/5)^6%7";

  // Task 2
  vector<Token> infix = tokenize(expression);
  cout << "   Expr: " << expression << endl;
  cout << "  Infix: " << infix << endl;

  // Task 3
  vector<Token> postfix = in_to_post(infix);
  cout << "Postfix: " << postfix << endl;

  // Task 4
  cout << " Result: ";
  cout << calculate(postfix) << endl;
}