//Sparse Matrix 又名稀疏矩陣，意思是一個矩陣超多零；使用一般的矩陣註記方法，有浪費空間之虞
//所以使用一個一維陣列只記錄有值得部分
//transpose指矩陣翻轉
#include<stdio.h>

typedef struct term{
    int row;
    int col;
    int val;
} term;

void fastTranspose(struct term a[],struct term b[]) {
    int maxcol = a[0].col;
    //printf("%d\n",maxcol);
    int nonZeroRow[maxcol]; //那一列有幾個資料
    int startingPos[maxcol]; //紀錄到時候要從第幾個b陣列開始放
    for(int i=0;i<maxcol;i++){
        nonZeroRow[i] = 0;
        startingPos[i] = 0;
    }
    b[0].col = a[0].row;
    b[0].row = a[0].col;
    b[0].val = a[0].val;
    for (int i = 1; i <= a[0].val; i++) {
        nonZeroRow[a[i].col]++;
    }
    startingPos[0] = 1;
    for (int i = 1; i <= a[0].col; i++) {
        startingPos[i] = startingPos[i-1] + nonZeroRow[i-1];
    }
    for (int i = 1; i <= a[0].val; i++) {
        int j = startingPos[a[i].col]++;
        b[j].row = a[i].col;
        b[j].col = a[i].row;
        b[j].val = a[i].val;
    }
}

int main(){
    int row , col , lines;
    scanf("%d %d %d",&row,&col,&lines);
    struct term a[lines + 1];
    struct term b[lines + 1];
    a[0].row = row;
    a[0].col = col;
    a[0].val = lines;
    for(int i=1;i<=lines+1;i++){
        scanf("%d %d %d",&a[i].row,&a[i].col,&a[i].val);
    }
    fastTranspose(a,b);
    for(int i=0;i<=lines;i++){
        printf("%d %d %d\n",b[i].row,b[i].col,b[i].val);
    }
}