/*實作河內塔*/
#include<stdio.h>
void hanoi(int n,int source , int auxiliary , int target){
    if(n==1){
        printf("%d %d %d\n",1,source,target);
    }
    else{
        hanoi(n-1,source,target,auxiliary); //把n-1個盤子放到輔助
        printf("%d %d %d\n",n,source,target); //把n號盤放到目標
        hanoi(n-1,auxiliary,source,target); //再把n-1個盤子放回來源
    }
}
int main(){
    int n=0;
    scanf("%d",&n);
    hanoi(n,1,2,3);
}