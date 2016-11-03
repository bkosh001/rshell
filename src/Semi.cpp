#include "Shell.h"
#include "Semi.h"

bool Semi::execute() {
    return left->execute() && right->execute();
}