#include <stdio.h>
#include <stdbool.h>

int h, w, step = 0;
//紀錄原先的陣列
int maze[50][50];
//紀錄那一格是否有被走過，走過的話0->1
int route[50][50] = {0};
//index為第n步驟，用於紀錄第幾步走到哪
int height_index_for_step[2500], width_index_for_step[2500];


bool visited(int height, int width) {
    //走到終點
    if (height == h - 1 && width == w - 1) {
        route[height][width] = 1;
        height_index_for_step[step] = height;
        width_index_for_step[step] = width;
        step ++;
        return true;
    }
    //還在地圖內且maze為0且尚未被訪問過
    if ((height >= 0 && height < h) &&(0 <= width && width < w)&& maze[height][width] == 0 && route[height][width] == 0){

        route[height][width] = 1;
        height_index_for_step[step] = height;
        width_index_for_step[step] = width;

        step += 1;

        if (visited(height - 1, width + 1))
            return true;
        if (visited(height, width + 1))
            return true;
        if (visited(height + 1, width + 1))
            return true;
        if (visited(height + 1, width))
            return true;
        if (visited(height + 1, width - 1))
            return true;
        if (visited(height - 1, width - 1))
            return true;
        if (visited(height - 1, width))
            return true;
        if (visited(height, width - 1))
            return true;
        //走不動的話，這步不算成功
        route[height][width] = 0;
        step -= 1;
        return false;
    }
    return false;
}

int main() {
    scanf("%d%d", &h, &w);
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            scanf("%d", &maze[i][j]);
        }
    }
    if (visited(0, 0)) {
        for (int i = 0; i < step; i++) {
            printf("%d %d\n", height_index_for_step[i], width_index_for_step[i]);
        }
    } else {
        printf("no answer");
    }
}
