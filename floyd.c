//
// Created by KexinCC on 2022/9/10.
//

/**
 *  folyd 算法 俗称 3for 算法
 *  实现查找最短路径
 */

#include <stdlib.h>
#include <stdio.h>

#define MAX 32767

typedef struct Graph {
    char *vexs;
    int **arcs;
    int vexNum;
    int arcNum;
}Graph;

Graph *initGraph(int vexNum) {
    Graph *G = (Graph *)malloc(sizeof(Graph));
    G -> vexs = (char *)malloc(sizeof(int *) * vexNum);
    G -> arcs = (int **)malloc(sizeof(int *) * vexNum);
    for (int i = 0; i < vexNum; i++) {
        G -> arcs[i] = (int *)malloc(sizeof(int) * vexNum);
    }
    G -> vexNum = vexNum;
    G -> arcNum = 0;
    return G;
}

void createGraph(Graph *G, char *vexs, int *arcs) {
    for (int i = 0; i < G -> vexNum; i++) {
        G -> vexs[i] = vexs[i];
        for (int j = 0; j < G -> vexNum; j++) {
            G -> arcs[i][j] = *(arcs + i * G -> vexNum + j);
            if (G -> arcs[i][j] != 0 && G -> arcs[i][j] != MAX) {
                G -> arcNum++;
            }
        }
    }
    G -> arcNum /= 2;
}

void DFS(Graph *G, int *visited, int index) {
    printf("%c\t", G -> vexs[index]);
    visited[index] = 1;
    for (int i = 0; i < G -> vexNum; ++i) {
        if (G -> arcs[index][i] > 0 && G -> arcs[index][i] != MAX && !visited[i]) {
            DFS(G,visited,i);
        }
    }
    printf("\n");
}

/**
 *
 *  @param G 图
 *  d数组代表了当前节点到其他节点的最短路径
 *  p数组代表了其他节点到当前节点的最短路径的前驱
 */

void floyd(Graph *G) {
    int d[G -> vexNum][G -> vexNum];
    int p[G -> vexNum][G -> vexNum];
    for (int i = 0; i < G -> vexNum; ++i) {
        for (int j = 0; j < G -> vexNum; ++j) {
            d[i][j] = G -> arcs[i][j];
            if (G -> arcs[i][j] > 0 && G -> arcs[i][j] != MAX) {
                p[i][j] = i;
            } else {
                p[i][j] = -1;
            }
        }
    }

    for (int i = 0; i < G -> vexNum; ++i) {
        for (int j = 0; j < G -> vexNum; ++j) {
            for (int k = 0; k < G -> vexNum; ++k) {
                if (d[j][i] + d[i][k] < d[j][k]) {
                    d[j][k] = d[j][i] + d[i][k];
                    p[j][k] = p[i][k];
                }
            }
        }
    }

    for (int i = 0; i < G -> vexNum; ++i) {
        for (int j = 0; j < G -> vexNum; ++j) {
            printf("%d\t", p[i][j]);
        }
        printf("\n");
    }
}

int main() {
    Graph* G = initGraph(4);
    int* visited = (int*)malloc(sizeof(int) * G -> vexNum);
    for (int i = 0; i < G -> vexNum; i++)
        visited[i] = 0;
    int arcs[4][4] = {
            0, 1, MAX, 3,
            1, 0, 2, 2,
            MAX, 2, 0, 8,
            3, 2, 8, 0
    };
    createGraph(G, "1234", (int*)arcs);
    DFS(G, visited, 0);
    floyd(G);
    printf("\n");
    return 0;
}
