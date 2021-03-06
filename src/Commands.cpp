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
#include <sys/stat.h>
using namespace std;

Commands::Commands() {}

Commands::Commands(char c[]) {
    strcpy(this->str, c);
}

int Commands::execute() {
    // TOKENIZE STRING
    char* pch;
    pch = strtok (str," ");
    char* argv[100] = {};
    unsigned size = 0;
    while (pch != NULL) {
        argv[size] = pch;
        pch = strtok (NULL, " ");
        size++;
    }
    // CHECK IF EXIT
    if (strcmp(argv[0], "exit") == 0) {
        // 2 SHOWS THAT WE WANT TO EXIT
        return 2;
    }
    // CHECK IF TEST
    if (strcmp(argv[0], "test") == 0){
        return test(argv, size);
    }
    else if (strcmp(argv[0], "[") == 0) {
        return test(argv, size);
    }
    // CHECK IF CD
    else if (strcmp(argv[0], "cd") == 0) {
        return cd(argv, size);
    }
    int returnval = -1;
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
        // EXECVP SHOULD NOT CONTINUE HERE
        char err[50] = "bash: ";
        strcat(err,argv[0]);
        strcat(err, ": command not found");
        perror (err);
        returnval = 0;
    }
    else if (child > 0) {
        while (wait(&status) != child);
        if(returnval == 0){
            return 0;
        }
        return 1;
    }
     
    // SOMETHING ELSE WENT WRONG
    return 0;
}

int Commands::test(char* argv[], int size){
    // ASSUME TEST OR [ IS FIRST CHAR*
    // IF TEST THEN JUST CHECK NORMALLY
    // IF [ THEN IGNORE LAST CHAR
    if (strcmp(argv[0], "test") == 0){
        if (argv[1]){
            struct stat sb;
            // CHECK IF FILE EXISTS
            if(strcmp(argv[1], "-e") == 0){
                if(argv[2]){
                    int num = stat(argv[2], &sb);
                    if(num == 0){
                        // SUCCESS: FILE EXISTS
                        cout << "(True)" << endl;
                        return 1;
                    }
                    else {
                        // FAILED: FILE DOESNT EXIST
                        cout << "(False)" << endl;
                        return 0;
                    }
                }
                else {
                    // FAILED: NO FILE TO CHECK
                    return 0;
                }
            }
            // CHECK IF IT IS A REGULAR FILE
            else if (strcmp(argv[1], "-f") == 0){
                if (argv[2]){
                    stat(argv[2], &sb);
                    if (S_ISREG(sb.st_mode)) {
                        // SUCCESS: IS A REGULAR FILE
                        cout << "(True)" << endl;
                        return 1;
                    } else{
                        // FAILED: FILE NOT REGULAR
                        cout << "(False)" << endl;
                        return 0;
                    }
                }
                else {
                    // FAILED: NO FILE TO CHECK
                    cout << "(False)" << endl;
                    return 0;
                }
            }
            // CHECK IF IT IS A DIRECTORY
            else if(strcmp(argv[1], "-d") == 0){
                if(argv[2]){
                    stat(argv[2], &sb);
                    if (S_ISDIR(sb.st_mode)) {
                        // SUCCESS: IS A REGULAR FILE
                        cout << "(True)" << endl;
                        return 1;
                    }
                    else {
                        // FAILED: FILE NOT REGULAR
                        cout << "(False)" << endl;
                        return 0;
                    }
                }
                else {
                    // FAILED: NO FILE TO CHECK
                    cout << "(False)" << endl;
                    return 0;
                }
            }
            // ASSUME -e
            else {
                if(stat(argv[1], &sb) == 0) {
                    // SUCCESS: FILE EXISTS
                    cout << "(True)" << endl;
                    return 1;
                }
                else {
                    // FAILED: FILE DOESNT EXIST
                    cout << "(False)" << endl;
                    return 0;
                }
            }
        }
    }
    else if (strcmp(argv[0], "[") == 0) {
        if (strcmp(argv[size - 1], "]") == 0){
            if (argv[1]) {
                struct stat sb;
                // CHECK IF FILE EXISTS
                if (strcmp(argv[1], "-e") == 0){
                    if (argv[2]){
                        int num = stat(argv[2], &sb);
                        if (num == 0){
                            // SUCCESS: FILE EXISTS
                            cout << "(True)" << endl;
                            return 1;
                        }
                        else {
                            // FAILED: FILE DOESNT EXIST
                            cout << "(False)" << endl;
                            return 0;
                        }
                    }
                    else {
                        // FAILED: NO FILE TO CHECK
                        return 0;
                    }
                }
                // CHECK IF IT IS A REGULAR FILE
                else if (strcmp(argv[1], "-f") == 0){
                    if (argv[2]){
                        stat(argv[2], &sb);
                        if (S_ISREG(sb.st_mode)) {
                            // SUCCESS: IS A REGULAR FILE
                            cout << "(True)" << endl;
                            return 1;
                        }
                        else {
                            // FAILED: FILE NOT REGULAR
                            cout << "(False)" << endl;
                            return 0;
                        }
                    }
                    else {
                        // FAILED: NO FILE TO CHECK
                        cout << "(False)" << endl;
                        return 0;
                    }
                }
                // CHECK IF IT IS A DIRECTORY
                else if (strcmp(argv[1], "-d") == 0){
                    if (argv[2]){
                        stat(argv[2], &sb);
                        if (S_ISDIR(sb.st_mode)) {
                            // SUCCESS: IS A REGULAR FILE
                            cout << "(True)" << endl;
                            return 1;
                        }
                        else {
                            // FAILED: FILE NOT REGULAR
                            cout << "(False)" << endl;
                            return 0;
                        }
                    }
                    else {
                        // FAILED: NO FILE TO CHECK
                        cout << "(False)" << endl;
                        return 0;
                    }
                }
                // ASSUME -e
                else {
                    if (stat(argv[1], &sb) == 0) {
                        // SUCCESS: FILE EXISTS
                        cout << "(True)" << endl;
                        return 1;
                    }
                    else {
                        // FAILED: FILE DOESNT EXIST
                        cout << "(False)" << endl;
                        return 0;
                    }
                }
            }
            else {
                // NO FILE TO CHECK
                return 0;
            }
        }
    }
    cout << "(False)" << endl;
    return 0;
}

