#include "Shell.h"
#include "Semi.h"

int Semi::execute() {
    // if (left->execute() == 0 || right->execute() ) {
    //     return 2;
    // }
    // if (!left->execute() || !right->execute()) {
    //     return 1;
    // }
    // return 0;
    
    if (left->execute() == 0 || right->execute() == 0) {
        return 0;
    }
    else {
        return 1;
    }
}