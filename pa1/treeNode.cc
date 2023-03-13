#include "treeNode.h"
#include<iostream>

TreeNode::TreeNode(std::string cntt): content {cntt} {}

std::string TreeNode::getContent() const{
  // your code starts here

  // return 
  return content;
}

TreeNode *TreeNode::getLeftChild() const  {
  // your code starts here
  return this->leftChild;
  
}
TreeNode *TreeNode::getRightChild() const {
  // your code starts here
  return this->rightChild;
  
}

bool TreeNode::evaluate(TreeNode* root, std::map<std::string, bool>& results) const {
  
  std::string node= root->getContent();// left = leftChild->getToken(), rightChild->getToken();
  if(node == "*"){
    bool temp1 = evaluate(root->getLeftChild(), results), temp2 = evaluate(root->getRightChild(), results);
    return temp1 && temp2;
    
  }
  else if (node == "+"){
    bool temp1 = evaluate(root->getLeftChild(), results), temp2 = evaluate(root->getRightChild(), results);
    
    return temp1 || temp2;
  }
  
  else if (node == "-"){
    return !(evaluate(root->getLeftChild(), results));
    
  }

  else if(node == "0"){
    return false;
  }
  else if(node =="1"){
    return true;
  }
  else{
    if (results.find(node) != results.end()){
      bool tempConst = results.at(node);
      return tempConst;
    }
    else if(results.find(node)== results.end()){
      throw std::invalid_argument("Error: incomplete assignment");
    }
  }
  return true; 
}

void TreeNode::updateLeftChild(TreeNode *lChild) {
  // your code starts here
  this->leftChild = lChild;

}

void TreeNode::updateChildren(TreeNode *lChild, TreeNode *rChild) {
  // your code starts here
  this->leftChild = lChild;
  this->rightChild = rChild;
}

OperatorNode::OperatorNode(std::string cntt): TreeNode{cntt} {}


ConstantNode::ConstantNode(std::string cntt): TreeNode{cntt} {}


VariableNode::VariableNode(std::string cntt): TreeNode{cntt} {}


TreeNode::~TreeNode() {
  // your code starts here
  delete this->leftChild;
  delete this->rightChild;
}
