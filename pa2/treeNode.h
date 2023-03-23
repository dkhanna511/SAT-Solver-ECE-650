#ifndef TNODE_H
#define TNODE_H

#include <string>
#include <map>

// abstract superclass of the syntax tree node
class TreeNode {
    std::string content;
    TreeNode *leftChild = nullptr;
    TreeNode *rightChild = nullptr;
  // protected:
  public:
    TreeNode(std::string cntt);
    //TODO: THIS HAS TO BE CHECKED BECAUSE I have removed "const"
    TreeNode *getLeftChild() const ;
    TreeNode *getRightChild() const ;
  
    std::string getContent() const;
    void updateLeftChild(TreeNode *lChild); // for the operator "-", the operand is stored in leftChild
    void updateChildren(TreeNode *lChild, TreeNode *rChild);
    void printInorder(TreeNode* nde) const;
    virtual ~TreeNode();

};

// concrete tree node of opertaor type
class OperatorNode : public TreeNode {
  public:
    OperatorNode(std::string cntt);
    // bool evaluate(const std::map<std::string, bool> &assignment) const override;
};

// concrete tree node of constant type
class ConstantNode : public TreeNode {
  public:
    ConstantNode(std::string cntt);
    // bool evaluate(const std::map<std::string, bool> &assignment) const override;
};

// concrete tree node of varibale type
class VariableNode : public TreeNode {
  public:
    VariableNode(std::string cntt);
    // bool evaluate(const std::map<std::string, bool> &assignment) const override;
};

#endif
