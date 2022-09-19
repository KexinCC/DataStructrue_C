//
// Created by KexinCC on 2022/9/18.
//

#include <stdlib.h>
#include <stdio.h>

typedef struct List {
    int num;
    int *data;
    int length;
}List;

List *initList(int length) {
    List *list = (List *)malloc(sizeof(List));
    list -> data = (int *)malloc(sizeof(int) * length);
    list -> length = length;
    list -> num = 0;
    return list;
}

void listAdd(List *list, int data) {
    list -> data[list -> num++] = data;
}

void printList(List *list) {
    for (int i = 0; i < list -> num; ++i) {
        printf("%d -> ", list -> data[i]);
    }
    printf("NULL\n");
}

int search(List *list, int key) {
    for (int i = 0; i < list -> num; ++i) {
        if (list -> data[i] == key)
            return i;
    }
    return -1;
}

int main() {
    List* list = initList(5);
    listAdd(list, 1);
    listAdd(list, 2);
    listAdd(list, 3);
    listAdd(list, 4);
    printList(list);
    printf("%d\n", search(list, 4));
    return 0;
}