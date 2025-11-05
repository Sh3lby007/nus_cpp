#include <iostream>
#include "simpleIntLinkedList.h"
using namespace std;

int main() {
    List l;

    l.insertHead(123);
    l.insertHead(11);
    l.insertHead(9);
    l.insertHead(1);
    l.insertHead(9);

    cout << "Head Element: " << l.headItem() << endl;
    cout << "Tail Element (Call 1): " << l.tailItem() << endl;
    l.insertTail(42);
    cout << "Tail Element (Call 2): " << l.tailItem() << endl << endl;

    while (!l.isEmpty()) {
        cout << "Alternating sum: " << l.alternatingSum() << endl;
        cout << "The number of occurrences of 9 in the list: " << l.count(9) << endl;
        cout << endl;
        cout << "Removed head: " << l.headItem() << endl;
        l.removeHead();
    }

    return 0;
}
