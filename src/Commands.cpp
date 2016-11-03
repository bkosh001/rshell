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
    // printf ("%s\n", c);
    strcpy(this->str, c);
}

bool Commands::execute() {
    char* pch;
    pch = strtok (str," ");
    vector<char*> vC;
    while (pch != NULL)
    {
        // printf ("%s\n",pch);
        vC.push_back(pch);
        pch = strtok (NULL, " ");
    }
    unsigned size = vC.size();
    char** argv = new char*[size];
    
    for(unsigned i = 0; i < vC.size(); i++){
        argv[i] = vC.at(i);
    }
    
    // char** argv = &vC[0];
    
    pid_t child;
    int status;
    
    child = fork();
    if (child < 0) {
        // ERROR FORKING CHILD
        // cout << "what" << endl;
        perror ("Error forking child");
        return false;
    }
    else if (child == 0) {
        // USER ENTERED EXIT COMMAND
        // cout << "Comparing to exit" << endl;
        if(strcmp(argv[0], "exit") == 0){
            exit(0);
        }
        // cout << "Executing argv: " << endl;
        execvp(argv[0], argv);
        
        perror ("Error, execvp shouldn't have gone here");
        // EXECVP SHOULD NOT CONTINUE HERE
        return false;
    }
    else if (child > 0) {
        while(wait(&status) != child);
        // cout << "Success!!" << endl;
        return true;
    }
    else {
        // SOMETHING ELSE WENT WRONG
        // cout << "what" << endl;
        perror ("Error, something else went wrong");
        return false;
    }
}

// void Commands::parse(){
//     char* pch;
//     pch = strtok (str," ");
//     vector<char*> vC;
//     // unsigned i = 0;
//     while (pch != NULL)
//     {
//         printf ("%s\n",pch);
//         vC.push_back(pch);
//         // strcpy(argv[i], pch);
//         // cout << "made it" << endl;
//         pch = strtok (NULL, " ");
//         // i++;
//     }
//     // cout << "made it" << endl;
//     char** argv;
//     argv = new char* [vC.size()];
//     for(unsigned i = 0; i < vC.size(); i++){
//         strcpy(argv[i], vC.at(i));
//     }
//     return argv;
// }