/* 定义链表，实现链表的各种操作 */

#include <stdio.h>
#include <stdlib.h>

// 宏定义 -- 定义常用的宏变量
#define ELEMENT_TYPE int         // 规定数据项类型为int类型（可根据实际的需求进行改变，例如修改为自定义的结构体类型）
#define SUCCESS 1
#define FAILURE 0
#define NOT_FOUND (-1)

// 定义链表的数据元素
typedef struct list_node{
    ELEMENT_TYPE data;              // 链表数据域
    struct list_node* next;         // 链表指针域 -- 用于指向下一节点
}list_node, *LinkList;              // 前者指向普通节点，后者指向整条链表的头节点（代表整条链表）     LinkList = *listNode

// 初始化链表 -- 带头节点
LinkList init_linkList(){
    // 申请一个节点的内存作为链表头节点（即为整条链表的起始节点）
    /*
        此处体现顺序表以及链表最大的不同：
            顺序表申请内存空间时需要申请一片连续的、固定大小的内存空间存储顺序表，大小确定后不可再做出修改；
            链表申请内存空间时无需申请整个链表的空间，只需要申请头节点的内存空间，后面添加节点时随用随申请，所以链表存储为碎片的、不连续的；
    */
    list_node* head = (list_node *)malloc(sizeof(list_node));
    if(head == NULL){
        printf("节点内存申请失败!\n");
        return NULL;
    }else head->next = NULL;      // 申请成功则将头节点下一节点设置为NULL并返回
    return head;
}

// 向链表内插入新节点 -- 按位序插入
int insert_linklist_node(LinkList list, const int index, const ELEMENT_TYPE inserted_data){
    // 转化索引：base_1 --> base_0
    int insert_index = index - 1;
    // 索引检查
    if(insert_index < 0){
        printf("非法索引!\n");
        return FAILURE;
    }
    // 遍历寻找插入位置 
    list_node* current_node = list;         // 当前遍历到的节点 -- 初始化为头节点
    int current_index = 0;                  // 当前索引
    while(current_node && current_index < insert_index){      // 开始遍历寻找插入位置
        current_node = current_node->next;
        current_index++;
    }
    if(current_node == NULL) return FAILURE;
    // 申请新节点的内存空间
    list_node* new_node = (list_node *)malloc(sizeof(list_node));
    if(new_node == NULL){
        printf("节点内存申请失败!\n");
        free(new_node);         // 释放申请的新节点内存避免出现内存泄露
        return FAILURE;
    }
    // 执行赋值以及插入操作
    new_node->data = inserted_data;
    new_node->next = current_node->next;
    current_node->next = new_node;
    return SUCCESS;
}

// 删除链表节点
int delete_linklist_node(LinkList list,int index,ELEMENT_TYPE* deleted_value){
    // 转化索引：base_1 --> base_0
    int delete_index = index - 1;
    // 检查索引
    if(delete_index < 0){
        printf("非法索引.\n");
        return FAILURE;
    }
    // 遍历寻找位置 
    list_node* current_node = list;         // 当前遍历到的节点 -- 初始化为头节点
    int current_index = 0;                  // 当前索引
    while(current_node && current_index < delete_index){      // 开始遍历寻找位置
        current_node = current_node->next;
        current_index++;
    }
    if(current_node == NULL) return FAILURE; // 检查是否超出链表长度
    // 执行删除操作
    /*
        1、使用一个临时节点指向要被删除的节点；
        2、记录被删除的节点的值；
        3、将被删除节点的前驱节点的next指针指向被删除节点的后继节点，将被删除节点从链表中剔除并释放内存；
    */
    list_node* temp_node = current_node->next;
    *deleted_value = temp_node->data;
    current_node->next = temp_node->next;
    free(temp_node);
    return SUCCESS;
}

// 按位查找链表节点
list_node* select_listnode_by_index(const LinkList list,const int index){
    // 转化索引：base_1 --> base_0
    int select_index = index - 1;
    if(select_index < 0){
        printf("非法索引.\n");
        return NULL;
    }
    // 遍历查找元素
    list_node* current_node = list;
    int current_index = 0;
    while(current_node && current_index <= select_index){
        current_node = current_node->next;
        current_index++;
    }
    // 检查是否查找到位
    if(current_node == NULL){
        printf("索引超过链表长度!\n");
        return NULL;
    }
    // 返回当前节点
    return current_node;
}

// 按值查找链表节点 -- 返回链表中第一个匹配的节点索引
int select_listnode_by_value(const LinkList list,const ELEMENT_TYPE select_data){
    // 遍历寻找
    list_node* current_node = list->next;   // 头节点不存储数据，直接跳过
    int current_index = 0;
    while(current_node && current_node->data != select_data){
        current_node = current_node->next;
        current_index++;
    }
    // 检查是否存在
    if(current_node == NULL) return NOT_FOUND;
    return current_index + 1;     // 转换索引：base_0 --> base_1
}

// 打印链表
void print_linklist(LinkList list){
    list_node* current_node = list->next;       // 跳过头节点
    printf("[Head]-->");
    while (current_node != NULL) {
        printf("[%d]-->",current_node->data);
        current_node = current_node->next;
    }
    printf("NULL\n");
}

// 销毁链表
void destory_linklist(LinkList list){
    /*
        销毁链表的策略为：
            1、定义两个节点，分别为指向头节点的当前节点和为空的临时节点；
            2、临时节点指向当前节点，当前节点移动至当前节点的后继节点；
            3、释放临时节点指向节点的内存空间；
            4、置空整个链表；
    */
   list_node* current_node = list;
   list_node* temp_node = NULL;
   while(current_node){
        temp_node = current_node;
        current_node = current_node->next;
        free(temp_node);
   }
   list = NULL;
}

/*=========================> 单向循环链表 <=========================*/

/* 
    循环单链表最后一个节点的 next 指针指向头节点
    单链表从一个节点出发只能找到相对应的后继节点，循环链表则可以找到所有
    节点
*/
// 初始化循环单链表
LinkList init_C_LinkList(){
    // 申请链表动态内存
    list_node*  head = (list_node *)malloc(sizeof(list_node));
    if(head == NULL) return NULL;
    /*
        单链表中最后一个节点的next指针指向NULL，循环链表则指向头节点
    */
    head->next = head;
    return head;
}

// 循环链表判空 -- 判断头节点的next指针是否指向自己
int is_empty(LinkList c_list){
    return (c_list->next == c_list) ? SUCCESS : FAILURE;
}

// 判断节点是否为最后一个节点 -- 判断下一节点是不是头节点
int is_tail(LinkList c_list, list_node* node){
    return (node->next == c_list) ? SUCCESS : FAILURE;
}