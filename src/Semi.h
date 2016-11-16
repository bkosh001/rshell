#ifndef SEMI_H
#define SEMI_H

#include "Shell.h"
#include "Symbols.h"

class Semi : public Symbols {
    // do right->execute() and left->execute()
    private:
        Shell* left;
        Shell* right;
    public:
        Semi() : left(0), right(0) {}
        Semi(Shell* l, Shell* r) : left(l), right(r) {}
        ~Semi() {}
        int execute();
};

#endif