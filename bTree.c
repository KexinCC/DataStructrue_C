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
    //往节点中插入数据
    int index = findSuiteIndex(node, data);
    for (int i = node -> keyNum; i >= index; --i) {
        node -> keys[i+1] = node -> keys[i];
    }
    node -> keys[index] = data;
    node -> keyNum++;
    // 判断是否需要进行分裂
    if (node -> keyNum == node -> level) {
        //开始分裂找到中间位置
        int mid = node -> level / 2 + node -> level % 2;
        //初始化左孩子节点
        Node *lchild = initNode(node -> level);
        //初始化右孩子节点
        Node *rchild = initNode(node -> level);
        //将mid左边的值赋值给左孩子
        for (int i = 1; i < mid; ++i) {
            addData(lchild, node -> keys[i], T);
        }
        //将mid右边的值赋值给右孩子
        for (int i = mid + 1; i <= node -> keyNum; ++i) {
            addData(rchild, node -> keys[i], T);
        }
        //将原先节点mid左边的孩子赋值给分裂出来的左孩子
        //(刚分裂出来的孩子指向分裂前节点孩子的孩子)
        for (int i = 0; i < mid; ++i) {
            lchild -> children[i] = node -> children[i];
            if (node -> children[i] != NULL) {
                node -> children[i] -> parent = lchild;
                lchild -> childNum++;
            }
        }
        int index = 0;
        for (int i = mid; i < node -> childNum; ++i) {
            rchild -> children[index++] = node -> children[i];
            if (node -> children[i] != NULL) {
                node -> children[i] -> children = rchild;
                rchild -> childNum++;
            }
        }
        //判断当前节点是否是根节点
        if (node -> parent == NULL) {
            //是根节点
            Node *newParent = initNode(node -> level);
            //给新的根节点传入数据, 就是分裂前节点的 mid 上的值
            addData(newParent, node -> keys[mid], T);
            newParent -> children[0] = lchild;
            newParent -> children[1] = rchild;
            newParent -> childNum = 2;
            lchild -> parent = newParent;
            rchild -> parent = newParent;
            *T = newParent;
        } else {
            //不是根节点
            //在父亲节点找一个合适的位置插入 , index: 在父亲节点中合适的位置
            int index = findSuiteIndex(node -> parent, node -> keys[mid]);
            lchild -> parent = node -> parent;
            rchild -> parent = node -> parent;
            node -> parent -> children[index - 1] = lchild;
            if (node -> parent -> children[index] != NULL) {
                for (int i = node -> parent -> childNum - 1; i >= index; --i) {
                    node -> parent -> children[i+1] = node -> parent -> children[i];
                }
            }
            node -> parent -> children[index] = rchild;
            node -> parent -> childNum++;
            addData(node -> parent, node -> keys[mid], T);
        }
    }
}

/**
 *
 * @param node 传入的根节点
 * @param data 想要寻找的数据
 * @return 找到的 包含 data 的 node 或 NULL
 */
Node *find(Node *node, int data) {
    if (node == NULL) {
        return NULL;
    }
    for (int i = 1; i <= node -> keyNum; ++i) {
        if (data == node -> keys[i]) {
            return node;
        } else if (data < node -> keys[i]) {
            return find(node -> children[i-1], data);
        } else {
            if (i != node -> keyNum && data < node -> keys[i+1]) {
                return find(node -> children[i], data);
            }
        }
        // node -> children[node -> keyNum] == NULL
        return find(node -> children[node -> keyNum], data);
    }
}

void insert(Node **T, int data) {
    Node *node = findSuiteLeafNode(*T, data);
    addData(node, data, T);
}

void printTree(Node *T) {
    if (T != NULL) {
        // 遍历打印关键字
        for (int i = 1; i <= T -> keyNum; ++i) {
            printf("%d ", T -> keys[i]);
        }
        printf("\n");
        for (int i = 0; i < T -> childNum; ++i) {
            printTree(T -> children[i]);
        }
    }
}

int main() {
    Node* T = initNode(5);
    insert(&T, 1);
    insert(&T, 2);
    insert(&T, 6);
    insert(&T, 7);
    insert(&T, 11);
    insert(&T, 4);
    insert(&T, 8);
    insert(&T, 13);
    insert(&T, 10);
    insert(&T, 5);
    insert(&T, 17);
    insert(&T, 9);
    insert(&T, 16);
    insert(&T, 20);
    insert(&T, 3);
    insert(&T, 12);
    insert(&T, 14);
    insert(&T, 18);
    insert(&T, 19);
    insert(&T, 15);
    printTree(T);
    Node* node = find(T, 7);
    if (node) {
        for (int i = 1; i <= node -> keyNum; i++) {
            printf("%d ", node -> keys[i]);
        }
        printf("\n");
    }
    return 0;
}