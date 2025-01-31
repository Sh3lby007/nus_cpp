#include <iostream> //for cout
#include <cstdio>   //you can use printf if needed

using namespace std;

void print_solid_slanted_pyramid(int height){
    for (int i = 1; i <= height; ++i) {
        for (int j = 0; j < i; ++j) {
            cout << '#';
        }
        cout << endl;
    }
}

void print_solid_symmetric_pyramid(int height){
    for (int i = 1; i <= height; ++i) {
        for (int s = 0; s < height - i; ++s) {
            cout << ' ';
        }
        for (int j = 0; j < 2 * i - 1; ++j) {
            cout << '#';
        }
        cout << endl;
    }
}

void print_hollow_symmetric_pyramid(int height, char outer, char inner){
    for (int i = 1; i <= height; ++i) {
        for (int s = 0; s < height - i; ++s) {
            cout << ' ';
        }
        if (i == height) {
            for (int j = 0; j < 2 * i - 1; ++j) {
                cout << outer;
            }
        } else {
            cout << outer;
            if (i > 1) {
                int num_inner = 2 * (i - 1) - 1;
                for (int j = 0; j < num_inner; ++j) {
                    cout << inner;
                }
                cout << outer;
            }
        }
        cout << endl;
    }
}

int main(){
    // Comment / modify the following statements to test
    // You can attempt the parts independently

    // print_solid_slanted_pyramid(4);

    // print_solid_symmetric_pyramid(4);

    // print_hollow_symmetric_pyramid( 4, '#', '$');

    return 0;
}
