/* 构建线索二叉树 */

/*
【说明】:
    二叉链表仅能反应父子关系，无法直接获取前驱以及后继节点，并且或存在 n+1 个空指针，可以按照下面的规则对
    二叉树进行线索化得到线索二叉树：
    1. 节点无左孩子     -->     left_child 指针指向其前驱节点
    2. 节点无右孩子     -->     right_child 指针指向其后继节点
    按照遍历方式分为：先序线索化、中序线索化以及后序线索化，本质为对二叉树进行一次遍历
*/

#include <stdio.h>
#include <stdlib.h>

#define ELEMENTTYPE int   // 规定数据类型为int类型


typedef struct LinkTreeNode{
    ELEMENTTYPE data;                           // 数据域
    struct LinkTreeNode* left_child;            // 左孩子
    struct LinkTreeNode* right_child;           // 右孩子
    int left_flag;                              // 标记左孩子指针指向前驱(1)还是左孩子(0)
    int right_flag;                             // 标记右孩子指针指向后继(1)还是右孩子(0)
}LinkTreeNode,*LinkBinTree;

LinkTreeNode* pre_node;             // 全局变量 -- 当前访问节点的前驱节点


/* 
    定义对当前访问节点的操作
    1、设置当前节点的前驱节点为 pre_node
    2、设置 pre_node 的后继节点为当前节点
*/
void visit(LinkTreeNode* current_node){
    // 建立当前节点的前驱
    if(current_node->left_child == NULL){
        current_node->left_child = pre_node;
        current_node->left_flag = 1;
    }
    // 建立 pre_node 的后继
    if(pre_node!=NULL && current_node->right_child==NULL){
        pre_node->right_child = current_node;
        pre_node->right_flag = 1;
    }
    // 移动 pre_node 指针指向当前节点
    pre_node = current_node;
}

// 先序遍历并线索化 -- 先序遍历二叉树并建立线索指针
void pre_thread(LinkBinTree tree){
    if(tree != NULL){
        visit(tree);        // 先处理根节点
        // 先序递归遍历左子树需要判断左孩子指针指向前驱还是左孩子节点，否则当节点没有左孩子时会出现死循环
        if(tree->left_flag == 0){
            pre_thread(tree->left_child);
        }
        pre_thread(tree->right_child);
    }
}

// 中序遍历并线索化 -- 中序遍历二叉树并建立线索指针
void in_thread(LinkBinTree tree){
    if(tree != NULL){
        in_thread(tree->left_child);
        visit(tree);
        in_thread(tree->right_child);
    }
}

// 后序遍历并线索化 -- 后序遍历二叉树并建立线索指针
void post_thread(LinkBinTree tree){
    if(tree != NULL){
        post_thread(tree->left_child);
        post_thread(tree->right_child);
        visit(tree);
    }
}

// 构建线索二叉树
void create_thread_tree(LinkBinTree tree){
    pre_node = NULL;        // 初始化前驱节点指针
    if(tree != NULL){
        pre_thread(tree);       // 此处可替换为具体线索化逻辑函数
        // 处理最后一个节点
        if(pre_node->right_child == NULL) pre_node->right_flag = 1;
    }
}
