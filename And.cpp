#include "Shell.h"
#include "Symbols.h"
#include "And.h"

bool And::execute() {
    //if left->execute successful, do right->execute
    if (left->execute()) {
        if (right->execute()) {
            return true;
        }
    }
    return false;
}