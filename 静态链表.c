/* 定义静态链表并实现操作 */
/*
    用数组的方式实现链表
    静态链表需要分配一片连续的内存空间，各个节点集中安置
    指针域换为游标（下一节点的数组下标）进行节点之间的连接
*/

#include <stdio.h>
#include <stdlib.h>

// 宏定义 -- 定义常用的宏变量
#define ELEMENT_TYPE int         // 规定数据项类型为int类型（可根据实际的需求进行改变，例如修改为自定义的结构体类型）
#define SUCCESS 1
#define FAILURE 0
#define NOT_FOUND (-1)
#define MAX_SIZE 50

// 定义数据结构
typedef struct {
    ELEMENT_TYPE data;          // 数据域
    int next;                   // 游标
}S_LinkList[MAX_SIZE];          // 链表 -- 最大长度为MAX_SIZE