int Commands::cd(char* argv[], int size){
    // CD TO <PATH> OR -

    if (argv[1]){
        // CD TO PREVIOUS WORKING DIR
        if (strcmp(argv[1], "-") == 0) {
            char * p = getenv("OLDPWD");
            cout << p << endl; //cd - outputs new path
            if (chdir(p) < 0) { // go to oldpwd
                perror("bash: cd: OLDPWD not set");
                return 0; //chdir fails, no OLDPWD
            }
            char* o = getenv("PWD"); //saves a temp copy of pwd (new previous)
            setenv("OLDPWD", o, 1); // save "new" oldpwd
            
            setenv("PWD", p, 1);
            return 1;
        
        // CD TO PATH
        }
        else {
            char* o = getenv("PWD");
            // cout << getenv("OLDPWD") << endl;
            if (chdir(argv[1]) < 0) { // PATH DOESNT EXIST
                char err[500] = "bash: cd: ";
                strcat(err,argv[1]);
                perror(err);
                return 0;
            }

            char* curr = getcwd(argv[1], 500);
            setenv("OLDPWD", o, 1); //save PWD to OLDPWD;
            setenv("PWD", curr, 1);
            return 1;
        }
    }
    // JUST CD
    char* p = getenv("PWD");
    setenv("OLDPWD", p, 1); //overwrite OLDPWD with PWD(current PWD)

    char* h = getenv("HOME");
    if (chdir(h) < 0) {
        perror("no homes for orphans");
        return 0;
    }
    
    setenv("PWD", h, 1);
    return 1;
}

void Commands::printcurPWD() {
    char* curPWD = getenv("PWD");
    for (int i = 0; curPWD[i] != '\0'; ++i) {
        cout << curPWD[i];
    }
}