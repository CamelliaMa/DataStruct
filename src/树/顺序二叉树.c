/* 定义二叉树顺序存储结构 */

#include <stdio.h>
#include <stdlib.h>

#define ELEMENTTYPE int   // 规定数据类型为int类型


#define MAXSZIE 100
typedef struct TreeNode{
    ELEMENTTYPE value;          // 节点数据域
    size_t is_empty;            // 节点是否为空flage
}TreeNode;
TreeNode BinTree[MAXSZIE];      // 二叉树使用数组实现顺序存储

/*
【注】:
    对于满二叉树以及完全二叉树，数组下标可以和节点编号一一对应，从而反映节点之间的逻辑关系。
    也可以最大限度的节省存储空间。对于编号为 i 的节点:
    left child      -->     2i
    right child     -->     2i+1
    father node     -->     i/2(向下取整)
    若一共 n 个节点，则对于节点i:
    是否存在左孩子：2i <= n
    是否存在右孩子：2i+1 <= n
    是否为叶子节点/分支节点：i > n/2(向下取整)
    对于一般二叉树，则需要插入空节点来达到下标反映节点编号.
*/