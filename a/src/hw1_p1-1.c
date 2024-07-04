#include <stdio.h>
#include <ctype.h>
#include <string.h>
#define MAX_SIZE 100

//優先序函式
int precedence(char operator){
    if (operator == '+' || operator == '-')
        return 1;
    if (operator == '*' || operator == '/')
        return 2;
    return 0;
}

int main() {
    char infix[MAX_SIZE], postfix[MAX_SIZE] , stack[MAX_SIZE];
    scanf("%s", infix);

    int i=0,j=0;
    int len = strlen(infix);
    int top = -1;
    for(i=0,j=0;i<len;i++){
        //如果是操作數就直接先放進postfix
        if(isalnum(infix[i])){
            postfix[j++] = infix[i];
        }
        //左括號
        else if(infix[i] == '('){
            stack[++top] = infix[i];
        }
        //右括號
        else if(infix[i] == ')'){
            while (top > -1 && stack[top] != '(') 
                postfix[j++] = stack[top--];
        }
        //  若要放入stack的優先序小於等於stack裡的就pop直到可以放入stack
        else if(infix[i] == '+' || infix[i] == '-' ||infix[i] == '*' ||infix[i] == '/'){
            while (top > -1 && (precedence(infix[i]) <= precedence(stack[top])))
                postfix[j++] = stack[top--];
            stack[++top] = infix[i]; 
        }
    }
    //所有infix跑完了，把stack跑完
    while(top>-1){
        if(stack[top]=='('){
            top--;
        }
        else{
            postfix[j++] = stack[top--];
        }
    }
    postfix[j] = '\0';
    printf("%s", postfix);
    return 0;
}
