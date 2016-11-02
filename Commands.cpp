#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include "Shell.h"
#include "Commands.h"
#include <cstdio>
#include <cstring>
#include <sys/types.h>
#include <sys/wait.h>
using namespace std;

Commands::Commands(char c[]){
    strcpy(str, c);
}

bool Commands::execute() {
    pid_t child;
    int status;
    
    char* argv[100];
    parse(argv);
    
    child = fork();
    if (child < 0) {
        // ERROR FORKING CHILD
        return false;
    }
    else if (child == 0) {
        // USER ENTERED EXIT COMMAND
        // FIX ME
        if(strcmp(argv[0], "exit")){
            exit(0);
        }
        execvp(argv[0], argv);
        
        // EXECVP SHOULD NOT CONTINUE HERE
        return false;
    }
    else if (child > 0) {
        while(wait(&status) != child);
        return true;
    }
    else {
        // SOMETHING ELSE WENT WRONG
        return false;
    }
}

void Commands::parse(char* argv[]){
    // char str[] ="- This, a sample string.";
    char* pch;
    pch = strtok (str," ");
    unsigned i = 0;
    while (pch != NULL)
    {
        argv[i] = pch;
        pch = strtok (NULL, " ");
        i++;
    }
}