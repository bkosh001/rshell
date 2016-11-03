#include "Shell.h"
#include "And.h"
#include "Bar.h"
#include "Commands.h"
// #include "Pound.h"
#include "Semi.h"
#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdio> 
#include <stack>
#include <fstream>
#include <cstdlib>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>

using namespace std;
void getHostLogin(char*, char*, size_t);
void printVector(vector<string> v);
vector<string> InfixtoPostfix(vector<string>& v);
void parse(string input, vector<string>& v);
Shell* buildTree(vector<string> v);

void getHostLogin(char* host, char* login, size_t l) {
    // sethostname(gethostname(host, 300), 300);
    cout << "g: " << gethostname(host,l) << endl;
    if (!gethostname(host,l)) {
        //Successfully retrieved hostname
        sethostname(host,l);
        
    }
    cout << "l: " << getlogin_r(login, 300) << endl;
    // setlogin_r(login, 300);
    
    
}

// PRINT VECTOR
void printVector(vector<string> v){
    for(unsigned i = 0; i < v.size(); i++){
        cout << i << ": " << v.at(i) << endl;
    }
}

// PARSE STRING INTO CHAR POINTERS
void parse(string input, vector<string>& v) {
    //searches strings
    string pushCMD = "";
    string pushSYM = "";
    
    unsigned index = 0;
    
    for (unsigned int i = 0; i < input.length() - 1; ++i) {

        // AND SYMBOL
        if (input.at(i) == '&' && input.at(i + 1) == '&'){
            if(i > 0){
                // cout << "index: " << index << endl;
                pushCMD = input.substr(index, i - index); //was 1
                // cout << pushCMD << endl;
                v.push_back(pushCMD);
                
                pushSYM = "&&";
                // cout << pushSYM << endl;
                v.push_back(pushSYM);
                
                i++;
                index = i + 1;
            }
            else{
                // ASSUMING YOU CANT BEGIN A COMMAND LINE WITH &
                cout << "Invalid input" << endl;
                exit(0);
            }
        }
        
        // OR SYMBOL
        else if (input.at(i) == '|' && input.at(i + 1) == '|'){
            if(i > 0){
                // cout << "found or" << endl;
                // cout << "index: " << index << endl;
                pushCMD = input.substr(index, i - index);
                // cout << pushCMD << endl;
                v.push_back(pushCMD);
                
                pushSYM = "||";
                v.push_back(pushSYM);
                
                i++;
                index = i + 1;
                // cout << "incremented: " << index << endl;
            }
            else{
                // ASSUMING YOU CANT BEGIN A COMMAND LINE WITH |
                cout << "Invalid input" << endl;
                exit(0);
            }
        }
        
        // SEMICOLON SYMBOL
        else if (input.at(i) == ';'){
            if(i > 0){
                // cout << "index: " << index << endl;
                // cout << "found col" << endl;
                pushCMD = input.substr(index, i - index);
                
                // cout << pushCMD << endl;
                v.push_back(pushCMD);
                
                pushSYM = ";";
                v.push_back(pushSYM);
                
                i++;
                index = i + 1;
                // cout << "ind: " << index << endl;
            }
            else{
                // ASSUMING YOU CANT BEGIN A COMMAND LINE WITH ;
                cout << "Invalid input" << endl;
                exit(0);
            }
        }
    }
    
    // PUSH REMAINING COMMAND
    if (index != 0) {
        pushCMD = input.substr(index + 1, input.length() - 1);
        v.push_back(pushCMD);
    }
    else if (index == 0) {
        pushCMD = input.substr(0, input.length());
        v.push_back(pushCMD);
    }
    // cout << "Printing vector" << endl;
    // printVector(v);
}

// CONVERT INFIX TO POSTFIX AND RETURN POSTFIX VECTOR
vector<string> InfixtoPostfix(vector<string>& v) {
    // printVector(v);
    stack<string> s;
    vector<string> postfix;
    
    for(unsigned i = 0; i < v.size(); i++){
        
        // IF CONNECTOR THEN PUSH STACK TO POSTFIX AND POP THEN PUSH CONNECTOR
        // FIXME
        if (v.at(i).find("&&") != string::npos ||
            v.at(i).find("||") != string::npos ||
            v.at(i).find(";") != string::npos){
            while(!s.empty()){
                postfix.push_back(s.top());
                s.pop();
            }
            s.push(v.at(i));
        }
        // ELSE THEN COMMAND SO ADD TO POSTFIX
        else if (i < v.size()) {
            postfix.push_back(v.at(i)); //"FIX"
        }
    }
    
    while(!s.empty()){
        postfix.push_back(s.top());
        s.pop();
    }
    // printVector(postfix);
    return postfix;
}

// BUILD SHELL TREE AND RETURN ROOT
Shell* buildTree(vector<string> v) {
    stack<Shell*> s;
    for (unsigned int i = 0; i < v.size(); ++i) {
        if (v.at(i).find("&&") != string::npos){
            Shell* right = s.top();
            s.pop();
            Shell* left = s.top();
            s.pop();
            And* SYM = new And(left, right);
            s.push(SYM);
        }
        else if (v.at(i).find("||") != string::npos){
            Shell* right = s.top();
            s.pop();
            Shell* left = s.top();
            s.pop();
            Bar* SYM = new Bar(left, right);
            s.push(SYM);
        }
        else if (v.at(i).find(";") != string::npos){
            Shell* right = s.top();
            s.pop();
            Shell* left = s.top();
            s.pop();
            Semi* SYM = new Semi(left, right);
            s.push(SYM);
        }
        else { //item is not a connector
            char* str = new char[v.at(i).length() - 1];
            strcpy(str, v.at(i).c_str());
            // printf ("%s\n",str);
            Commands* t = new Commands(str);
            s.push(t);
        }
    }
    // printVector(v);
    Shell* top = s.top();
    
    // IF I LEAVE THIS THEN WE GET SEG FAULT
    // delete stack
    // while (!s.empty()) {
    //     Shell* t = s.top();
    //     s.pop();
    //     delete t;
    //     t = 0;
    // }
    return top;
}


int main() {
    // size_t len;
    // char host [];
    // char login [];
    // getHostLogin(host, login, len);
    // cout << host << endl;
    // cout << login << endl;
    
    while(1){
        string userInput = "";
        cout << "$ ";
        getline(cin, userInput);
        if (userInput.size() == 0) {
            continue;
        }
        
        // cout << "Creating vector" << endl;
        vector<string> userStrings;
        // cout << "Parsing userinput" << endl;
        parse(userInput, userStrings);
        // cout << "Converting to postfix" << endl;
        vector<string> postfix = InfixtoPostfix(userStrings);
        // cout << "Building tree" << endl;
        Shell* root = buildTree(postfix);
        // cout << "Executing" << endl;
        bool run = root->execute();
        if(run || !run){
            continue;
        }
        
    return 0;
    }
}