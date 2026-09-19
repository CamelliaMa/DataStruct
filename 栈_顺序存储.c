/* 栈的顺序存储 -- 实现顺序栈的操作 -- 先进后出、后进先出 */

#include <stdio.h>
#include <stdlib.h>
#include<string.h>

// 宏定义 -- 定义常用的宏变量
#define MAX_SIZE 50             // 规定最大的长度为50
#define ELEMENT_TYPE char        // 规定数据项类型为char类型（可根据实际的需求进行改变，例如修改为自定义的结构体类型）
#define SUCCESS 1
#define FAILURE 0
#define NOT_FOUND (-1)

// 定义栈的数据结构
typedef struct{
    ELEMENT_TYPE* data;       // 数据域
    int stackTop;             // 栈顶指针 -- 指向栈顶,初始化为0
}SeqStack;

// 初始化顺序栈
SeqStack* init_SeqStack(){
    // 申请栈内存
    SeqStack* stack  = (SeqStack *)malloc(sizeof(SeqStack));
    if(stack == NULL){
        printf("栈内存申请失败!\n");
        return NULL;
    }
    // 申请数据域内存
    stack->data = (ELEMENT_TYPE *)malloc(sizeof(ELEMENT_TYPE) * MAX_SIZE);
    if(stack->data == NULL){
        printf("数据域内存申请失败!\n");
        free(stack);
        return NULL;
    }
    stack->stackTop = 0;   // 栈顶指针默认为0 -- 指向下一个入栈元素的位置
    return stack;
}

// 检查栈是否已满
int stack_IsFull(SeqStack* stack){
    return (stack->stackTop == MAX_SIZE) ? SUCCESS : FAILURE;
}

// 检查栈是否为空
int stack_IsEmpty(SeqStack* stack){
    return (stack->stackTop == 0) ? SUCCESS : FAILURE;
}

// 入栈
int push_SeqStack(SeqStack* stack, ELEMENT_TYPE push_data){
    // 检查栈是否已满
    if(stack_IsFull(stack)){
        printf("栈已满!\n");
        return FAILURE;
    }
    // 执行入栈操作
    /*
        该复合语句执行的顺序为：
        1、stack->data[stack->stackTop] = push_data;
        2、stackTop++;
    */
    stack->data[stack->stackTop++] = push_data;
    return SUCCESS;
}

// 出栈
int pop_SeqStack(SeqStack* stack, ELEMENT_TYPE* pop_data){
    // 检查是不是空栈
    if(stack_IsEmpty(stack)){
        printf("栈为空!\n");
        return FAILURE;
    }
    // 执行出栈操作
    /*
        该复合语句执行的顺序为：
        1、stackTop--;
        2、stack->data[stack->stackTop] = pop_data;
    */
    *pop_data = stack->data[--stack->stackTop];
    return SUCCESS;
}

// 获取栈顶元素
int select_SeqStackTop(SeqStack* stack,ELEMENT_TYPE* top_value){
    if(stack_IsEmpty(stack)){
        printf("栈为空!\n");
        return FAILURE;
    }
    *top_value = stack->data[stack->stackTop - 1];
    return SUCCESS;
}

// 释放栈内存
void free_SeqStack(SeqStack* stack){
    if(stack->data != NULL){
        free(stack->data);
    }
    free(stack);
    stack = NULL;
}


/*======================================> 括号匹配算法 <======================================*/
/*  
    【算法思想】：
    1. 初始化一个空栈，顺序扫描输入的括号序列；
    2. 若遇到左括号，执行压栈操作，表示新增一个待匹配的期待，且其优先级最高（栈顶永远持有最高优先级）；
    3. 若遇到右括号，则检查栈是否为空：若栈非空而且栈顶的左括号与当前的右括号匹配，则执行出栈操作，
       完成一次匹配操作；否则，括号序列非法，算法终止；
    4. 扫描结束，若栈为空，则括号序列合法；否则，存在未匹配的左括号，序列非法。

    【算法测试】：
    使用顺序栈检查括号字符串是否匹配
    "({[()]})"      -->    SUCCESS
    "({[[}]]})"     -->    FAILURE
*/

