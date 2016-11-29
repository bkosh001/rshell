#include "Shell.h"
#include "Semi.h"

int Semi::execute() {
    // execute both no matter what
    int lnum = left->execute();
    int rnum = 0;
    if (right) {
        rnum = right->execute();
    }
    
    if(lnum == 0 || rnum == 0){
        return 0;
    }
    else if (lnum == 2 || rnum == 2) {
        return 2;
    }
    return 1;
}