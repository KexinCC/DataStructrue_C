//
// Created by KexinCC on 2022/9/21.
//
#include <stdlib.h>
#include <stdio.h>
#define NUM 5

typedef struct HashList {
    int num;
    char *data;
}HashList;

HashList *initHashList() {
    HashList *list = (HashList *)malloc(sizeof(HashList));
    list -> num  = 0;
    list -> data = (char *)malloc(sizeof(char) * NUM);
    for (int i = 0; i < NUM; ++i) {
        list -> data[i] = 0;
    }
    return list;
}

int hash(int data) {
    return data % NUM;
}

void put(HashList *list, char data) {
    int index = hash(data);
    if (list -> data[index] != 0) {
        int count = 1;
        while (list -> data[index] != 0) {
            index = hash(hash(data) + count);
            count++;
        }
    }
    list -> data[index] = data;
    list -> num++;
}

int main() {
    HashList* list = initHashList();
    put(list, 'A');
    put(list, 'F');
    put(list, 'F');
    for (int i = 0; i < NUM; ++i) {
        printf("%c ",list -> data[i]);
    }
    printf("\n");
    return 0;
}