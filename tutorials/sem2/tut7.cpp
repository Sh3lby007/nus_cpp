#include <iostream>
#include <string>  // Need to include string header
using namespace std;

class Person {
 private:
  string name;
  int age;
  Person* mother;  // Should be a pointer to avoid infinite recursion
 public:
  // Constructor with default parameters to handle all cases
  Person(string name = "", int age = 0, Person* mother = nullptr) {
    this->name = name;  // Need 'this->' to distinguish parameters from members
    this->age = age;
    this->mother = mother;
  }

  string get_name() { return name; }
  int get_age() { return age; }
  Person* get_mother() { return mother; }  // Return pointer
};  // Missing semicolon after class definition

int my_main() {
  Person sally("Sally", 32);
  Person thomas("Thomas", 6, &sally);  // Need to pass address of sally
  cout << sally.get_name() << " is the mother of " << thomas.get_name()
       << endl;  // Can't access private members directly
  cout << "their age difference is " << sally.get_age() - thomas.get_age()
       << " years" << endl;
  return 0;  // Should return a value
}