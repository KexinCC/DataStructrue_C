//
// Created by KexinCC on 2022/9/10.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
}Node;

typedef struct Graph {
    char *vexs;
    int **arcs;
    int vexNum;
    int arcNum;
}Graph;

Node *initStack() {
    Node *stack = (Node *)malloc(sizeof(Node));
    stack -> data = 0;
    stack -> next = NULL;
    return stack;
}

int isEmpty(Node *node) {
    if (node -> next == NULL) {
        return 1;
    } else {
        return 0;
    }
}

void push(Node *stack, int data) {
    Node *node = (Node *)malloc(sizeof(Node));
    node -> data = data;
    node -> next = stack -> next;
    stack -> next = node;
    stack -> data++;
}

int pop(Node *stack) {
    if (!isEmpty(stack)) {
        Node *node = stack -> next;
        stack -> next = node -> next;
        stack -> data--;
        int data = node -> data;
        free(node);
        return data;
    } else {
        return -1;
    }
}


Graph *initGraph(int vexNum) {
    Graph *G = (Graph *)malloc(sizeof(Graph));
    G -> vexs = (char *)malloc(sizeof(char) * vexNum);
    G -> arcs = (int **)malloc(sizeof(int*) * vexNum);
    for (int i = 0; i < vexNum; ++i) {
        G -> arcs[i] = (int *)malloc(sizeof(int) * vexNum);
    }
    G -> vexNum = vexNum;
    G -> arcNum = 0;
}

void createGraph(Graph *G, char *vexs, int *arcs) {
    for (int i = 0; i < G -> vexNum; ++i) {
        G -> vexs[i] = vexs[i];
        for (int j = 0; j < G -> vexNum; ++j) {
            G -> arcs[i][j] = *(arcs + i * G -> vexNum + j);
            if (G -> arcs[i][j] != 0) {
                G -> arcNum++;
            }
        }
        G -> arcNum /= 2;
    }
}

void DFS(Graph *G, int *visited, int index) {
    printf("%c\t", G -> vexs[index]);
    visited[index] = 1;
    for (int i = 0; i < G -> vexNum; ++i) {
        if (G -> arcs[index][i] && !visited[i]) {
            DFS(G, visited, i);
        }
    }
}

int *findInDegrees(Graph *G) {
    int *inDegrees = (int *)malloc(sizeof(G -> vexNum));
    for (int i = 0; i < G -> vexNum; ++i) {
        inDegrees[i] = 0;
    }
    for (int i = 0; i < G -> vexNum; ++i) {
        for (int j = 0; j < G -> vexNum; ++j) {
            if (G -> arcs[i][j]) {
                inDegrees[j]++;
            }
        }
    }
    return inDegrees;
}

void topologicalSort(Graph* G) {
    int index = 0; // 记录 top数组的实际的长度加一
    int *top = (int *)malloc(sizeof(int) * G -> vexNum);
    int *inDegrees = findInDegrees(G);
    Node *stack = initStack();
    for (int i = 0; i < G -> vexNum; ++i) {
        if (inDegrees[i] == 0) {
            push(stack, i);
        }
    }
    while (!isEmpty(stack)) {
        int vex = pop(stack);
        top[index++] = vex;
        for (int i = 0; i < G -> vexNum; ++i) {
            // 如果入度为 0 的节点连接了其他节点
            if (G -> arcs[vex][i]) {
                inDegrees[i]--;
                if (inDegrees[i] == 0) {
                    push(stack, i);
                }
            }
        }

        // index 表示top数组实际的长度加一
        // top 数组保存了 排序后节点的下标
        // vexs 是char数组 所以用top数组中的元素作为下标遍历取出
        for (int i = 0; i < index; ++i) {
            printf("%c ", G -> vexs[top[i]]);
        }
        printf("\n");
    }
    for (int i = 0; i < index; ++i) {
        printf("%c ", G -> vexs[top[i]]);
    }
    printf("\n");
}

int main() {
    Graph* G = initGraph(6);
    int* visited = (int*)malloc(sizeof(int) * G -> vexNum);
    for (int i = 0; i < G -> vexNum; i++)
        visited[i] = 0;
    int arcs[6][6] = {
            0,1,1,1,0,0,
            0,0,0,0,0,0,
            0,1,0,0,1,0,
            0,0,0,0,1,0,
            0,0,0,0,0,0,
            0,0,0,1,1,0
    };
    createGraph(G, "123456", (int *)arcs);
    DFS(G, visited, 0);
    printf("\n");
    topologicalSort(G);
    return 0;
}