//
// Created by kevin on 2022/8/7.
//

#include <stdlib.h>
#include <stdio.h>

typedef struct TreeNode{
    int weight;
    int parent;
    int lchild;
    int rchild;
}TreeNode;

typedef struct HFTree {
    TreeNode *data;
    int length;
}HFTree;

HFTree *initTree(int *weight, int length) {
    HFTree *T = (HFTree *)malloc(sizeof(HFTree));
    T -> data = (TreeNode *)malloc(sizeof(TreeNode) * (2 * length -1));
    T -> length = length;
    for (int i = 0; i < length; i++) {
        T -> data[i].weight = weight[i];
        T -> data[i].parent = 0;
        T -> data[i].lchild = -1;
        T -> data[i].rchild = -1;
    }
    return T;
}

int *selectMin(HFTree *T) {
    int min = 10000;
    int secondMin = 10000;
    int minIndex;
    int secondIndex;
    for (int i = 0; i < T -> length; i++) {
        if (T -> data[i].parent == 0) {
            if (T -> data[i].weight < min) {
                min = T -> data[i].weight;
                minIndex = i;
            }
        }
    }
    for (int i = 0; i < T -> length; i++) {
        if (T -> data[i].parent == 0 && i != minIndex) {
            if (T -> data[i].weight < secondMin) {
                secondMin = T -> data[i].weight;
                secondIndex = i;
            }
        }
    }
    int *res = (int *)malloc(sizeof(int) * 2);
    res[0] = minIndex;
    res[1] = secondIndex;
    return res;
}

void createHFTree(HFTree *T) {
    int *res;
    int minIndex;
    int secondIndex;
    // HF树全部的节点数量 length = 2n - 1
    // T -> length 表示实际存储数据的节点数量
    int length = T -> length * 2 - 1;
    for (int i = T -> length; i < length; i++) {
        res = selectMin(T);
        //返回最小权值和第二小权值的节点的下标
        minIndex = res[0];
        secondIndex = res[1];
        T -> data[i].weight = T -> data[minIndex].weight + T -> data[secondIndex].weight;
        T -> data[i].lchild = minIndex;
        T -> data[i].rchild = secondIndex;
        T -> data[i].parent = 0;
        T -> data[minIndex].parent = i;
        T -> data[secondIndex].parent = i;
        T -> length++;
    }
}

void preOrder(HFTree *T, int index) {
    if (index != -1) {
        printf("%d ", T -> data[index].weight);
        preOrder(T, T -> data[index].lchild);
        preOrder(T, T -> data[index].rchild);
    }
}

int main() {
    int weight[7] = {5,1,3,6,11,2,4};
    HFTree* T = initTree(weight, 7);
    createHFTree(T);
    preOrder(T, T -> length - 1);
    printf("\n");
    return 0;
}