//
// Created by KexinCC on 2022/9/8.
//

#include <stdio.h>
#include <stdlib.h>

/**
 *  约定 MAX 代表相邻顶点之间不连通
 *  S数组 记录了目标顶点到其他顶点的最短路径是否求得 (0/1)
 *  P数组 记录了目标顶点到其他顶的的最短路径的前驱节点的下标
 *  D数组 记录了目标顶点到其他顶点的最短路径的长度
 *  主要特点是以起始点为中心向外层层扩展，直到扩展到终点为止
 */
#define MAX 32767

typedef struct Graph {
    char *vexs;
    int **arcs;
    int vexNum;
    int arcNum;
}Graph;

typedef struct Edge {
    char vex;
    int weight;
}Edge;

int getMin(int *d, int *s, Graph *G) {
    int min = MAX;
    int index;
    for (int i = 0; i < G -> vexNum; ++i) {
        // 如果到i的最短路径没有找到 且有更小值则更新最短路径
        // 返回到当前最短路径的下标
        if (!s[i] && d[i] < min) {
            min = d[i];
            index = i;
        }
    }
    return index;
}

Graph *initGraph(int vexNum) {
    Graph *G = (Graph *)malloc(sizeof(Graph));
    G -> vexs = (char *)malloc(sizeof(char) * vexNum);
    G -> arcs = (int **)malloc(sizeof(int *) * vexNum);
    for (int i = 0; i < vexNum; ++i) {
        G -> arcs[i] = (int*)malloc(sizeof(int) * vexNum);
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

void DFS(Graph *G, int *visited, int index) {
    printf("%c\t", G -> vexs[index]);
    visited[index] = 1;
    for (int i = 0; i < G -> vexNum; ++i) {
        if (G -> arcs[index][i] > 0 && G -> arcs[index][i] != MAX && !visited[i]) {
            DFS(G,visited,i);
        }
    }
}

void dijkstra(Graph *G, int index) {
    /*  S数组 记录了目标顶点到其他顶点的最短路径是否求得 (0/1)
        P数组 记录了目标顶点到其他顶点的最短路径的前驱节点的下标
        D数组 记录了目标顶点到其他顶点的最短路径的长度           */
    int *s = (int *)malloc(sizeof(int) * G -> vexNum);
    int *p = (int *)malloc(sizeof(int) * G -> vexNum);
    int *d = (int *)malloc(sizeof(int) * G -> vexNum);

    // 根据 index 初始化三个数组
    for (int i = 0; i < G -> vexNum; ++i) {
        if (G -> arcs[index][i] > 0 && G -> arcs[index][i] != MAX) {
            p[i] = index;
            d[i] = G -> arcs[index][i];
        }
        //没有找到前驱节点
        else {
            p[i] = -1;
            d[i] = MAX;
        }
        if (i == index){
            s[i] = 1;
            d[i] = 0;
        }
        else
            s[i] = 0;
    }

    for (int i = 0; i < G -> vexNum - 1; ++i) {
        int index = getMin(d, s, G);
        // 已经找到了到下标 index 的最短路径 通过遍历 index的相邻节点来找到新的最短路径
        // 由中心向四周扩散
        s[index] = 1;
        for (int j = 0; j < G -> vexNum; ++j) {
            // 指定元素到 下标为 j 元素的最短路径没有找到
            // 并且当前路径长度比原先路径长度更短 则更新 d数组 和 p数组
            if(!s[j] && d[index] + G -> arcs[index][j] < d[j]) {
                d[j] = d[index] + G -> arcs[index][j];
                p[j] = index;
            }
        }
    }
    for (int j = 0; j < G -> vexNum; ++j) {
        printf("%d\t%d\t%d \n", s[j], p[j], d[j]);
    }
}



int main() {
    Graph* G = initGraph(7);
    int* visited = (int*)malloc(sizeof(int) * G -> vexNum);
    for (int i = 0; i < G -> vexNum; i++)
        visited[i] = 0;
    int arcs[7][7] = {
            0, 12, MAX, MAX, MAX, 16, 14,
            12, 0, 10, MAX, MAX, 7, MAX,
            MAX, 10, 0, 3, 5, 6, MAX,
            MAX, MAX, 3, 0, 4, MAX, MAX,
            MAX, MAX, 5, 4, 0, 2, 8,
            16, 7, 6, MAX, 2, 0, 9,
            14, MAX, MAX, MAX, 8, 9, 0
    };
    createGraph(G, "1234567", (int*)arcs);
    DFS(G, visited, 0);
    printf("\n");
    dijkstra(G, 0);
    return 0;
}