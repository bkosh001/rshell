#ifndef COMMANDS_H
#define COMMANDS_H

#include "Shell.h"

class Commands : public Shell {
    private:
        char str[100];
    public:
        // Commands() : cmd(0) {}
        Commands(char c[]);
        ~Commands() {};
        int execute();
        // char** parses();
        int test(char* argv[], int size);
};

#endif