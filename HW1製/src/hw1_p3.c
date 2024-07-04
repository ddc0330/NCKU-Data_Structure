#include <stdio.h>
#include <stdlib.h>

struct Edge {
    int source, destination, weight;
};
//一個棍子左右各接一個球深度是0，再接一個就+1
struct Subset {
    int parent;
    int rank;
};

int SortEdges(const void* a,const void* b){
    return (((struct Edge*)a)->weight - ((struct Edge*)b)->weight);
}

int FIND(struct Subset* subsets ,int a){
    if(subsets[a].parent != a){
        subsets[a].parent = FIND(subsets, subsets[a].parent);
    }
    return subsets[a].parent;
}

int main() {
    long long int V, E, mincost = 0;
    scanf("%lld %lld", &V, &E);
    struct Edge edges[E];
    struct Subset subsets[V];
    for(int i = 0; i < E; i++){
        scanf("%d %d %d", &edges[i].source, &edges[i].destination, &edges[i].weight);
    }
    for(int i = 0; i < V; i++){
        subsets[i].parent = i;
        subsets[i].rank = 0;
    }
    //Kruskal's algorithm
    //把邊生序排列
    qsort(edges,E,sizeof(struct Edge),SortEdges);
    for(int i = 0; i < E; i++){
        //找兩端，包含先前加入的邊
        int x = FIND(subsets,edges[i].source);
        int y = FIND(subsets,edges[i].destination);
        //沒有圍成圓，就把那個邊算進來，
        if(x!=y){
            mincost+=edges[i].weight;
            //union，比較長那端當老大，若一樣長那隨便
            if(subsets[x].rank<subsets[y].rank){
                subsets[x].parent = y;
            }
            else if(subsets[x].rank>subsets[y].rank){
                subsets[y].parent = x;
            }
            else if(subsets[x].rank==subsets[y].rank){
                subsets[y].parent = x;
                subsets[x].rank++;
            }
        }
    }
    printf("%lld",mincost);
    return 0;
}
