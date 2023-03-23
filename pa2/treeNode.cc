#include<iostream>
#include "treeNode.h"


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

void TreeNode::printInorder(TreeNode* nde) const
{
if (nde == nullptr) {
 return ;
 }
 std::cout<<nde->getContent()<<" ";

 printInorder(nde->getLeftChild());
 printInorder(nde->getRightChild());
}



TreeNode::~TreeNode() {
  // your code starts here
  delete this->leftChild;
  delete this->rightChild;
}
