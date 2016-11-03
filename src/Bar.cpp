#include "Shell.h"
#include "Bar.h"

int Bar::execute() {
    if (left->execute() == 2) {
        return 2;
    }
    if (left->execute() == 1) {
        if (right->execute()) {
            return 1;
        }
    }
    return 0;
}