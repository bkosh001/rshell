#include "Shell.h"
#include "Symbols.h"
#include "And.h"
#include <iostream>

using namespace std;

int And::execute() {
    //if lnum->execute successful, do right->execute
    int lnum = left->execute();
    if(lnum == 1){
        int rnum = right->execute();
        if(rnum == 1){
            return 1;
        }else if(rnum == 0){
            return 0;
        }else if(rnum == 2){
            return 2;
        }
    }else if(lnum == 0){
        return 0;
    }else if(lnum == 2){
        return 2;
    }
    return 0;
}