/*
    模式匹配: 在主串中查找与模式串完全相同的字串并返回子串位置.
    【注】: 
        所有字符串数组均为base_1.
*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>


/*
* 朴素匹配算法 -- 暴力求解 最坏复杂度：O(n*m)
* @param S 主串
* @param T 模式串
*/
int simple_attern_match(char* S,char* T){
    int S_index = 1,T_index = 1;        // 匹配指针
    // 获取两个字符串大小 
    int S_length = strlen(S);
    int T_length = strlen(T);
    // 开始循环匹配
    while(S_index <= S_length && T_index <= T_length){
        if(S[S_index] == T[T_index]){   // 当前字符匹配成功 -- 前进
            S_index++;
            T_index++;
        }else{          // 当前字符匹配失败 -- 回退
            S_index = S_index - T_index + 2;
            T_index = 1;
        }
    }
    if(T_index > T_length) return S_index-T_length;     // 匹配成功 -- 返回位置
    else return 0;                                      // 匹配失败 -- 返回0
}


/*
* 辅助函数 -- 构建next数组
* @param next next数组指针 
* @param str  模板串指针
*/
void get_next(int* next,char* str){
    int i = 1,j = 0;
    next[1] = 0;
    while(i < strlen(str)){
        if(j == 0 || str[i] == str[j]){
            i++;
            j++;
            next[i] = j;
        }else{
            j = next[j];
        }
    }
}

/*
* 辅助函数 -- 构建nextval数组
* @param nextval nextval数组指针 
* @param str  模板串指针
*/
void get_nextval(int* nextval,char* str){
    int i = 1,j = 0;
    nextval[1] = 0;
    while(i < strlen(str)){
        if(j == 0 || str[i] == str[j]){
            i++;
            j++;
            if(str[i] != str[j]) nextval[i] = j;
            else nextval[i] = nextval[j];
        }else j = nextval[j];
    }
}


/*
* KMP匹配算法
* @param S 主串
* @param T 模式串
*/
int KMP_pattern_match(char* S,char* T){
    int S_index = 1,T_index = 1;        // 匹配指针
    // 获取两个字符串大小
    int S_length = strlen(S);
    int T_length = strlen(T);
    int next[T_length];
    get_next(next,T);
    // 开始循环匹配
    while(S_index <= S_length && T_index <= T_length){
        if(T_index == 0 || S[S_index] == T[T_index]){   // 当前字符匹配成功 -- 前进
            S_index++;
            T_index++;
        }else{          // 当前字符匹配失败 -- 滑动模串
            T_index = next[T_index];
        }
    }
    if(T_index > T_length) return S_index-T_length;     // 匹配成功 -- 返回位置
    else return 0;                                      // 匹配失败 -- 返回0
}



int main(){
    char S[] = "ababcabd";
    char T[] = "abc"; 
    printf("%d",KMP_pattern_match(S,T));
    return 0;
}