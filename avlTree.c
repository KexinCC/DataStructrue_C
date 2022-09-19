//
// Created by kevin on 2022/8/4.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int data;
    int height;
    struct TreeNode *lchild;
    struct TreeNode *rchild;
} TreeNode;

int getHeight(TreeNode *node) { return node ? node -> height : 0; }

int max(int a, int b) { return a > b ? a : b; }

/*
 *  RR:失衡树节点node在根节点root的右侧
 *  node在root孩子的右侧
 *  取中间节点，使它的父亲成为它的左孩子
 *  如果它有左孩子的，左孩子连接到父亲的右孩子上
 */
void rrRotation(TreeNode *node, TreeNode **root) {
    TreeNode *temp = node -> rchild;
    node -> rchild = temp -> lchild;
    temp -> lchild = node;
    node -> height = max(getHeight(node -> lchild), getHeight(node -> rchild)) + 1;
    temp -> height = max(getHeight(temp -> lchild), getHeight(temp -> rchild)) + 1;
    *root = temp;
}

void llRotation(TreeNode *node, TreeNode **root) {
    TreeNode *temp = node -> lchild;
    node -> lchild = temp -> rchild;
    temp -> rchild = node;
    node -> height = max(getHeight(node -> lchild), getHeight(node -> rchild)) + 1;
    temp -> height = max(getHeight(temp -> lchild), getHeight(temp -> rchild)) + 1;
    *root = temp;
}

void avlInsert(TreeNode **T, int data) {
    if (*T == NULL) {
        *T = (TreeNode *) malloc(sizeof(TreeNode));
        (*T) -> data = data;
        (*T) -> height = 0;
        (*T) -> lchild = NULL;
        (*T) -> rchild = NULL;
    } else if (data > (*T) -> data) {
        avlInsert(&((*T) -> rchild), data);
        int lHeight = getHeight((*T) -> lchild);
        int rHeight = getHeight((*T) -> rchild);

        if (rHeight - lHeight == 2) {
            if (data > (*T) -> rchild -> data) {
                // RR调整
                rrRotation(*T, T);
            } else if (data < (*T) -> rchild -> data) {
                // RL调整
                llRotation((*T) -> rchild, &((*T) -> rchild));
                rrRotation(*T, T);
            }
        }

    } else if (data < (*T) -> data) {
        avlInsert(&((*T) -> lchild), data);
        int lHeight = getHeight((*T) -> lchild);
        int rHeight = getHeight((*T) -> rchild);
        if (lHeight - rHeight == 2) {
            if (data < (*T) -> lchild -> data) {
                // LL调整
                llRotation(*T, T);
            } else if (data > (*T) -> lchild -> data) {
                // LR调整
                rrRotation((*T) -> lchild, &((*T) -> lchild));
                llRotation(*T, T);
            }
        }
    }
    (*T) -> height = max(getHeight((*T) -> lchild),
                         getHeight((*T) -> rchild)) + 1;
}

void preOrder(TreeNode *T) {
    if (T) {
        printf("%d ", T -> data);
        preOrder(T -> lchild);
        preOrder(T -> rchild);
    }
}

int main() {
    TreeNode *T = NULL;
    int nums[5] = {1, 2, 3, 4, 5};
    for (int i = 0; i < 5; i++) {
        avlInsert(&T, nums[i]);
    }
    preOrder(T);
    printf("\n");
    return 0;
}