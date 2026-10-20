/* 定义二叉树链式存储结构 -- 实现二叉树的遍历操作 */

#include <stdio.h>
#include <stdlib.h>

#define ELEMENTTYPE int   // 规定数据类型为int类型


typedef struct LinkTreeNode{
    ELEMENTTYPE data;      // 数据域
    struct LinkTreeNode* left_child;            // 左孩子
    struct LinkTreeNode* right_child;           // 右孩子
}LinkTreeNode,*LinkBinTree;

// 辅助函数 -- 对当前访问的节点的操作，例如打印节点值
void visit(LinkTreeNode* node){
    printf("%d ",node->data);
}

/*
【注】：
    在遍历二叉树时普遍使用递归算法，可以更好的回溯
*/

// 先序遍历二叉树
void pre_order(LinkBinTree tree){
    if(tree != NULL){
        visit(tree);                        // 访问根节点
        pre_order(tree->left_child);        // 递归先序遍历左子树
        pre_order(tree->right_child);       // 递归先序遍历右子树
    }
}

// 中序遍历二叉树
void in_order(LinkBinTree tree){
    if(tree != NULL){
        in_order(tree->left_child);        // 递归中序遍历左子树
        visit(tree);                        // 访问根节点
        in_order(tree->right_child);       // 递归中序遍历右子树
    }
}

// 后序遍历二叉树
void post_order(LinkBinTree tree){
    if(tree != NULL){

        post_order(tree->left_child);        // 递归后序遍历左子树
        post_order(tree->right_child);       // 递归后序遍历右子树
        visit(tree);                        // 访问根节点
    }
}

// 求二叉树深度
int get_bin_tree_depth(LinkBinTree tree){
    if(tree == NULL) return 0;              // 空树或者叶子节点判断
    else{   // 对左右子树进行递归求解子树深度 -- 二叉树深度为根节点到叶子节点的最远距离
        int left_depth = get_bin_tree_depth(tree->left_child);
        int right_depth = get_bin_tree_depth(tree->right_child);
        return left_depth > right_depth ? left_depth + 1 : right_depth + 1;
    }
}
