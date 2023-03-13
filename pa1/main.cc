#include <iostream>
#include <string>
#include <map>
#include "parser.h"
#include "treeNode.h"
#include<cctype>
#include<regex>

// a helper function parsing the input into the formula string and the assignment string

void parseLine(const std::string &line, std::string &formulaStr, std::string &assignmentStr) {
    // your code starts here

    int paranLeft=0, paranRight = 0, paranCounter=0;
    std::string delimiter = ";";
    formulaStr = line.substr(0, line.find(delimiter));
    if (formulaStr.length() <1)
        throw std::invalid_argument("Error: invalid input");
    std::string temp=  line.substr(line.find(delimiter)+1, line.length());
  
    assignmentStr = temp;
    for(size_t i = 0; i < formulaStr.length(); i++){
        if(formulaStr[i] == '('){
            paranLeft++;
            paranCounter++;
        }
        else if(formulaStr[i] == ')'){
            paranRight++;
            paranCounter-=1;
            if (paranRight > paranLeft){
                throw std::invalid_argument("Error: invalid input");
            }
        }
    
        if(formulaStr[i] == ' '){
            if(std::isalnum(formulaStr[i-1])){
                int j = i;

                while(formulaStr[j] == ' '){
                    j++;
                }
                if (std::isalnum(formulaStr[j])){
                    throw std::invalid_argument("Error: invalid input");
                }
            }
        }
    }
  
    if (paranCounter!=0){
        throw std::invalid_argument("Error: invalid input");
    }

}

// The program shall continuously ask for new inputs from standard input and output to the standard output
// The program should terminate gracefully (and quietly) once it sees EOF
int main() {
  
    std::string line; // store each input line
    std::string formulaStr; // store the formula string
    std::string assignmentStr; // store the assignment string
    while(std::getline(std::cin, line)){
        TreeNode* root = NULL;
        try{

            parseLine(line, formulaStr, assignmentStr);
            
            FormulaParser formulaToken(formulaStr, "formula");
            AssignmentParser assignmentToken(assignmentStr, "assignment");
            root = formulaToken.getTreeRoot();

            std::map<std::string, bool>  assignmentResults = assignmentToken.parseAssignments();
            bool answer;
            
            answer = root->evaluate(root, assignmentResults);
            std::cout<<answer<<std::endl;
            delete root;
        }
        catch (std::invalid_argument &err) {
            std::cout<<err.what()<<std::endl;
            if (root !=NULL){
                delete root;
            }
        }
    
    }
    return 0;
  
}


