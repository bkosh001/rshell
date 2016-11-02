#ifndef COMMANDS_H
#define COMMANDS_H

#include "Shell.h"

class Commands : public Shell {
    private:
        char str[];
    public:
        // Commands() : cmd(0) {}
        Commands(char c[]);
        bool execute();
        void parse(char* arg[]);
};

#endif