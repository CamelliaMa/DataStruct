/* 串的三种存储结构 */


#include<stdio.h>
#include<stdlib.h>

/* 
【定长存储】：
    使用一片连续的存储空间存储字符串，存储结构类似于线性表的顺序存储
    串的长度不能超过预设的最大长度，否则会发生截断.
*/
#define MAXLENGTH 255
typedef struct{
    char value[MAXLENGTH];
    int length;
}String_1;

/*
【动态分配】：
    不预设大小而是根据串的大小动态分配内存.
*/
typedef struct{
    char* value;
    int length;
}String_2;

/*
【块链存储】：
    使用链表存储，每个链表节点存储一个或多个字符(块大小)，不足的使用 '#' 字符补足.
    无法进行随机存取
*/
typedef struct node{
    char* value;                // 数据域 -- 可存储一个或多个字符
    struct node* next;          // 指针域
}String_3;


int main(){
    printf("hello");
    return 0;
}