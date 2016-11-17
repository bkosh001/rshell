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
void sharp(string&);
void printVector(const vector<string>& v);
vector<string> InfixtoPostfix(vector<string>& v);
void parse(string input, vector<string>& v);
Shell* buildTree(vector<string> v, stack<Shell*> s);

void getHostLogin(char* host, char* login, size_t l) {
    // sethostname(gethostname(host, 300), 300)
    if (!gethostname(host,l)) {
        //Successfully retrieved hostname
        sethostname(host,l);
    }
    if (!getlogin_r(login, l)) {
        // setlogin(login);
    }
}


// PRINT VECTOR
void printVector(const vector<string>& v) {
    for (unsigned i = 0; i < v.size(); i++) {
        cout << i << ":" << v.at(i) << endl;
    }
}

void sharp(string& input) {
    if (input.find('#') == string::npos) {
        //no sharp found in input
        return;
    }
    
    /*
    // unsigned int i = 0;
    // unsigned int j = 0;
    
    // for (i = 0; i < input.size(); ++i) {
    //     if (input.at(i) == '"') {
    //         if (i < s) {
    //             // if element(") < element('#') 
    //             for (j = i + 1; j < input.size(); ++j) {
    //                 if (input.at(j) == '"') {
    //                     if (j > s) {
    //                         // if 2nd element('"') > element('#')
    //                         //not a comment, check for another comment after the quote
    //                         break;
    //                     }
    //                     else {
                            
    //                     }
    //                 }
    //             }
    //         }
    //     }
    // }
    // cout << i << endl;
    // cout << j << endl;
    // cout << s << endl;
    // cout << string::npos << endl;
    // return; */
    
    
    // if comment, cuts off everything after comment
    for (unsigned int i = 0; i < input.size(); ++i) {
        if (input.at(i) == '#') {
            if (input.at(i - 1) == ' ') {
                //FIX: check if '#' in quotes
                //FIX: check if 
                // if the input has a valid comment
                //FIX: what if echo "1243 #1234" --> 1234 #1234
                //FIX: what if echo 1234\ #1324 --> 1234 #1234
                //FIX: what if echo 1234\  #1234 --> 1234
                //FIX: what if echo 1234 \#1234 --> 1234 #1234
                //FIX: what if echo 1234 ##1234 --> 1234
                input = input.substr(0,i);
            }
        }
    }
}

// PARSE STRING INTO CHAR POINTERS
void parse(string input, vector<string>& v) {
    //FIX: check for no whitespace b/w connector and 2nd command
    //FIX: semi doesn't need a second operator
    sharp(input);
    // searches strings
    string pushCMD = "";
    string pushSYM = "";
    string pushT1  = "";
    string pushT2  = "";
    
    unsigned index = 0;
    
    for (unsigned int i = 0; i < input.length() - 1; ++i) {
        if (input.at(i) == '(') {
            pushT1 = '(';
            v.push_back(pushT1);
            i++;
            index++;
        }
            //found a set of parenthesis
        // AND SYMBOL
        if (input.at(i) == '&' && input.at(i + 1) == '&') {
            if (i > 0) {
                pushCMD = input.substr(index, i - index);
                while (pushCMD.at(0) == ' ') {
                    pushCMD.erase(0,1);
                }
                while (pushCMD.at(pushCMD.size() - 1) == ' ') {
                    pushCMD.erase(pushCMD.size() - 1, 1);
                }
                v.push_back(pushCMD);
                
                pushSYM = "&&";
                v.push_back(pushSYM);
                
                i++;
                index = i + 1;
            }
            else {
                // ASSUMING YOU CANT BEGIN A COMMAND LINE WITH &
                cout << "Invalid input" << endl;
                exit(0);
            }
        }
        
        // OR SYMBOL
        else if (input.at(i) == '|' && input.at(i + 1) == '|') {
            if (i > 0) {
                pushCMD = input.substr(index, i - index);
                while (pushCMD.at(0) == ' ') {
                    pushCMD.erase(0,1);
                }
                while (pushCMD.at(pushCMD.size() - 1) == ' ') {
                    pushCMD.erase(pushCMD.size() - 1, 1);
                }
                v.push_back(pushCMD);
                
                pushSYM = "||";
                v.push_back(pushSYM);
                
                i++;
                index = i + 1;
            }
            else {
                // ASSUMING YOU CANT BEGIN A COMMAND LINE WITH |
                cout << "Invalid input" << endl;
                exit(0);
            }
        }
        
        // SEMICOLON SYMBOL
        else if (input.at(i) == ';') {
            if (i > 0){
                pushCMD = input.substr(index, i - index);
                while (pushCMD.at(0) == ' ') {
                    pushCMD.erase(0,1);
                }
                while (pushCMD.at(pushCMD.size() - 1) == ' ') {
                    pushCMD.erase(pushCMD.size() - 1, 1);
                }
                v.push_back(pushCMD);
                
                pushSYM = ";";
                v.push_back(pushSYM);
                
                index = i + 1;
            }
            else {
                // ASSUMING YOU CANT BEGIN A COMMAND LINE WITH ;
                cout << "bash: syntax error near unexpected token `;'" << endl;
                exit(0);
            }
        }
    }
    
    // PUSH REMAINING COMMAND
    if (index != 0) {
        pushCMD = input.substr(index, input.length() - 1);
        v.push_back(pushCMD);
    }
    else { // if (index == 0) { 
        pushCMD = input.substr(0, input.length());
        v.push_back(pushCMD);
    }
    
    printVector(v);
    return;
    
}

