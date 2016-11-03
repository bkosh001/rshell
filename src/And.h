#ifndef AND_H
#define AND_H

#include "Symbols.h"

class And : public Symbols {
    private:
        Shell* left;
        Shell* right;
    public:
        And() : left(0), right(0) {}
        And(Shell* l, Shell* r) : left(l), right(r) {}
        ~And() {}
        int execute();
};

#endif