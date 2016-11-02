#ifndef BAR_H
#define BAR_H

#include "Symbols.h"

class Bar : public Symbols {
    private:
        Shell* left;
        Shell* right;
    public:
        Bar() : left(0), right(0) {}
        Bar(Shell* l, Shell* r) : left(l), right(0) {}
        bool execute();
};

#endif