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
void getHostLogin(char*, char*);
void printVector(vector<string> v);
vector<string> InfixtoPostfix(vector<string>& v);
void parse(string input, vector<string>& v);
Shell* buildTree(vector<string> v);

void getHostLogin(char* host, char* login) {
    // sethostname();
    
    
}

// PRINT VECTOR
void printVector(vector<string> v){
    for(unsigned i = 0; i < v.size(); i++){
        cout << i << ": " << v.at(i) << endl;
    }
}

// CONVERT INFIX TO POSTFIX
vector<string> InfixtoPostfix(vector<string>& v) {
    stack<string> s;
    vector<string> postfix;
    int j = 0;
    
    for(unsigned i = 0; i < v.size(); i++){
        
        // IF CONNECTOR THEN ADD TO STACK TO STR AND POP
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
        // ELSE THEN COMMAND THEN ADD TO STR
        else if (i < v.size()) {
            postfix.push_back(v.at(i)); //"FIX"
        }
        j = i;
    }
    
    while(!s.empty()){
        postfix.push_back(s.top());
        s.pop();
        j++;
    }
    return postfix;
}

// PARSE STRING INTO CHAR POINTERS
void parse(string input, vector<string>& v) {
    string pushCMD = "";
    string pushSYM = "";
    
    unsigned index = 0;
    
    for (unsigned int i = 0; i < input.length() - 1; ++i) {

        // AND SYMBOL
        if (input.at(i) == '&' && input.at(i + 1) == '&'){
            if(i > 0){
                cout << "index: " << index << endl;
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
                cout << "Invalid input";
                exit(0);
            }
        }
        
        // OR SYMBOL
        else if (input.at(i) == '|' && input.at(i + 1) == '|'){
            if(i > 0){
                // cout << "found or" << endl;
                cout << "index: " << index << endl;
                pushCMD = input.substr(index, i - index);
                cout << pushCMD << endl;
                v.push_back(pushCMD);
                
                pushSYM = "||";
                v.push_back(pushSYM);
                
                i++;
                index = i + 1;
                cout << "incremented: " << index << endl;
            }
            else{
                // ASSUMING YOU CANT BEGIN A COMMAND LINE WITH |
                cout << "Invalid input";
                exit(0);
            }
        }
        
        // SEMICOLON SYMBOL
        else if (input.at(i) == ';'){
            if(i > 0){
                cout << "index: " << index << endl;
                // cout << "found col" << endl;
                pushCMD = input.substr(index, i - index);
                cout << pushCMD << endl;
                v.push_back(pushCMD);
                
                pushSYM = ";";
                v.push_back(pushSYM);
                
                i++;
                index = i + 1;
                cout << "ind: " << index << endl;
            }
            else{
                // ASSUMING YOU CANT BEGIN A COMMAND LINE WITH ;
                cout << "Invalid input";
                exit(0);
            }
        }
    }
    
    // PUSH REMAINING COMMAND
    
    pushCMD = input.substr(index + 1, input.length() - 1);
    v.push_back(pushCMD);
    
    printVector(v);
    
    
//   vector<char*> postfix = InfixtoPostfix(v);
//     Shell* root = buildTree(postfix);
//     cout << "root: " << *(root->data) << endl;
//     cout << "left: " << *(root->left->data) << *(root->left->data + 1)<< endl;
//     cout << "right: "<< *(root->right->data) << *(root->right->data + 1) << endl; 
}

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
            Commands* t = new Commands(str);
            s.push(t);
        }
    }
    return s.top();
}


int main() {
    // char host [300];
    // char login [300];
    
    while(1){
        string userInput = "";
        cout << "$ ";
        getline(cin, userInput);

        vector<string> userStrings;
        cout << "Parsing userinput" << endl;
        parse(userInput, userStrings);
        cout << "Converting to postfix" << endl;
        vector<string> postfix = InfixtoPostfix(userStrings);
        cout << "Building tree" << endl;
        Shell* root = buildTree(postfix);
        cout << "Executing" << endl;
        root->execute();
        
    return 0;
    }
}