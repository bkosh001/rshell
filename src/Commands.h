#ifndef COMMANDS_H
#define COMMANDS_H

#include "Shell.h"

class Commands : public Shell {
    private:
        char str[100];
    public:
        Commands();
        Commands(char c[]);
        ~Commands() {};
        int execute();
        int test(char* argv[], int size);
        int cd(char*argv[], int size);
        void printcurPWD();
};

#endif