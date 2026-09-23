/* 定义顺序表，完成顺序表的各种操作 */

#include <stdio.h>
#include <stdlib.h>

// 宏定义 -- 定义常用的宏变量
#define MAX_SIZE 50             // 规定最大的长度为50
#define ELEMENT_TYPE int         // 规定顺序表的数据项类型为int类型（可根据实际的需求进行改变，例如修改为自定义的结构体类型）
#define SUCCESS 1
#define FAILURE 0
#define NOT_FOUND (-1)

// 定义顺序表顺序元素
typedef struct {
    ELEMENT_TYPE *value;        // 顺序表数据域
    size_t size;                // 顺序表长度 -- 初始化为0
}SeqList;


/*
* 初始化顺序表 -- 动态分配内存并初始化长度
*/
SeqList* init_SeqList() {
    // 分配顺序表内存空间
    SeqList* list = (SeqList *)malloc(sizeof(SeqList));
    if(list == NULL){
        printf("顺序表内存分配失败!\n");
        return NULL;
    }
    // 分配顺序表数据域内存空间
    list->value = (ELEMENT_TYPE *)malloc(sizeof(ELEMENT_TYPE) * MAX_SIZE);   // 顺序表大小定义后不可改变
    if(list->value == NULL){
        printf("顺序表数据域内存分配失败!\n");
        free(list);
        return NULL;
    }
    // 初始化长度
    list->size = 0;
    return list;
}

/*
* 向顺序表中插入数据元素
* @param list 操作的顺序表
*/
int insert_seqlist_element(SeqList* list, const ELEMENT_TYPE inserted_data, const int index){
    // 转换索引: base_1  --> base_0
    int insert_index = index - 1;
    // 检查索引以及顺序表是否已满
    if(insert_index < 0 || insert_index > list->size) {
        printf("非法索引.\n");
        return FAILURE;
    }
    if(list->size == MAX_SIZE) {
        printf("顺序表已满.\n");
        return FAILURE;
    }
    // 从表尾向后位移一位创建插入空间
    for(int i = list->size; i > insert_index; i--){
        list->value[i] = list->value[i-1];
    }
    // 插值并更新长度
    list->value[insert_index] = inserted_data;
    list->size++;
    return SUCCESS;
}

/*
* 删除顺序表中指定位置的元素
* @param list 操作的顺序表
* @param index 待删除元素的位置（从1开始）
* @param delete_value 用于接收被删除的元素
*/
int delete_seqlist_element(SeqList* list, const int index, ELEMENT_TYPE* delete_value){
    // 转换索引: base_1  --> base_0
    int delete_index = index - 1;
    // 检查索引以及顺序表是否为空表
    if(delete_index < 0 || delete_index >= list->size){
        printf("非法索引.\n");
        return FAILURE;
    }
    if(list->size == 0){
        printf("顺序表为空表.\n");
        return FAILURE;
    }
    // 将顺序表删除元素的后一位整体前移一位实现元素删除
    *delete_value = list->value[delete_index];    // 记录被删除的元素
    for(int i = delete_index; i < list->size;i++){
        list->value[i] = list->value[i+1];
    }
    list->size--;           // 更新顺序表长度
    return SUCCESS;
}

/*
* 修改顺序表指定位置的元素
* @param list 操作的顺序表
* @param index 待修改元素的位置（从1开始）
* @param update_data 更新后的元素值
*/
int update_seqlist_element(SeqList* list,const int index,ELEMENT_TYPE update_data){
    // 转换索引: base_1  --> base_0
    int update_index = index - 1;
    // 检查索引以及顺序表是否为空表
    if(update_index < 0 || update_index >= list->size){
        printf("非法索引.\n");
        return FAILURE;
    }
    if(list->size == 0){
        printf("顺序表为空表.\n");
        return FAILURE;
    }
    // 执行更新操作
    list->value[update_index] = update_data;
    return SUCCESS;
}

/*
* 按值查找顺序表中的元素，返回第一个匹配的位置（从1开始）
* @param list 操作的顺序表
* @param select_value 待查找的元素值
*/
int select_seqlist_element(const SeqList* list,ELEMENT_TYPE select_value){
    for(int i = 0; i < list->size; i++){
        if(list->value[i] == select_value) return i+1;   // base_0 --> base_1
    }
    return NOT_FOUND;
}

/*
* 打印顺序表中的所有元素
* @param list 操作的顺序表
*/
void print_list(const SeqList* list) {
    printf("完整顺序表为:\n|");
    for (int i = 0;i<list->size;i++) {
        printf(" %d | ",list->value[i]);
    }
    printf("\n");
}

/*
* 释放顺序表占用的内存
* @param list 待释放的顺序表
*/
int free_list(SeqList* list) {
    if (list->value != NULL) {
        free(list->value);
    }
    free(list);
    list = NULL;
    return SUCCESS;
}