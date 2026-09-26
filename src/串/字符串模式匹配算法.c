/*
    模式匹配: 在主串中查找与模式串完全相同的字串并返回子串位置.
    【注】: 
        所有字符串数组均为base_1.所有字符串下表为0位置存储 '#'
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
    // 获取两个字符串大小 -- -1去除占位符 '#' 的影响
    int S_length = strlen(S) - 1;
    int T_length = strlen(T) - 1;
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
    else return 0;                                      // 匹配失败 -- 放回0
}

/*
* KMP匹配算法
* @param S 主串
* @param T 模式串
*/
int KMP_attern_match(char* S,char* T){
    
}



int main(){
    char S[] = "#ababcabd";
    char T[] = "#abe"; 
    printf("%d",simple_attern_match(S,T));
    return 0;
}