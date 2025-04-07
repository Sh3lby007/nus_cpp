#include <iostream>
#include <string>  // Need to include string header
#include <vector>
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

class Animal {
 private:
  string name;
  string sound;

 public:
  Animal(string name, string sound) {
    this->name = name;
    this->sound = sound;
  }

  string getName() { return name; }

  string getSound() { return sound; }
};

class OldMcDonald {
 private:
  vector<Animal*> _farm;

 public:
  OldMcDonald() {
    _farm.push_back(new Animal("Cow", "Moo"));
    _farm.push_back(new Animal("Dog", "Woof"));
    _farm.push_back(new Animal("Duck", "Quack"));
  }

  ~OldMcDonald() {
    for (int i = 0; i < _farm.size(); i++) {
      delete _farm[i];
    }
    _farm.clear();
  }

  void sing() {
    for (int i = 0; i < _farm.size(); i++) {
      cout << "Old McDonald had a farm, E-I-E-I-O\n";
      cout << "And on his farm he had a " << _farm[i]->getName()
           << ", E-I-E-I-O\n";
      cout << "With a " << _farm[i]->getSound() << " " << _farm[i]->getSound()
           << " here and a " << _farm[i]->getSound() << " "
           << _farm[i]->getSound() << " there\n";
      cout << _farm[i]->getSound() << " here " << _farm[i]->getSound()
           << " there, everywhere " << _farm[i]->getSound() << " "
           << _farm[i]->getSound() << "\n";
      cout << "Old McDonald had a farm, E-I-E-I-O\n\n";
    }
  }
};

int main() {
  Person sally("Sally", 32);
  Person thomas("Thomas", 6, &sally);  // Need to pass address of sally
  cout << sally.get_name() << " is the mother of " << thomas.get_name()
       << endl;  // Can't access private members directly
  cout << "their age difference is " << sally.get_age() - thomas.get_age()
       << " years" << endl;

  OldMcDonald farm;
  farm.sing();
  return 0;
}