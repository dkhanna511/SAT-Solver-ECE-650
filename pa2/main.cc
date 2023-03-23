#include <iostream>
#include <string>
#include <map>
#include<fstream>
#include<cctype>
#include<regex>

#include "parser.h"
#include "treeNode.h"
#include "tseitinTransformer.h"
#include "satSolver.h"

// a helper function parsing the input into the formula string

void parseLine(const std::string &formulaStr) {
    // your code starts here

    int paranLeft=0, paranRight = 0, paranCounter=0;
    if (formulaStr.length() <1)
        throw std::invalid_argument("Error: invalid input");
    
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
  
    std::string line;
    std::ifstream file;
    // file.open("test/test0.in");
    while(std::getline(std::cin, line)){
    
        TreeNode* root = NULL;
        try{
            
            parseLine(line);
            FormulaParser formulaToken(line, "formula");
            root = formulaToken.getTreeRoot();
            // root->printInorder(root);
            TseitinTransformer tseitinTransform(root);
            std::vector<std::vector<int > > cnf = tseitinTransform.transform(root);
            // tseitinTransform.cnfString();
            int totVar = tseitinTransform.getVarNum();
            bool result = satCallingMiniSat(totVar, cnf );
            if (result){std::cout<<"sat"<<std::endl;}
            else{std::cout<<"unsat"<<std::endl;}
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


