/* 队列顺序存储定义 -- 顺序队列的操作实现 */
/*  
    队列特性为先进先出（First In First Out）
    队列是一种特殊的线性表，只允许在表头进行删除操作（出队）
    只允许在表尾进行新增操作（入队）
*/

#include<stdio.h>
#include<stdlib.h>

// 宏定义 -- 定义常量变量
#define MAX_SIZE 50
#define ELEMENT_TYPE int
#define SUCCESS 1
#define FAILURE 0

// 定义队列的数据结构
typedef struct{
    ELEMENT_TYPE* data;         // 数据域
    int front,rear;              // 队头指针 | 队尾指针
}SeqQue;

/*
* 初始化顺序队列 -- 动态分配内存并初始化队头队尾指针
*/
SeqQue* init_SeqQue(){
    // 申请队列内存
    SeqQue* que = (SeqQue *)malloc(sizeof(SeqQue));
    if(que == NULL){
        printf("队列内存申请失败!\n");
        return NULL;
    }
    // 申请队列数据域内存
    que->data = (ELEMENT_TYPE *)malloc(sizeof(ELEMENT_TYPE) * MAX_SIZE);
    if(que->data == NULL){
        printf("队列数据域内存申请失败!\n");
        free(que);
        return NULL;
    }
    que->front = que->rear = 0;
    return que;
}

/*
* 判断队列是否为空
* @param que 操作的队列
*/
int que_IsEmpty(SeqQue* que){
    return (que->front == que->rear) ? SUCCESS : FAILURE;
}

/*
* 判断队列是否已满
* @param que 操作的队列
*/
int que_IsFull(SeqQue* que){
    return ((que->rear + 1)%MAX_SIZE == que->front) ? SUCCESS : FAILURE;
}

/*
* 元素入队 -- 循环队列
* @param que 操作的队列
* @param en_data 入队的数据元素
*/
int en_SeqQue(SeqQue* que,ELEMENT_TYPE en_data){
    if(que_IsFull(que)){
        printf("队列已满!\n");
        return FAILURE;
    }
    // 执行入队操作
    que->data[que->rear] = en_data;
    que->rear = (que->rear + 1) % MAX_SIZE;
    return SUCCESS;
}

/*
* 元素出队
* @param que 操作的队列
* @param de_data 用于接收出队的元素
*/
int de_SeqQue(SeqQue* que,ELEMENT_TYPE* de_data){
    if(que_IsEmpty(que)){
        printf("队列为空!\n");
        return FAILURE;
    }
    // 执行出队操作
    *de_data = que->data[que->front];
    que->front = (que->front + 1) % MAX_SIZE;
    return SUCCESS;
}

/*
* 获取队头元素
* @param que 操作的队列
* @param front_data 用于接收队头元素
*/
int select_SeqQueFront(SeqQue* que,ELEMENT_TYPE* front_data){
    if(que_IsEmpty(que)){
        printf("队列为空!\n");
        return FAILURE;
    }
    *front_data = que->data[que->front];
    return SUCCESS;
}

/*
* 获取队列长度
* @param que 操作的队列
*/
int select_SeqQueSize(SeqQue* que){
    if(que_IsEmpty(que)){
        printf("队列为空!\n");
        return FAILURE;
    }
    // 计算公式为（尾指针 - 头指针 + MAX_SIZE）% MAX_SIZE
    return (que->rear - que->front + MAX_SIZE) % MAX_SIZE;
}