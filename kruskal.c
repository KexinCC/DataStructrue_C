//
// Created by KexinCC on 2022/9/6.
//
#include <stdio.h>
#include <stdlib.h>


//2^15-1  约定 权重MAX 代表两个点之间不连通
#define MAX 32767


typedef struct Graph {
    char *vexs;     //顶点
    int **arcs;     //边
    int vexNum;     //顶点数量
    int arcNum;     //边数量
}Graph;

typedef struct Edge {
    int start;      //边起始位置顶点在邻接矩阵中的位置
    int end;        //边结束位置
    int weight;     //权重
}Edge;

Edge *initEdge(Graph *G) {
    int index = 0;
    Edge *edge = (Edge *)malloc(sizeof(Edge) * G -> arcNum);
    for (int i = 0; i < G -> vexNum; ++i) {
        for (int j = i + 1; j < G -> vexNum; ++j) {
            //如果两个点之间联连通，则给边赋值
            if (G -> arcs[i][j] != MAX) {
                edge[index].start = i;
                edge[index].end = j;
                edge[index].weight = G -> arcs[i][j];
                index++;
            }
        }
    }
    return edge;
}

//给边数组排序 ， 方便找到最小边
void sortEdge(Edge* edge, Graph* G) {
    Edge temp;
    for (int i = 0; i < G -> arcNum - 1; i++) {
        for (int j = 0; j < G -> arcNum - i - 1; j++) {
            if (edge[j].weight > edge[j + 1].weight) {
                temp = edge[j];
                edge[j] = edge[j + 1];
                edge[j + 1] = temp;
            }
        }
    }
}

//初始化图，传入顶点的数量作为参数
//构建一个vexNum * vexNum的邻接矩阵来表示 顶点之间的联通情况
Graph *initGraph(int vexNum) {
    Graph *G = (Graph *)malloc(sizeof(Graph));
    G -> vexs = (char *)malloc(sizeof(char) * vexNum);
    G -> arcs = (int **)malloc(sizeof(int *) * vexNum);
    for (int i = 0; i < vexNum; ++i) {
        G -> arcs[i] = malloc(sizeof(int) * vexNum);
    }
    G -> vexNum = vexNum;
    G -> arcNum = 0;
    return G;
}

void createGraph(Graph *G, char *vexs, int *arcs) {
    for (int i = 0 ; i < G -> vexNum; i++) {
        G -> vexs[i] = vexs[i];
        for (int j = 0; j < G -> vexNum; j++) {
            G -> arcs[i][j] = *(arcs + i * G -> vexNum + j);
            // 如果两个顶点之间相连 ， 并且不是其本身
            if (G -> arcs[i][j] != 0 && G -> arcs[i][j] != MAX)
                G -> arcNum ++;
        }
    }
    G -> arcNum /= 2;
}

void kruskal(Graph *G) {
    int *connected = (int *)malloc(sizeof(int) * G -> vexNum);
    for (int i = 0 ; i < G -> vexNum; i++) {
        connected[i] = i;
    }
    Edge *edge = initEdge(G);
    sortEdge(edge, G);
    // 遍历边数组 ， 从小到大遍历边
    for (int i = 0; i < G -> arcNum; ++i) {
        //start 和 end 表示一条边两个顶点的 两个连通增量
        int start = connected[edge[i].start];
        int end = connected[edge[i].end];
        //如果两个连通增量不相等 代表两条边不通 则连通两条边
        if (start != end) {
            printf("v%c --> v%c weight = %d\n", G -> vexs[edge[i].start], G -> vexs[edge[i].end], edge[i].weight);
        }
        //改变 end 顶点及其子节点的连通增量
        for (int j = 0; j < G -> vexNum; ++j) {
            if (connected[j] == end) {
                connected[j] = start;
            }
        }
    }
}

void DFS(Graph *G, int *visited, int index) {
    printf("%c\t", G -> vexs[index]);
    visited[index] = 1;
    for (int i = 0; i < G -> vexNum; ++i) {
        if (G -> arcs[index][i] > 0 && G -> arcs[index][i] != MAX && !visited[i]) {
            DFS(G,visited,i);
        }
    }
}

int main() {
    Graph* G = initGraph(6);
    int* visited = (int*)malloc(sizeof(int) * G -> vexNum);
    for (int i = 0; i < G -> vexNum; i++)
        visited[i] = 0;
    int arcs[6][6] = {
            0, 6, 1, 5, MAX, MAX,
            6, 0, 5, MAX, 3, MAX,
            1, 5, 0, 5, 6, 4,
            5, MAX, 5, 0, MAX, 2,
            MAX, 3, 6, MAX, 0, 6,
            MAX, MAX, 4, 2, 6, 0
    };
    createGraph(G, "ABCDEF", (int*)arcs);

    DFS(G, visited, 0);
    printf("\n");
    kruskal(G);
    return 0;
}

