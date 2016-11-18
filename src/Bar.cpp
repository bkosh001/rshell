#include "Shell.h"
#include "Bar.h"

int Bar::execute() {
    //if lnum->execute() was unsuccessful, do rnum->execute()
    int lnum = left->execute();
    if(lnum == 0) {
        int rnum = right->execute();
        if (rnum == 1) {
            return 1;
        } 
        else if (rnum == 0) {
            return 0;
        }
        else if (rnum == 2) {
            return 2;
        }
    }
    else if (lnum == 1) {
        return 1;
    }
    else if (lnum == 2) {
        return 2;
    }
    return 0;
}