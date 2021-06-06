//
// Created by 86186 on 2021/4/21.
//

#ifndef UNTITLED24_BINARYTREE_H
#define UNTITLED24_BINARYTREE_H
#include <iostream>
#include "stack.h"
typedef struct BinaryNode {
    char data;
    BinaryNode *left;
    BinaryNode *right;
} TreeNode;
TreeNode *CreateTreeNode(char ch);
void changeBackCNF(TreeNode *node, string *&s,int &n);
void changeBackDNF(TreeNode *node, string *&s,int &n);
TreeNode*createTree(string s);
void PrintTree(TreeNode *node, int nLayer);
void PostOrderPrint(TreeNode*node);
void PreOrderPrint(TreeNode*node);
void InOrderPrint(TreeNode*node);
void FloorTraverse(TreeNode *Tree);
TreeNode *distributeCNF(TreeNode *&node, TreeNode *&left, TreeNode *&right);
TreeNode *distributeDNF(TreeNode *&node, TreeNode *&left, TreeNode *&right);
TreeNode *NegationEmbed(TreeNode*&node,TreeNode*&right);
TreeNode *Simplify(TreeNode *&node, TreeNode *&left, TreeNode *&right);
bool isValidLetter(char ch);
bool isOperator(char op);
#endif //UNTITLED24_BINARYTREE_H
