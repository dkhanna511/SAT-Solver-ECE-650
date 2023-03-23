#include<iostream>
#include<string>
// #include<algorithm>
// #include<stdio.h>

#include "tseitinTransformer.h"
// #include "treeNode.h"

// #include "tokenizer.cc"
#include "parser.h"
#include"treeNode.h"

TseitinTransformer::TseitinTransformer(TreeNode *root): formulaRoot{root} {}

int TseitinTransformer::transSubformula(TreeNode* subRoot) {
  // your code starts here
    
    if(subRoot->getContent() == "+"){
      int currentID = varIdCounter;
      
      varIdCounter++;
      int leftID = transSubformula(subRoot->getLeftChild());
      int rightID = transSubformula(subRoot->getRightChild());
      addOrEq(currentID, leftID, rightID);
      return currentID;
    }
    else if(subRoot->getContent() == "*"){
      int currentID = varIdCounter;
      
      varIdCounter++;
      int leftID = transSubformula(subRoot->getLeftChild());
      int rightID = transSubformula(subRoot->getRightChild());
      addAndEq(currentID, leftID, rightID);
      return currentID;
    }
    else if(subRoot->getContent() == "-"){
      int currentID = varIdCounter;
      
      varIdCounter++;
      int leftID = transSubformula(subRoot->getLeftChild());
      // int rightID = subRoot->getRightChild(transSubFormula(subRoot->getRightChild()));
      addNegEq(currentID, leftID);
      return currentID;
    }

    else{
      int currentID = varIdCounter;
      
      if (varIdTable.find(subRoot->getContent()) != varIdTable.end()){
          return varIdTable.at(subRoot->getContent());
      }
      if (varIdTable.find(subRoot->getContent()) == varIdTable.end()){
        varIdCounter++;
        varIdTable.insert({subRoot->getContent(),currentID});
        return varIdTable.at(subRoot->getContent());
      }
      return currentID;
    }
  

  return 0;
}

void TseitinTransformer::addNegEq(int curID, int childID) {
  // your code starts here

  std::vector<int> clause1, clause2;
  clause1.push_back(-curID);
  clause1.push_back(-childID);

  clause2.push_back(curID);
  clause2.push_back(childID);

  cnf.push_back(clause1);
  cnf.push_back(clause2);  
    
}

void TseitinTransformer::addOrEq(int curID, int leftID, int rightID) {
  // your code starts here
  std::vector<int> clause1, clause2, clause3;
  clause1.push_back(-curID);
  clause1.push_back(leftID);
  clause1.push_back(rightID);


  clause2.push_back(-leftID);
  clause2.push_back(curID);

  clause3.push_back(-rightID);
  clause3.push_back(curID);

  cnf.push_back(clause1);
  cnf.push_back(clause2);
  cnf.push_back(clause3);


}

void TseitinTransformer::addAndEq(int curID, int leftID, int rightID) {
  // your code starts here
  std::vector<int> clause1, clause2, clause3;
  clause1.push_back(curID);
  clause1.push_back(-leftID);
  clause1.push_back(-rightID);


  clause2.push_back(-curID);
  clause2.push_back(rightID);

  clause3.push_back(-curID);
  clause3.push_back(leftID);

  cnf.push_back(clause1);
  cnf.push_back(clause2);
  cnf.push_back(clause3);

}

std::vector<std::vector<int>> TseitinTransformer::transform(TreeNode *root) {
  // your code starts here
    int totalID = transSubformula(root);
    cnf.push_back({1});
    // for (size_t i  = 0; i < cnf.size(); i++){
    //   for(size_t j = 0 ; j < cnf[i].size(); j++)
    //   {
    //     std::cout<<cnf[i][j]<<"  ";
    //   }
    //   std::cout<<std::endl;
    // }

    // std::cout<<"carIDNum is : "<<varIdCounter<<std::endl;

  return cnf;
}

std::string TseitinTransformer::cnfString() const {
  std::string result = "[";

  // your code starts hereint totalID = transSubformula(root);
    for (size_t i  = 0; i < cnf.size(); i++){
      result+="[";
      for(size_t j = 0 ; j < cnf[i].size(); j++)
        {
          if (j<cnf[i].size()-1){
          result+=std::to_string(cnf[i][j]) + ", ";
          }
          else{
            result+=std::to_string(cnf[i][j])+"]";
        }
      
      }
    }
  result = result  + "]";
  std::cout<<"result is : "<<result<<std::endl;
  return result;
}

unsigned int TseitinTransformer::getVarNum() const {
  // your code starts here
  return varIdCounter;
}
