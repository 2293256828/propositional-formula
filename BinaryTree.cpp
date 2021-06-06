//
// Created by 86186 on 2021/4/21.
//

#include <vector>
#include "BinaryTree.h"
#include "queue.h"

using namespace std;
bool isValidLetter(char ch) {
    return ch == 'p' || ch == 'q' || ch == 'r' || ch == 'u' || ch == 'v' || ch == 'w' || ch == 'x' || ch == 'y';
}

bool isOperator(char op) {
    switch (op) {
        case '!':
        case '&':
        case '|':
            return 1;
        default:
            return 0;
    }
}
TreeNode *CreateTreeNode(char ch) {

    TreeNode *pNode = new TreeNode;

    pNode->data = ch;

    pNode->left = nullptr;

    pNode->right = nullptr;

    return pNode;

}

TreeNode *createTree(string s) {
    MyStack<TreeNode *> nodeStack;
    char ch;
    int i = 0;
    while (i < s.length() - 1) {
        ch = s[i];
        TreeNode *pNode = CreateTreeNode(ch);
        if (ch == '&' || ch == '|') {
            TreeNode *pRight = nodeStack.pop();
            TreeNode *pLeft = nodeStack.pop();
            pNode->right = pRight;
            pNode->left = pLeft;
            nodeStack.push(pNode);
        } else if (ch == '!') {
            TreeNode *pRight = nodeStack.pop();
            pNode->right = pRight;
            pNode->left = nullptr;
            nodeStack.push(pNode);
        } else { nodeStack.push(pNode); }
        i++;
    }
    return nodeStack.pop();
}

void PrintTree(TreeNode *node, int nLayer) {
    if (node == nullptr)return;
    PrintTree(node->right, nLayer + 2);
    for (int i = 0; i < nLayer; i++) {
        printf(" ");
    }
    printf("%c \n", node->data);
    PrintTree(node->left, nLayer + 2);
    return;
}
TreeNode *distributeCNF(TreeNode *&node, TreeNode *&left, TreeNode *&right) {

    if (node->data == '|') {
        if (left->data == '&') {
            TreeNode *node1=new TreeNode ;
            TreeNode *node2 = new TreeNode;
            TreeNode *node3 = new TreeNode;
            node2->data = '|';
            node3->data = '|';
            node2->left = left->left;
            node2->right = right;
            node3->left = left->right;
            node3->right = right;
            node1->data = '&';
            node1->left = node2;
            node1->right = node3;
            return node1;
        } else if (right->data == '&') {
            TreeNode *node1=new TreeNode ;
            TreeNode *node2 = new TreeNode;
            TreeNode *node3 = new TreeNode;
            node2->data = '|';
            node3->data = '|';
            node2->left = right->left;
            node2->right = left;
            node3->left = right->right;
            node3->right = left;
            node1->data = '&';
            node1->left = node2;
            node1->right = node3;
            return node1;
        }

    }
   if(node->data=='&'||node->data=='|'){
        node->left=left;
        node->right=right;
    }
    return node;
}
TreeNode *distributeDNF(TreeNode *&node, TreeNode *&left, TreeNode *&right) {
    if (node->data == '&') {
        if (left->data == '|') {
            TreeNode *node1=new TreeNode ;
            TreeNode *node2 = new TreeNode;
            TreeNode *node3 = new TreeNode;
            node2->data = '&';
            node3->data = '&';
            node2->left = left->left;
            node2->right = right;
            node3->left = left->right;
            node3->right = right;
            node1->data = '|';
            node1->left = node2;
            node1->right = node3;
            return node1;
        } else if (right->data == '|') {
            TreeNode *node1=new TreeNode ;
            TreeNode *node2 = new TreeNode;
            TreeNode *node3 = new TreeNode;
            node2->data = '&';
            node3->data = '&';
            node2->left = right->left;
            node2->right = left;
            node3->left = right->right;
            node3->right = left;
            node1->data = '|';
            node1->left = node2;
            node1->right = node3;
            return node1;
        }
    }
    if(node->data=='|'||node->data=='&'){
        node->left=left;
        node->right=right;

    }
    return node;
}
bool judgeEqual(TreeNode*left,TreeNode*right){
    if(left== nullptr&&right== nullptr)return true;
    if(left== nullptr||right== nullptr)return false;
    if(left->data!=right->data)return false;
    return judgeEqual(left->left,right->left)&& judgeEqual(left->right,right->right);
}
bool judgeSymmetric(TreeNode*left,TreeNode*right){
    if(left== nullptr&&right== nullptr)return true;
    if(left== nullptr||right== nullptr)return false;
    if(left->data=='!'&&right->data=='!')return judgeSymmetric(left->right,right->right)|| judgeEqual(left->right,right->right);
    if(left->data!=right->data)return false;
        return judgeSymmetric(left->left,right->right)&& judgeSymmetric(left->right,right->left);
}
TreeNode *Simplify(TreeNode *&node, TreeNode *&left, TreeNode *&right){
    if(node->data=='!'){
        if(node->right->data=='!'){
            return right->right;
        }
    }
    if(judgeEqual(left,right)|| judgeSymmetric(left,right)){
        return left;
    }
    node->left=left;
    node->right=right;
    return node;
}
TreeNode *NegationEmbed(TreeNode*&node,TreeNode*&right){
    if(node->data=='!'){
         if(right->data == '|'){
            TreeNode *node1=new TreeNode ;//新节点
            TreeNode *node2=new TreeNode ;//新节点左子树
            TreeNode *node3=new TreeNode ;//新节点右子树
            node2->data='!';node3->data='!';
            node2->right=right->left;node3->right=right->right;
            node2->left= nullptr;node3->left= nullptr;
             node2=Simplify(node2,node2->left,node2->right);
             node3=Simplify(node3,node3->left,node3->right);//分别对左右子树简化
            node1->data='&';
            if(node2->right!= nullptr&&!isValidLetter(node2->right->data)){
                node2=NegationEmbed(node2,node2->right);
            }//递归
             if(node3->right!= nullptr&&!isValidLetter(node3->right->data)){
                node3=NegationEmbed(node3,node3->right);
             }
             node1->left=node2;
             node1->right=node3;
            return node1;
        } else if(right->data == '&'){
            TreeNode *node1=new TreeNode ;
            TreeNode *node2=new TreeNode ;
            TreeNode *node3=new TreeNode ;
            node2->data='!';node3->data='!';
            node2->right=right->left;node3->right=right->right;
            node2->left= nullptr;node3->left= nullptr;
             node2=Simplify(node2,node2->left,node2->right);
             node3=Simplify(node3,node3->left,node3->right);
            node1->data='|';
             if(node2->right!= nullptr&&!isValidLetter(node2->right->data)){
                 node2=NegationEmbed(node2,node2->right);
             }
             if(node3->right!= nullptr&&!isValidLetter(node3->right->data)){
                 node3=NegationEmbed(node3,node3->right);
             }
            node1->left=node2;
            node1->right=node3;
            return node1;
        }
       else if(right->data=='!'){
             return right->right;
       }
    }

    if(node->data=='!'){
        node->right=right;
    }
    return node;
}

