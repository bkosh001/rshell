#ifndef COMMANDS_H
#define COMMANDS_H

#include "Shell.h"

class Commands : public Shell {
    private:
        char str[500];
    public:
        // Commands() : cmd(0) {}
        Commands(char c[]);
        ~Commands() {};
        bool execute();
        // char** parses();
};

#endif