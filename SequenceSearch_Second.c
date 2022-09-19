//
// Created by KexinCC on 2022/9/18.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct List {
    int num;
    int *data;
    int length;
}List;

List *initList(int length) {
    List *list = (List *)malloc(sizeof(List));
    list -> num = 1;
    list -> length = length;
    list -> data = (int *)malloc(sizeof(int) * length);
    return list;
}



void listAdd(List *list, int data) {
    list -> data[list -> num++] = data;
}

int search(List *list, int key) {
    int i;
    list -> data[0] = key;
    for (i = list -> num - 1; list -> data[i] != key; --i) {
        printf("i = %d ", i);
    }
    printf("\n");
    return i;
}

void printList(List* list) {
    for (int i = 0; i < list -> num; i++) {
        printf("%d -> ", list -> data[i]);
    }
    printf("NULL\n");
}


int main() {
    List* list = initList(5);
    listAdd(list, 4);
    listAdd(list, 5);
    listAdd(list, 6);
    listAdd(list, 7);
    printList(list);
    printf("%d\n", search(list, 4));
    return 0;
}