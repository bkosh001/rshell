#ifndef SYMBOLS_H
#define SYMBOLS_H

#include "Shell.h"

class Symbols : public Shell {
    protected:
        Shell* left;
        Shell* right;
    public:
        // virtual bool execute() = 0;
};

#endif