#include <stdio.h>

struct ELEMENT{
    int parent;
    int height;
};

struct ELEMENT ele[10000];

void INIT(int total){
    for(int i=0;i<total;i++){
        ele[i].height = 0 ;
        ele[i].parent = i ;
    }
}

int FINDROOT(int a1){
    int current = a1;
    //我的parrent不是自己的話，就繼續往上找
    while(ele[current].parent != current){
        current = ele[current].parent;
    }
    return current ;
}

int SAME(int a1,int a2){
    if(FINDROOT(a1)==FINDROOT(a2)){
        return 1;
    }
    else{
        return 0;
    }
}

void UNION(int a1,int a2){
    int rootx = FINDROOT(a1);
    int rooty = FINDROOT(a2);
    if (rootx != rooty){
        if(ele[rooty].height>ele[rootx].height){
            ele[rootx].parent = ele[rooty].parent;
        }
        else{
            ele[rooty].parent = ele[rootx].parent;
        }
        if(ele[rooty].height==ele[rootx].height){
            ele[rootx].height++;
        }
    }
}

int main() {
    int NUM;
    scanf("%d",&NUM);
    for(int i=0;i<NUM;i++){
        int total=0,times=0;
        scanf("%d %d",&total,&times);
        INIT(total);
        for(int j=0;j<times;j++){
            char ope[10];
            int a1,a2;
            scanf("%s",ope);
            if(ope[0]=='u'){
                scanf("%d %d", &a1, &a2);
                UNION(a1,a2);
            }
            else if(ope[0]=='f'){
                scanf("%d", &a1);
                int aa = FINDROOT(a1);
                printf("%d\n",aa);
            }
            else if(ope[0]=='s'){
                scanf("%d %d", &a1, &a2);
                if(SAME(a1,a2)==1){
                    printf("true\n");
                }
                else{
                    printf("false\n");
                }
            }
        }
    }
    return 0;
}
