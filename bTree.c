//
// Created by KexinCC on 2022/9/18.
//

#include <stdio.h>
#include <stdlib.h>

/**
 *  level       B树的阶数 (一个节点最多可以有几个孩子节点)
 *  keyNum      关键字的个数
 *  childNum    孩子数量
 *  keys *      关键字数组
 *  parent      父亲的指针
 *  children    孩子指针
 */

typedef struct Node {
    int level;
    int keyNum;
    int childNum;
    int *keys;
    struct Node *parent;
    struct Node **children;
}Node;

Node *initNode(int level) {
    Node *node = (Node *)malloc(sizeof(Node));
    node -> level = level;
    node -> keyNum = 0;
    node -> childNum = 0;
    node -> parent = NULL;
    node -> keys = (int *)malloc(sizeof(int) * (level + 1));
    node -> children = (Node **)malloc(sizeof(Node *) * level);

    for (int i = 0; i < level; ++i) {
        node -> keys[i] = 0;
        node -> children[i] = NULL;
    }
    return node;
}

// 在节点处寻找合适的插入索引
int findSuiteIndex(Node *node, int data) {
    int index;
    // 一共有 level+1 个关键字, 最左和最右的关键字是空值
    for (index = 1; index <= node -> keyNum; ++index) {
        if (data < node -> keys[index]) {
            break;
        }
    }
    return index;
}

// 找到合适的叶子节点
Node *findSuiteLeafNode(Node *T, int data)  {
    if (T -> childNum == 0) {
        return T;
    } else {
        int index = findSuiteIndex(T, data);
        return findSuiteLeafNode(T -> children[index-1], data);
    }
}

void addData(Node *node, int data, Node **T) {
    int index = findSuiteIndex(node, data);
    for (int i = node -> keyNum; i <= index; --i) {
        node -> keys[i+1] = node -> keys[i];
    }
    node -> keys[index] = data;
    node -> keyNum++;
    // 判断是否需要进行分裂
    if (node -> keyNum == node -> level) {
        int mid = node -> level / 2 + node -> level % 2;
        Node *lchild = initNode(node -> level);
        Node *rchild = initNode(node -> level);
        for (int i = 0; i < mid; ++i) {
            addData(lchild, node -> keys[i], T);
        }
        for (int i = mid + 1; i <= node -> keyNum; ++i) {
            addData(rchild, node -> keys[i], T);
        }
        for (int i = 0; i < mid; ++i) {
            lchild -> children[i] = node -> children[i];
            if () {

            }
        }
    }
}

int main() {
    return 0;
}