#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Animal {
 private:
  string _name;   // e.g. Cow
  string _sound;  // e.g. Moo
 public:
  Animal(string name, string sound) {
    _name = name;
    _sound = sound;
  }
  string getName() { return _name; }
  virtual string getSound() { return _sound; }
};

class Flyer : public Animal {
 private:
  bool _isFlying;

 public:
  Flyer(string name, string sound) : Animal(name, sound), _isFlying(false) {}

  string getSound() {
    if (_isFlying)
      return "flap";
    else
      return Animal::getSound();
  }

  void fly() { _isFlying = true; }
  void stop() { _isFlying = false; }
};

class Glider : public Flyer {
 private:
  bool _isGliding;

 public:
  Glider(string name, string sound) : Flyer(name, sound), _isGliding(false) {}

  void glide() {
    if (isFlying()) _isGliding = true;
  }
  void stop() {
    Flyer::stop();
    _isGliding = false;
  }

  string getSound() {
    if (_isGliding)
      return "woosh";
    else
      return Flyer::getSound();
  }

  bool isFlying() { return getSound() == "flap"; }
};

int main() {
  // Create some animals
  Animal cow("Cow", "moo");
  Flyer parrot("Parrot", "squawk");
  Glider eagle("Eagle", "screech");

  // Test basic functionality
  cout << "Animal: " << cow.getName() << " says " << cow.getSound() << endl;

  cout << "Flyer: " << parrot.getName() << " initially says "
       << parrot.getSound() << endl;
  parrot.fly();
  cout << "After flying, " << parrot.getName() << " says " << parrot.getSound()
       << endl;
  parrot.stop();
  cout << "After stopping, " << parrot.getName() << " says "
       << parrot.getSound() << endl;

  cout << "Glider: " << eagle.getName() << " initially says "
       << eagle.getSound() << endl;
  eagle.fly();
  cout << "After flying, " << eagle.getName() << " says " << eagle.getSound()
       << endl;
  eagle.glide();
  cout << "After gliding, " << eagle.getName() << " says " << eagle.getSound()
       << endl;
  eagle.stop();
  cout << "After stopping, " << eagle.getName() << " says " << eagle.getSound()
       << endl;

  return 0;
}