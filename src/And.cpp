#include "Shell.h"
#include "Symbols.h"
#include "And.h"
#include <iostream>

using namespace std;

int And::execute() {
    //if left->execute successful, do right->execute
    if (left->execute() == 2 || right->execute() == 2) {
        return 2;
    }
    if (left->execute() != 2) {
        // cout << "Left success" << endl;
        if (right->execute() != 2) {
            // cout << "right s" << endl;
            return 1;
        }
    }
    return 0;
}