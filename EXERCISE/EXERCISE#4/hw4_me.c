//把一隻蟑螂放進一個陣列，讓他隨便跑，計算全部走過後花的步驟數

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#define MAX_MOVE 50000

int inmove[] = {-1, 0, 1, 1, 1, 0, -1, -1};
int jmove[] = {1, 1, 1, 0, -1, -1, -1, 0};

int mLen, nLen;
int moveCnt = 0;//移動的總數

bool check(int **arr) {//確認有沒有每一個格子都走過
    for (int i = 0; i < mLen; i++) {
        for (int j = 0; j < nLen; j++) {
            if (arr[i][j] == 0)
                return false;
        }
    }
    return true;
}

void move(int **arr, int x, int y) {
    int which_Direction = rand() % 8;
    if (moveCnt >= MAX_MOVE)
        return;
    //超出邊界了
    if (x + inmove[which_Direction] > mLen - 1 || y + jmove[which_Direction] > nLen - 1 || x + inmove[which_Direction] < 0 || y + jmove[which_Direction] < 0) { 
        move(arr, x, y); 
    } else {
        x += inmove[which_Direction];
        y += jmove[which_Direction];
        arr[x][y]++;
        moveCnt++;
        if (check(arr)){ //都走過了
            return;
        }
        move(arr, x, y);
    }
}


int main() {
    //將當前的系統時間作為種子傳遞給 srand 函數。這個種子用於初始化偽隨機數發生器
    //一旦 srand 被設置了一個新的種子，rand() 函數將使用這個種子生成偽隨機數序列。
    srand(time(NULL));
    char command;
    command = getchar();

    while (command != 'q') {
        if (command == 'a') {
            scanf("%d %d", &mLen, &nLen);
            int **arr = (int **) malloc(mLen * sizeof(int *));
            // initialize
            for (int i = 0; i < mLen; i++) {
                *(arr + i) = calloc(nLen, sizeof(int));
            }
            move(arr, 1, 1);
            printf("%d\n", moveCnt);
            for (int i = 0; i < mLen; i++) {
                for (int j = 0; j < nLen; j++) {
                    printf("%3d ", arr[i][j]); //3d表示三位數，若無3位會補空白
                }
                printf("\n");
            }
            moveCnt = 0;
        } else if (command == 'b') {
            int problem = 0;
            scanf("%d", &problem);
            if (problem == 1) {
                mLen = 15;
                nLen = 15;
                int **arr = (int **) malloc(mLen * sizeof(int *));
                // initialize
                for (int i = 0; i < mLen; i++) {
                    *(arr + i) = calloc(nLen, sizeof(int));
                }
                move(arr, 10, 10);
                printf("%d\n", moveCnt);
                for (int i = 0; i < mLen; i++) {
                    for (int j = 0; j < nLen; j++) {
                        printf("%3d ", arr[i][j]);
                    }
                    printf("\n");
                }
                moveCnt = 0;
            } else if (problem == 2) {
                mLen = 19;
                nLen = 39;
                int **arr = (int **) malloc(mLen * sizeof(int *));
                // initialize
                for (int i = 0; i < mLen; i++) {
                    *(arr + i) = calloc(nLen, sizeof(int));
                }
                move(arr, 1, 1);
                printf("%d\n", moveCnt);
                for (int i = 0; i < mLen; i++) {
                    for (int j = 0; j < nLen; j++) {
                        printf("%3d ", arr[i][j]);
                    }
                    printf("\n");
                }
                moveCnt = 0;
            }
        }
        getchar();//讀調換行符號
        command = getchar();
    }

    return 0;
}

