//
// Created by kevin on 2022/8/4.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int data;
    struct TreeNode *lchild;
    struct TreeNode *rchild;
} TreeNode;

TreeNode *binarySearch(TreeNode *T, int data) {
    if (T) {
        if (data == T->data) {
            return T;
        } else if (data < T->data) {
            return T->lchild;
        } else {
            return T->rchild;
        }
    } else {
        return NULL;
    }
}

void bstInsert(TreeNode **T, int data) {
    if (*T == NULL) {
        *T = malloc(sizeof(TreeNode));
        (*T)->data = data;
        (*T)->lchild = NULL;
        (*T)->rchild = NULL;
    } else if (data < (*T)->data) {
        return bstInsert(&((*T)->lchild), data);
    } else {
        return bstInsert(&((*T)->rchild), data);
    }
}

void preOrder(TreeNode *T) {
    if (T) {
        printf("%d ", T -> data);
        preOrder(T -> lchild);
        preOrder(T -> rchild);
    }
}

int main() {
    TreeNode* T = NULL;
    int nums[6] = {8, 6, 10, 9, 11, 23};
    for (int i = 0; i < 6; i++) {
        bstInsert(&T, nums[i]);
    }
    preOrder(T);
    printf("\n");
    printf("%p",binarySearch(T,8));
}

