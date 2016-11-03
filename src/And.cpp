#include "Shell.h"
#include "Symbols.h"
#include "And.h"
#include <iostream>

using namespace std;

bool And::execute() {
    //if left->execute successful, do right->execute
    if (left->execute()) {
        // cout << "Left success" << endl;
        if (right->execute()) {
            // cout << "right s" << endl;
            return true;
        }
    }
    return false;
}