// CONVERT INFIX TO POSTFIX AND RETURN POSTFIX VECTOR
vector<string> InfixtoPostfix(vector<string>& v) {
    // printVector(v);
    stack<string> s;
    vector<string> postfix;
    
    for (unsigned i = 0; i < v.size(); i++) {
        
        // IF CONNECTOR THEN PUSH STACK TO POSTFIX AND POP THEN PUSH CONNECTOR
        // FIXME
        if (v.at(i) == "&&" ||  v.at(i) == "||" || v.at(i) == ";") {
            while (!s.empty()) {
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
    
    while (!s.empty()){
        postfix.push_back(s.top());
        s.pop();
    }
    return postfix;
}

// BUILD SHELL TREE AND RETURN ROOT
Shell* buildTree(vector<string> v, stack<Shell*> s) {
    for (unsigned int i = 0; i < v.size(); ++i) {
        
        // AND SYMBOL
        if (v.at(i) == "&&") {
            Shell* right = s.top();
            s.pop();
            Shell* left = s.top();
            s.pop();
            And* SYM = new And(left, right);
            s.push(SYM);

        }
        // BAR SYMBOL
        else if (v.at(i) == "||") {
            Shell* right = s.top();
            s.pop();
            Shell* left = s.top();
            s.pop();
            Bar* SYM = new Bar(left, right);
            s.push(SYM);
        }
        // SEMICOLON
        else if (v.at(i) == ";") {
            Shell* right = s.top();
            s.pop();
            Shell* left = s.top();
            s.pop();
            Semi* SYM = new Semi(left, right);
            s.push(SYM);
            // if (right == 0) {
            //     cout << "r" << endl;
            // }
            // if (left == 0) {
            //     cout << "l" << endl;
            // }
            // FIX: segfault with ||, no segfault when first command is wrong
        }
        else { //item is not a connector
            char* str = new char[v.at(i).length() - 1];
            strcpy(str, v.at(i).c_str());
            // printf ("%s\n",str);
            Commands* t = new Commands(str);
            s.push(t);
        }
    }
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
    char host [500];
    char login [500];
    getHostLogin(host, login, 500);
    // cout << login << '@' << host;
    // cout << login << endl;
    // bool go = true;
    int run = 0;
    while (run != 2){
        string userInput = "";
        cout << login << '@' << host << "$ ";
        getline(cin, userInput);
        // cout << "fuck" << endl;/
        if (userInput.size() != 0 && userInput.at(0) != '#') {
            // cout << "Creating vector" << endl;
            vector<string> userStrings;
            stack<Shell*> s;
            // cout << "Parsing userinput" << endl;
            parse(userInput, userStrings);
            // cout << "Converting to postfix" << endl;
            vector<string> postfix = InfixtoPostfix(userStrings);
            // cout << "Building tree" << endl;
            Shell* root = buildTree(postfix, s);
            // cout << "Executing" << endl;
            
            run = root->execute();
            Shell* t = 0;
            while (!s.empty()) {
                t = s.top();
                s.pop();
                delete t;
                t = 0;
            }
            
            if (run == 2) {
                // cout << run << endl;
                exit(0);
            }
        }
    }
    return 0;
}
