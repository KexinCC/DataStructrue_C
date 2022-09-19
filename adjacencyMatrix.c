//
// Created by KexinCC on 2022/8/18.
//
#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 5

typedef struct Graph {
    char *vexs;
    int **arcs;
    int vexNum;
    int arcNum;
}Graph;

typedef struct Queue {
    int front;
    int rear;
    int data[MAXSIZE];
}Queue;

Queue* initQueue() {
    Queue* Q = (Queue*)malloc(sizeof(Queue));
    Q->front = Q->rear = 0;
    return Q;
}

int isFull(Queue* Q) {
    if ((Q->rear + 1) % MAXSIZE == Q->front) {
        return 1;
    }
    else {
        return 0;
    }
}

int isEmpty(Queue* Q) {
    if (Q->front == Q->rear) {
        return 1;
    }
    else {
        return 0;
    }
}

int enQueue(Queue* Q, int data) {
    if (isFull(Q)) {
        return 0;
    }
    else {
        Q->data[Q->rear] = data;
        Q->rear = (Q->rear + 1) % MAXSIZE;
        return 1;
    }
}

int deQueue(Queue* Q) {
    if(isEmpty(Q)) {
        return -1;
    }
    else {
        int data = Q->data[Q->front];
        Q->front = (Q->front + 1) % MAXSIZE;
        return data;
    }
}

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

void creatGraph(Graph *G, char *vexs, int *arcs) {
    for (int i = 0; i < G -> vexNum; i++) {
        G -> vexs[i] = vexs[i];
        for (int j = 0; j < G -> vexNum; j++) {
            G -> arcs[i][j] = *(arcs + i * G -> vexNum + j);
            if (G -> arcs[i][j] != 0) {
                 G -> arcNum++;
            }
        }
    }
    G -> arcNum /= 2;
}

void DFS(Graph *G, int *visited, int index) {
    printf("%c\t", G -> vexs[index]);
    visited[index] = 1;
    for (int i = 0; i < G -> vexNum; i++) {
        if (G -> arcs[index][i] == 1 && !visited[i]) {
            DFS(G, visited, i);
        }
    }
}

void BFS(Graph *G, int *visited, int index) {
    Queue *Q = initQueue();
    printf("%c\t", G -> vexs[index]);
    visited[index] = 1;
    enQueue(Q, index);
    while (!isEmpty(Q)) {
        int i = deQueue(Q);
        for (int j = 0; j < G -> vexNum; j++) {
            if (G -> arcs[i][j] == 1 && !visited[j]) {
                printf("%c\t", G -> vexs[j]);
                visited[j] = 1;
                enQueue(Q,j);
            }
        }
    }
}

int main() {
    Graph *G = initGraph(5);
    int *visited = (int *)malloc(sizeof(int) * G -> vexNum);
    for (int i = 0; i < G -> vexNum; ++i) {
        visited[i] = 0;
    }
    int arcs[5][5] = {
            0,1,1,1,0,
            1,0,1,1,1,
            1,1,0,0,1,
            0,1,0,1,0
    };
    creatGraph(G, "ABCDE",arcs[0]);
    printf("%p\n",arcs[0]);
    printf("%p\n",&arcs[0]);
    printf("%p\n",&arcs[0][0]);
    printf("%p\n",arcs);
    DFS(G, visited, 0);
    printf("\n");
    for (int i = 0; i < G -> vexNum; ++i) {
        visited[i] = 0;
    }
    BFS(G, visited, 0);
    return 0;
}