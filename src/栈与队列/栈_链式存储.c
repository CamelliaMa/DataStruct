/* 栈的链式存储 -- 实现链栈的操作  */
/*
    栈的链式存储实为只允许在头节点一端进行操作的特殊单链表
    该代码演示的为不带头结点的栈
*/

#include <stdio.h>
#include <stdlib.h>

// 宏定义 -- 定义常用的宏变量
#define ELEMENT_TYPE int         // 规定数据项类型为int类型（可根据实际的需求进行改变，例如修改为自定义的结构体类型）
#define SUCCESS 1
#define FAILURE 0
#define NOT_FOUND (-1)

// 定义链栈节点的数据结构
typedef struct stack_node{
    ELEMENT_TYPE data;              // 数据域      
    struct stack_node* next;        // 指针域
}stack_node;

// 定义链栈数据结构
typedef struct{
    stack_node* StackTop;           // 栈顶指针
    int size;                       // 节点数量
}LinkStack;

/*
* 初始化链栈 -- 不带头节点
*/
LinkStack* init_LinkStack(){
    // 分配内存
    LinkStack* stack = (LinkStack *)malloc(sizeof(LinkStack));
    if(stack == NULL){
        printf("动态分配内存失败!\n");
        return NULL;
    }
    // 设置栈顶以及大小
    stack->StackTop = NULL;
    stack->size = 0;
    return stack;
}

/*
* 判断链栈是否为空
* @param stack 操作的链栈
*/
int stack_IsEmpty(LinkStack* stack){
    return stack->StackTop == NULL;
}

/*
* 元素入栈
* @param stack 操作的链栈
* @param push_data 入栈的数据元素
*/
int push_LinkStack(LinkStack* stack,ELEMENT_TYPE push_data){
    // 创建新节点
    stack_node* new_node = (stack_node *)malloc(sizeof(stack_node));
    if(new_node == NULL){
        printf("分配节点内存失败!\n");
        return FAILURE;
    }
    // 执行入栈操作
    new_node->data = push_data;
    new_node->next = stack->StackTop;
    stack->StackTop = new_node;
    stack->size++;
    return SUCCESS;
}

/*
* 元素出栈
* @param stack 操作的链栈
* @param pop_data 用于接收出栈的元素
*/
int pop_LinkStack(LinkStack* stack,ELEMENT_TYPE* pop_data){
    // 检查栈是否为空
    if(stack_IsEmpty(stack)){
        printf("栈为空!\n");
        return FAILURE;
    }
    stack_node* temp_node = stack->StackTop;    // 使用临时节点
    *pop_data = stack->StackTop->data;          // 取值
    stack->StackTop  = stack->StackTop->next;   // 移动栈顶指针
    free(temp_node);        // 释放原栈顶的内存
    stack->size--;
    return SUCCESS;
}

/*
* 获取链栈的栈顶元素
* @param stack 操作的链栈
* @param top_data 用于接收栈顶元素
*/
int select_LinKStackTop(LinkStack* stack,ELEMENT_TYPE* top_data){
    // 检查栈是否为空
    if(stack_IsEmpty(stack)){
        printf("栈为空!\n");
        return FAILURE;
    }
    *top_data = stack->StackTop->data;
    return SUCCESS;
}

/*
* 释放链栈占用的内存 -- 不断出栈进行销毁
* @param stack 待释放的链栈
*/
void free_LinkStack(LinkStack* stack){
    stack_node* current_node = NULL;
    while(stack->StackTop){
        current_node = stack->StackTop;
        stack->StackTop = stack->StackTop->next;
        free(current_node);
    }
    stack = NULL;
    printf("\n销毁成功!\n");
}

/*
* 主函数 -- 链栈操作演示
*/
int main(){
    LinkStack* stack = init_LinkStack();
    for(int i = 1;i<=10;i++){
        push_LinkStack(stack,i*10);
    }
    ELEMENT_TYPE top_value = 0;
    select_LinKStackTop(stack,&top_value);
    printf("当前栈顶元素为:%d\n",top_value);
    printf("完整出栈顺序为：");
    ELEMENT_TYPE pop_data = 0;
    for(int i = 1;i<=10;i++){
        pop_LinkStack(stack, &pop_data);
        printf("%d ",pop_data);
    }
    free_LinkStack(stack);
    return 0;
}
