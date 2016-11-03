#ifndef SHELL_H
#define SHELL_H

#include <string>
#include <iostream>

class Shell {
    public:
        ~Shell() {}
        virtual int execute() = 0;
};

#endif
