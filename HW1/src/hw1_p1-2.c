#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#define MAX_SIZE 100

int isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

int main() {
    //開二階，以string為元素做存放
    char *prefix_stack[MAX_SIZE];
    char postfix[MAX_SIZE];
    scanf("%s", postfix);

    int len = strlen(postfix);
    int i=0,j=0;
    int top = -1;
    
    
    for (i = 0 , j=0 ; i < len; i++) {
        //用開好空間的變數去等於沒開好空間的二階stack才可以成功編譯
        char* a = calloc(MAX_SIZE,sizeof(char));
        a[0] = postfix[i];
        //如果不是運算符，加入stack
        if (!isOperator(postfix[i])){
            //push
            prefix_stack[++top] = a;
        }
        //運算符，抓前兩個，把運算符放最前面再放回stack
        else{
            top--;  
            strcat(a,prefix_stack[top]);
            strcat(a,prefix_stack[top+1]);
            prefix_stack[top] = a;
        }
    }
    printf("%s",prefix_stack[0]);
    return 0;
}
