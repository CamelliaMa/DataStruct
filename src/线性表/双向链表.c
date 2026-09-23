/* 定义双向链表，实现双向链表的操作 */

#include <stdio.h>
#include <stdlib.h>

// 宏定义 -- 定义常用的宏变量
#define ELEMENT_TYPE int         // 规定顺序表的数据项类型为int类型（可根据实际的需求进行改变，例如修改为自定义的结构体类型）
#define SUCCESS 1
#define FAILURE 0
#define NOT_FOUND (-1)

// 定义双向链表节点数据结构 
typedef struct D_list_node{
    struct D_list_node* prior;      // 前驱节点指针
    ELEMENT_TYPE data;              // 数据域
    struct D_list_node* next;       // 后继结点指针
}D_list_node,*D_LinkList;           // 前者指向节点， 后者指向头节点代表整条双向链表


/*
* 初始化双向链表 -- 创建带头节点的空链表
*/
D_LinkList init_D_LinkList(){
    // 申请头节点内存
    D_list_node* head = (D_list_node *)malloc(sizeof(D_list_node));
    if(head == NULL){
        printf("初始化头节点失败!\n");
        return NULL;
    }
    head->prior = NULL;       // 双向链表头节点前驱指针永远为NULL
    head->next = NULL;
    return head;
} 

/*
* 在双向链表指定节点之后插入新节点
* @param prior_node 插入位置的前驱节点
* @param insert_node 待插入的节点
*/
int insert_D_LinkList_node(D_list_node* prior_node,D_list_node* insert_node){
    // 检查节点是否为空节点
    if(prior_node == NULL || insert_node == NULL){
        printf("节点为空!\n");
        return FAILURE;
    }
    // 执行插入操作
    insert_node->next = prior_node->next;
    if(prior_node->next != NULL){     // prior_node 不是最后一个节点
        prior_node->next->prior = insert_node;
    }
    insert_node->prior = prior_node;
    prior_node->next = insert_node;
    return SUCCESS;
}

/*
* 删除指定节点的后继节点
* @param node 操作的节点
*/
int delete_next_node(D_list_node* node){
    if(node == NULL){      // 检查节点是否为空
        printf("节点为空!\n");
        return FAILURE;
    }
    D_list_node* deleted_node = node->next;
    if(deleted_node == NULL){       // 检查指定节点有没有后继节点
        printf("该节点没有后继节点!\n");
        return FAILURE;
    }
    node->next = deleted_node->next;
    if(deleted_node->next != NULL){   // 检查要删除的节点是不是最后一个节点
        deleted_node->next->prior = node;
    }
    free(deleted_node);
    return SUCCESS;
}

/*
* 打印指定节点的前驱节点和后继节点
* @param node 指定的节点
*/
void print_list(D_list_node* node){
    if(node == NULL){      // 检查节点是否为空
        printf("节点为空!\n");
        return FAILURE;
    }
    if(node->prior != NULL){      // 检查节点是否为空
        printf("指定节点的前驱节点为:\n");
        D_list_node* current_node = node->prior;
        while(current_node != NULL){    // 前向遍历
            print("[%d]<-->",current_node->data);
            current_node = current_node->prior;
        }
    }
    if(node->prior != NULL){      // 检查节点是否为空
        printf("指定节点的后继节点为:\n");
        D_list_node* current_node = node->next;
        while(current_node != NULL){    // 后向遍历
            print("[%d]<-->",current_node->data);
            current_node = current_node->next;
        }
    }
}


/*=========================> 双向循环链表 <=========================*/

/*
    表头节点的prior指针指向表尾节点 | 表尾节点的next指针指向表头节点
*/

/*
* 初始化双向循环链表
*/
D_LinkList init_D_C_LinkList(){
    D_list_node* head = (D_list_node *)malloc(sizeof(D_list_node));
    if(head == NULL) return NULL;
    // 头节点指向头节点
    head->prior = head;
    head->next = head;
    return head;
}

/*
* 判断双向循环链表是否为空
* @param d_c_list 操作的双向循环链表
*/
int is_empty(D_LinkList d_c_list){
    return(d_c_list->next == d_c_list ) ? SUCCESS : FAILURE;
}

/*
* 判断节点是否为双向循环链表的最后一个节点
* @param d_c_list 操作的双向循环链表
* @param node 待判断的节点
*/
int is_tail(D_LinkList d_c_list, D_list_node* node){
    return (node->next == d_c_list) ? SUCCESS : FAILURE;
}

/*
* 在双向循环链表指定节点之后插入新节点
* @param prior_node 插入位置的前驱节点
* @param insert_node 待插入的节点
*/
int insert_D_C_LinkList_node(D_list_node* prior_node,D_list_node* insert_node){
    if(prior_node == NULL || insert_node == NULL) return FAILURE;
    // 执行插入操作
    insert_node->next = prior_node->next;
    /*
        此处因为循环关系，无需判断是否为最后一个节点
    */
    prior_node->next->prior = insert_node;
    insert_node->prior = prior_node;
    prior_node->next = insert_node;
    return SUCCESS;
}

/*
* 删除双向循环链表中指定节点的后继节点
* @param prior_node 被删除节点的前驱节点
*/
int delete_D_C_LinkList_node(D_list_node* prior_node){
    D_list_node* delete_node = prior_node->next;
    // 执行插入操作
    prior_node->next = delete_node->next;
    delete_node->next->prior = prior_node;
    free(delete_node);
    return SUCCESS; 
}