#include "parser.h"
#include "treeNode.h"
#include "tokenizer.h"

FormulaParser::FormulaParser(std::string ln, std::string type): tknzr {new Tokenizer{ln, type}} {
  
}


TreeNode *FormulaParser::parseConjTerm() {
  // your code starts here
    
    TreeNode* term = parseTerm();
    
    if(tknzr->getToken().content != "*"){
        return term;
    }

    else if (tknzr->getToken().content == "*"){

        TreeNode* andNode = new OperatorNode(tknzr->getToken().content);
        tknzr->advanceToken();
        TreeNode* conjTerm = parseConjTerm();
        
        andNode->updateChildren(term, conjTerm);
        return andNode;
    }
    
    return nullptr;
}

TreeNode *FormulaParser::parseTerm() {
    // your code starts here
    std::string str = tknzr->getToken().content;
    if (str == "("){
        tknzr->advanceToken();
        TreeNode* formula = parseFormula();
    
        if(tknzr->getToken().content!=")"){
            throw std::invalid_argument("Error: invalid input");    
        }
    tknzr->advanceToken();

    return formula;
    } 
    
    if (tknzr->getToken().type == "CONSTANT"){
        
        TreeNode* constantNode = new ConstantNode(tknzr->getToken().content);
        tknzr->advanceToken();
        if(tknzr->getToken().type=="LEFTPARAN" || tknzr->getToken().type=="NEGATION")
            throw std::invalid_argument("Error: invalid input");
        
        return constantNode;
    }

    if(str == "-"){ 
        //string for not
        TreeNode* negationNode = new OperatorNode(tknzr->getToken().content);

        tknzr->advanceToken();

        TreeNode* term = parseTerm();
        negationNode->updateLeftChild(term);
        return negationNode; 
    }

    if(tknzr->getToken().type == "VARIABLE"){
        
        TreeNode* variableNode = new VariableNode(tknzr->getToken().content);
        tknzr->advanceToken();
        if(tknzr->getToken().type=="LEFTPARAN" || tknzr->getToken().type=="NEGATION")
            throw std::invalid_argument("Error: invalid input");
        return variableNode;
    }

    else{
        throw std::invalid_argument("Error: invalid input");
    }
  
  return nullptr;
}

TreeNode *FormulaParser::parseFormula() {
    // your code starts here
    
    TreeNode*  conjTerm = parseConjTerm();
    TreeNode* formulaTerm = nullptr;
    
    if (tknzr->getToken().content == "+"){
        TreeNode* plusNode = new OperatorNode(tknzr->getToken().content);
        tknzr->advanceToken();
        formulaTerm = parseFormula();
        
        plusNode->updateChildren(conjTerm, formulaTerm);
        
        return plusNode;
    }
    return conjTerm;
}

TreeNode * FormulaParser::getTreeRoot() {
    // your code starts here

    TreeNode* root = parseFormula();
    
    return root;
}

FormulaParser::~FormulaParser() {
    // your code starts here
    delete(tknzr);

}

void AssignmentParser::parseAssignment(std::map<std::string, bool>& results){

    if(tknzr->getToken().type == "VARIABLE")
    {   
        std::string tempVar = tknzr->getToken().content;
        tknzr->advanceToken();
        if(tknzr->getToken().type == "ASSIGNMENT"){
            tknzr->advanceToken();
            if(tknzr->getToken().type == "CONSTANT"){
                if(results.find(tempVar) == results.end()){
                    if(tknzr->getToken().content=="0" ){
                        results.insert({tempVar,false});
                        tknzr->advanceToken();
                    }
                    else{
                        results.insert({tempVar, true});
                        tknzr->advanceToken();
                    }
                }
                else if(results.find(tempVar)!=results.end()){
                    const char *tempConstant = tknzr->getToken().content.c_str();
                    if (results.at(tempVar) == std::atoi(tempConstant)){
                        tknzr->advanceToken();
                    }
                    else {throw std::invalid_argument("Error: contradicting assignment");}//<<std::endl;
                }
            }

            else{
                throw std::invalid_argument("Error: invalid input");
            }
        }
        else{throw std::invalid_argument("Error: invalid input");}
    }

    else {throw std::invalid_argument("Error: invalid input");}
    
}

AssignmentParser::AssignmentParser(std::string ln, std::string type): tknzr {new Tokenizer{ln, type}} {}

std::map<std::string, bool> AssignmentParser::parseAssignments() {
    
    if (tknzr->getToken().content.length() == 0)
        return results;
    parseAssignment(results);
    
    if(tknzr->getToken().content == ","){
        tknzr->advanceToken();
        results = parseAssignments();
    }

  return results;
}


AssignmentParser::~AssignmentParser() {
  // your code starts here
  delete(tknzr);
}
