#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <map>

#include "tokenizer.h"

class TreeNode;
class Tokenizer;

// Parser for the Boolean Formula
class FormulaParser {
    Tokenizer *tknzr;
    int paranCounter = 0;
    TreeNode *parseFormula(); // parse non-terminal Formula in the grammar
    TreeNode *parseConjTerm(); // parse non-terminal ConjTerm in the grammar
    TreeNode *parseTerm(); // parse non-terminal Term in the grammar
  public:
    FormulaParser(std::string ln, std::string type);
    TreeNode *getTreeRoot(); // parse the Boolean formula and return the root node of the formula syntax tree
    ~FormulaParser();
};

// Parser for the Assignment
class AssignmentParser {
    Tokenizer *tknzr;
    std::map<std::string, bool> results;
  public:
    AssignmentParser(std::string ln, std::string type);
    void parseAssignment(std::map<std::string, bool>&);
    std::map<std::string, bool> parseAssignments();

    // int tokenCoun\]\]er= 0;
    ~AssignmentParser();
};

#endif
