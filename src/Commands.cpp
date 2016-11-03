#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include "Shell.h"
#include "Commands.h"
#include <cstdio>
#include <cstring>
#include <sys/types.h>
#include <sys/wait.h>
#include <vector>
using namespace std;

Commands::Commands(char c[]){
    strcpy(this->str, c);
}

int Commands::execute() {
    char* pch;
    pch = strtok (str," ");
    char* argv[100] = {};
    unsigned i = 0;
    while (pch != NULL) {
        argv[i] = pch;
        pch = strtok (NULL, " ");
        i++;
    }
    
    // char ** argv = &vC[0];
    if(strcmp(argv[0], "exit") == 0){
        // 2 SHOWS THAT WE WANT TO EXIT
        return 2;
    }
    // if(strcmp(argv[0], "#") == 0){ // FIXME
    //     return 0;
    // }
    
    pid_t child;
    int status;
    
    child = fork();
    if (child < 0) {
        // ERROR FORKING CHILD
        perror ("Error forking child");
        return 0;
    }
    else if (child == 0) {
        // EXECUTE
        execvp(argv[0], argv);
        
        perror ("Error, execvp shouldn't have gone here");
        // EXECVP SHOULD NOT CONTINUE HERE
        return 0;
    }
    else if (child > 0) {
        while (wait(&status) != child);
        return 1;
    }
    else {
        // SOMETHING ELSE WENT WRONG
        // cout << "what" << endl;
        perror ("Error, something else went wrong");
        return 0;
    }
}