/* 队列的链式存储实现 */

#include<stdio.h>
#include<stdlib.h>

// 宏定义 -- 定义常用的宏变量
#define ELEMENT_TYPE int
#define SUCCESS 1
#define FAILURE 0

// 定义节点数据结构
typedef struct que_node{
    ELEMENT_TYPE data;                     // 数据域
    struct que_node* next;                 // 指针域
}que_node;

// 定义队列数据结构
typedef struct{
    que_node* front;        // 队头指针
    que_node* rear;         // 队尾指针
}LinkQue;

// 初始化队列 -- 不带头节点
LinkQue* init_LinkQue(){
    LinkQue* que = (LinkQue *)malloc(sizeof(LinkQue));
    if(que == NULL){
        printf("申请队列内存失败!\n");
        return NULL;
    }
    que->front = NULL;
    que->rear = NULL;
    return que;
}

// 检查队列是否为空
int que_IsEmpty(LinkQue* que){
    return (que->front == NULL) ? SUCCESS : FAILURE;
}

// 入队
int en_LinkQue(LinkQue* que,ELEMENT_TYPE en_data){
    // 申请新节点内存
    que_node* new_node = (que_node *)malloc(sizeof(que_node));
    if(new_node == NULL) return FAILURE;
    new_node->data = en_data;
    new_node->next = NULL;
    // 入队
    if(que_IsEmpty(que)){
        que->front = new_node;
        que->rear = new_node;
    }else{
        que->rear->next = new_node;
        que->rear = new_node;
    }
    return SUCCESS;
}

// 出队
int de_LinkQue(LinkQue* que,ELEMENT_TYPE* de_data){
    if(queue_IsEmpty(que)){
        printf("队列为空!\n");
        return FAILURE;
    }
    que_node* temp_node = que->front;
    *de_data = que->front->data;
    que->front = temp_node->next;
    // 如果出队后为空队 -- 队尾指针置空
    if(que->front == NULL) que->rear = NULL;
    free(temp_node);
    return SUCCESS;
}

// 获取队头元素
int select_LinkQueFront(LinkQue* que,ELEMENT_TYPE* front_data){
    if(queue_IsEmpty(que)){
        printf("队列为空!\n");
        return FAILURE;
    }
    *front_data = que->front->data;
    return SUCCESS;
}