void PreOrderPrint(TreeNode *node) {
    if (!node) {
        return;
    }
    cout << node->data << " -> ";
    PreOrderPrint(node->left);
    PreOrderPrint(node->right);
}

void InOrderPrint(TreeNode *node)//中序遍历
{
    if (nullptr != node) {
        InOrderPrint(node->left);
        cout << node->data << " -> ";
        InOrderPrint(node->right);
    }
}

void PostOrderPrint(TreeNode *node)//后序遍历
{
    if (nullptr != node) {
        PostOrderPrint(node->left);
        PostOrderPrint(node->right);
        cout << node->data << " -> ";
    }
}
void changeBackDNF(TreeNode *node, string *&s,int &n)//中序遍历
{

    if (nullptr != node) {
        changeBackDNF(node->left, s,n);
        if(node->data=='|'){n++;}
        else s[n]+=node->data;
        changeBackDNF(node->right, s,n);
    }

}
void changeBackCNF(TreeNode *node, string *&s,int &n)//中序遍历
{

    if (nullptr != node) {
        changeBackCNF(node->left, s,n);
        if(node->data=='&'){n++;}
        else s[n]+=node->data;
        changeBackCNF(node->right, s,n);
    }

}
void FloorTraverse(TreeNode *Tree) //层序遍历_队列实现
{
    Queue<TreeNode *> q;
    if (Tree != nullptr) {
        q.push(Tree);   //根节点进队列
    }

    while (q.empty() == false)  //队列不为空判断
    {
        cout << q.Front()->data << " -> ";

        if (q.Front()->left != nullptr)   //如果有左孩子，leftChild入队列
        {
            q.push(q.Front()->left);
        }


        if (q.Front()->right != nullptr)   //如果有右孩子，rightChild入队列
        {
            q.push(q.Front()->right);
        }

        q.pop();  //已经遍历过的节点出队列
    }
}

