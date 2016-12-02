#include "Shell.h"
#include "And.h"
#include "Bar.h"
#include "Commands.h"
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
    
    // if comment, cuts off everything after comment
    for (unsigned int i = 0; i < input.size(); ++i) {
        if (input.at(i) == '#') {
            if (input.at(i - 1) == ' ') {
                input = input.substr(0, i - 1);
                while (input.at(input.size() - 1) == ' ') {
                    input.erase(input.size() - 1, 1);
                }
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
    
    unsigned index = 0;
    for (unsigned int i = 0; i < input.length(); ++i) {
        if (input.at(i) == '(') {
            pushSYM = "(";
            v.push_back(pushSYM);
            index = i + 1;
        }
        else if (input.at(i) == ')') {
            pushCMD = input.substr(index, i - index);
            // FIX ME
            // GET RID OF WHITESPACE
            if (pushCMD.length() != 1 && pushCMD != " " && pushCMD != "") {
                while (pushCMD.at(0) == ' ') {
                    pushCMD.erase(0,1);
                }
                while (pushCMD.at(pushCMD.size() - 1) == ' ') {
                    pushCMD.erase(pushCMD.size() - 1, 1);
                }
            }
            if (pushCMD != " " && pushCMD != ""){
                v.push_back(pushCMD);
            }
            
            pushSYM = ")";
            v.push_back(pushSYM);
            
            index = i + 1;
        }
            //found a set of parenthesis
        // AND SYMBOL
        else if (input.at(i) == '&' && input.at(i + 1) == '&') {
            if (i > 0) {
                pushCMD = input.substr(index, i - index);
                if(pushCMD.length() != 1 && pushCMD != " "){
                    while (pushCMD.at(0) == ' ') {
                        pushCMD.erase(0,1);
                    }
                    while (pushCMD.at(pushCMD.size() - 1) == ' ') {
                        pushCMD.erase(pushCMD.size() - 1, 1);
                    }
                }
                if(pushCMD != " " && pushCMD != "\0"){
                    v.push_back(pushCMD);
                }
                
                pushSYM = "&&";
                v.push_back(pushSYM);
                
                i++;
                index = i + 1;
            }
            else {
                // ASSUMING YOU CANT BEGIN A COMMAND LINE WITH &
               cout << "bash: syntax error near unexpected token '" << input.at(0) << "'"<< endl;
                exit(0);
            }
        }
        
        // OR SYMBOL
        else if (input.at(i) == '|' && input.at(i + 1) == '|') {
            
            if (i > 0) {
                pushCMD = input.substr(index, i - index);
                if (pushCMD.length() > 1 && pushCMD != " ") {
                    while (pushCMD.at(0) == ' ') {
                        pushCMD.erase(0,1);
                    }
                    while (pushCMD.at(pushCMD.size() - 1) == ' ') {
                        pushCMD.erase(pushCMD.size() - 1, 1);
                    }
                }
                
                if (pushCMD != " " && pushCMD != "\0"){
                    v.push_back(pushCMD);
                }
                
                pushSYM = "||";
                v.push_back(pushSYM);
                
                i++;
                index = i + 1;
            }
            else {
                // ASSUMING YOU CANT BEGIN A COMMAND LINE WITH |
                cout << "bash: syntax error near unexpected token '" << input.at(0) << "'"<< endl;
                exit(0);
            }
        }
        
        // SEMICOLON SYMBOL
        else if (input.at(i) == ';') {
            if (i > 0) {
                pushCMD = input.substr(index, i - index);
                while (pushCMD.at(0) == ' ') {
                    pushCMD.erase(0,1);
                }
                while (pushCMD.at(pushCMD.size() - 1) == ' ') {
                    pushCMD.erase(pushCMD.size() - 1, 1);
                }

                if (pushCMD != " " && pushCMD != ""){
                    v.push_back(pushCMD);
                }
                
                pushSYM = ";";
                v.push_back(pushSYM);
                
                index = i + 1;
            }
            else {
                // ASSUMING YOU CANT BEGIN A COMMAND LINE WITH ;
                cout << "bash: syntax error near unexpected token '" << input.at(0) << "'"<< endl;
                exit(0);
            }
        }
    }
    // PUSH REMAINING COMMAND
    if (index != 0) {
        pushCMD = input.substr(index, input.length() - 1);
        if (pushCMD.length() == 1){
            if (pushCMD == ")"){
                v.push_back(")");
            }
        }
        else {
            while (pushCMD.at(0) == ' ') {
                pushCMD.erase(0,1);
            }
            while (pushCMD.at(pushCMD.size() - 1) == ' ') {
                pushCMD.erase(pushCMD.size() - 1, 1);
            }
            if (pushCMD.at(pushCMD.length() - 1) == ')' ) {
                pushCMD.erase(pushCMD.length() - 1, 1);
                if(pushCMD != "" || pushCMD != " "){
                    v.push_back(pushCMD);
                }
                v.push_back(")");
            }
            else {
                v.push_back(pushCMD);
            }
        }
        
    }
    else { // if (index == 0) { 
        pushCMD = input.substr(0, input.length());
        v.push_back(pushCMD);
    }
    
    // printVector(v);
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
            if(!s.empty()){
                if(s.top() != "("){
                    postfix.push_back(s.top());
                }
                s.pop();
            }
            s.push(v.at(i));
        }
        // IF LEFT PARENTHESES, PUSH
        
        else if (v.at(i) == "(") {
            s.push(v.at(i));
        }
        else if (v.at(i) == ")") {
            while (!s.empty() && s.top() != "("){
                postfix.push_back(s.top()); 
                s.pop();
            }
            
            if (!s.empty()){
                if (s.top() == "(") {
                    s.pop();
                }
            }
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
    // printVector(postfix);
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
    
    return top;
}

// PRINT OUT CURRENT DIRECTORY
void printDir() {
    Commands c;
    c.printcurPWD();
    //FIXME: DOESN'T CHANGE WHEN DIRECTORY CHANGES
}

int main() {
    char host [500] = "";
    char login [500] = "";
    getHostLogin(host, login, 500);
    
    // bool go = true;
    int run = 0;
    while (run != 2) {
        string userInput = "";
        // OUTPUT HOST AND LOGIN
        cout << login << '@' << host <<":~";
        // OUTPUT CURRENT DIRECTORY
        printDir();
        cout << " $ ";
        
        getline(cin, userInput);
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
            //issue where multiple invalid inputs
            //try to exit, must enter "exit" multiple times
            //before it does anything
            if (run == 2) {
                // cout << run << endl;
                exit(0);
            }
        }
    }
    return 0;
}