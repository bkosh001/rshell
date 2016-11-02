#include "Shell.h"
#include "Bar.h"

bool Bar::execute() {
    if (!left->execute()) {
        if (right->execute()) {
            return true;
        }
    }
    return false;
}