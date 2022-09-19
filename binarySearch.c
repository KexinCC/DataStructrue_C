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
    list -> length = length;
    list -> data = (int *)malloc(sizeof(int) * length);
    list -> num = 0;
    return list;
}

void listAdd(int data, List *list) {
    list -> data[list -> num++] = data;
}

void printList(List *list) {
    for (int i = 0; i < list -> num; ++i) {
        printf("%d -> ", list -> data[i]);
    }
    printf("NULL\n");
}

int binarySearch(List *list, int key) {
    int start = 0;
    int end = list -> num - 1;
    int mid;
    while (start <= end) {
        mid = (start + end) / 2;
        if (list -> data[mid] < key)
            start = mid + 1;
        else if (list -> data[mid] > key)
            end = mid - 1;
        else
            return mid;
    }
    return -1;
}

int binarySearchRecursion(int key, List *list, int start, int end) {
    if (start == end) {
        if (list -> data[start] == key) {
            return start;
        } else {
            return -1;
        }
    }
    int mid = (start + end) / 2;
    if (list -> data[mid] < key) {
        return binarySearchRecursion(key, list, mid+1, end);
    } else if (list -> data[mid] > key) {
        return binarySearchRecursion(key, list, start, mid-1);
    } else {
        return mid;
    }
}

int main() {
    List* list = initList(9);
    listAdd(1, list);
    listAdd(2, list);
    listAdd(3, list);
    listAdd(4, list);
    listAdd(5, list);
    listAdd(6, list);
    listAdd(7, list);
    listAdd(8, list);
    listAdd(9, list);
    printList(list);
    printf("data %d in %d\n",90 , binarySearch(list, 90));
    printf("data %d in %d\n",1 , binarySearch(list, 1));
    printf("data %d in %d\n",4 , binarySearch(list, 4));
    printf("data %d in %d\n",6 , binarySearch(list, 6));
    printf("data %d in %d\n",0 , binarySearch(list, 0));
    printf("data %d in %d\n",2 , binarySearchRecursion(2, list, 0, list -> num - 1));
}