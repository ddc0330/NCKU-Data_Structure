/*寫兩種演算法(結果一樣)來計算Fibonacci數列
  一為遞迴法，一為迭代法(迴圈)*/
#include <stdio.h>
int recursive(int x){
    if(x==0){
        return 0 ;
    }
    else if(x==1){
        return 1 ;
    }
    else{
        return recursive(x-1) + recursive(x-2) ;
    }
}

int iterative(int x){
    
    if(x==0){
        return 0 ;
    }
    else if(x==1){
        return 1 ;
    }
    else{
        int a=0,b=1,c;
        for(int i=0;i<x-1;i++){
            c = a+b;
            a=b;
            b=c;
        }
        return c ;
    }
}

int main(){
    int n = 0;
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        char a[15] ;
        int x;
        scanf("%s %d",&a,&x);
        if(a[0]=='r'){
            printf("%d\n",recursive(x));
        }
        else if(a[0]=='i'){
            printf("%d\n",iterative(x));
        }
    }
    return 0 ;
}