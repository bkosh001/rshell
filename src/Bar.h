#ifndef BAR_H
#define BAR_H

#include "Shell.h"
#include "Symbols.h"

class Bar : public Symbols {
    //if left->execute() successful, do right->execute()
    private:
        Shell* left;
        Shell* right;
    public:
        Bar() : left(0), right(0) {}
        Bar(Shell* l, Shell* r) : left(l), right(r) {}
        ~Bar() {}
        int execute();
};

#endif