// 括号匹配算法
int backets_match(char backets[]){
    // 计算字符串长度
    /*
        【注】：此处不能使用 sizeof(backets) / sizeof(backets[0]) 进行计算，在传参过程中
            字符串数组会自动退化为指针导致大小改变，无法计算数组大小(字符串长度).
    */ 
    int char_length = strlen(backets);
    if(char_length % 2 != 0) return FAILURE;        // 长度必须为偶数才能进行匹配
    // 初始化顺序栈
    SeqStack* stack = init_SeqStack();
    // 开始进行匹算法
    for(int i = 0; i < char_length; i++){
        // 扫描到左括号 -- 入栈
        if(backets[i] == '(' || backets[i] == '[' || backets[i] == '{'){
            push_SeqStack(stack,backets[i]);
        }else{      // 扫描到右括号 -- 栈顶元素出栈并与当前右括号比匹配
            if(stack_IsEmpty(stack)) return FAILURE;  // 右括号存在但栈为空 -- 匹配失败
            char top_element;
            pop_SeqStack(stack,&top_element); // 栈顶元素出栈
            // 匹配
            if(backets[i] == ')' && top_element != '(') return FAILURE;
            if(backets[i] == ']' && top_element != '[') return FAILURE;
            if(backets[i] == '}' && top_element != '{') return FAILURE;
        }
    }
    // 如果栈为空则说明匹配成功 
    int result = stack_IsEmpty(stack);
    free_SeqStack(stack);
    return result;
} // 测试通过 -- 算法正确运行



/*======================================> 中缀表达式转后缀表达式算法 <======================================*/

// 辅助函数 -- 判断字符是否为运算符
int is_operator(char ch){
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/');
}

// 辅助函数 -- 判断运算符号优先级(数字越大表明优先级越高)
int get_priority(char operator_char){
    switch(operator_char){
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        default:
            return 0;     // 括号或者非运算符返回 0   
    };
}

/*
    【算法思想】：
    从头到尾扫描表达式并执行以下操作：
    1. 遇到操作数，直接加入后缀表达式；
    2. 遇到界限符，执行下面的操作：
        1). 左括号：直接入栈；
        2). 右括号：不执行入栈操作，且不断执行出栈操作将栈顶符号加入后缀表达式中直到遇到左括号，将其出栈并丢弃；
    3. 遇到运算符，执行以下操作：
        1). 若其优先级高于栈顶的运算符或者栈顶为左括号，直接执行入栈操作；
        2). 若其优先级低于或等于当前栈顶的运算符，则依次弹出当前栈顶的运算符并加入后缀表达式中，直到遇到优先级更低的符号
            或者栈空或栈顶为左括号为止，然后再将当前运算符入栈。
*/

// 中缀表达式转后缀表达式算法 -- [infix]：中缀表达式 [postfix]：转换后的后缀表达式
void infix_to_postfix(char* infix, char* postfix){
    // 初始化一个栈承载运算符
    SeqStack* operator_stack = init_SeqStack();
    int length = strlen(infix);    // 获取表达式长度
    int postfix_index = 0;      // 后缀表达式索引指针
    char top_element;           // 栈顶元素

    // 扫描整个中缀表达式 -- 开始转换
    for(int current_index = 0; current_index < length; current_index++){
        char current_char = infix[current_index];       //  提取单字符
        // 1. 空格直接跳过
        if(current_char == ' ') continue;
        // 2. 操作数直接加入表达式中
        else if((current_char >= 'a' && current_char <= 'z') || 
        (current_char >= 'A' && current_char <= 'Z') || (current_char >= '0' && current_char <= '9')){
            postfix[postfix_index++] = current_char;
        }
        // 3. 左括号直接入栈
        else if(current_char == '(') push_SeqStack(operator_stack, current_char);
        // 4. 右括号不断执行出栈操作将栈顶符号加入后缀表达式中直到遇到左括号，将其出栈并丢弃
        else if( current_char == ')' ){
            while(!stack_IsEmpty(operator_stack)){
                select_SeqStackTop(operator_stack,&top_element);        // 获取栈顶元素
                if(top_element == '('){         // 左括号直接出栈并丢弃
                    pop_SeqStack(operator_stack,&top_element);
                    break;
                }
                pop_SeqStack(operator_stack,&top_element);
                postfix[postfix_index++] = top_element;
            }
        }
        // 5. 运算符分支
        else if(is_operator(current_char)){
            while(!stack_IsEmpty(operator_stack)){
                select_SeqStackTop(operator_stack,&top_element);        // 获取栈顶元素
                // 栈顶不是左括号而且优先级高于或等于当前运算符时执行出栈操作并加入后缀表达式
                if(top_element != '(' && get_priority(top_element) >= get_priority(current_char)){
                    pop_SeqStack(operator_stack,&top_element);
                    postfix[postfix_index++] = top_element;
                }else break;
            }
            // 将当前运算符号入栈
            push_SeqStack(operator_stack,current_char);    
        }
    }
    // 扫描结束，清空栈中的运算符
    while(!stack_IsEmpty(operator_stack)){
        pop_SeqStack(operator_stack,&top_element);
        postfix[postfix_index++] = top_element;
    }
    // 完善后缀表达式并销毁顺序栈
    postfix[postfix_index] = '\0';
    free_SeqStack(operator_stack);
}// 测试通过 -- 算法正确
