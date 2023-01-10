//
// Created by KexinCC on 2023/1/10.
//

#include<stdio.h>
#include<stdlib.h>

typedef struct String {
    char *data;
    int len;
} String;

String *initString() {
    String *s = (String *) malloc(sizeof(String));
    s->data = NULL;
    s->len = 0;
    return s;
}

void stringAssign(String *s, char *data) {
    if (s->data) {
        free(s);
    }
    int len = 0;
    char *temp = data;
    while (*temp) {
        len++;
        temp++;
    }
    if (len == 0) {
        s->data = NULL;
        s->len = 0;
    } else {
        temp = data;
        s->len = len;
        s->data = (char *) malloc(sizeof(char) * (len + 1));
        for (int i = 0; i < len; ++i, ++temp) {
            s->data[i] = *temp;
        }
    }
}

void printString(String *s) {
    for (int i = 0; i < s->len; ++i) {
        printf(i == 0 ? "%c " : "-> %c ", s->data[i]);
    }
    printf("\n");
}

int *getNext(String *s) {
    int *next = (int *) malloc(sizeof(int) * s->len);
    int j = -1;
    next[0] = -1;
    for (int i = 1; i < s->len; ++i) {
        while (j >= 0 && s->data[i] != s->data[j + 1]) {
            j = next[j];
        }
        if (s->data[i] == s->data[j + 1]) {
            j++;
        }
        next[i] = j;
    }
    return next;
}

int strStr(String *master, String *sub, int *next) {
    if (sub->len == 0) {
        return 0;
    }
    int j = -1;
    for (int i = 0; i < master->len; ++i) {
        while (j >= 0 && master->data[i] != sub->data[j + 1]) {
            j = next[j];
        }
        if (master->data[i] == sub->data[j + 1]){
            j++;
        }
        if (j == sub->len - 1) {
            return i - sub->len + 1;
        }
    }
    return -1;
}


void printNext(int *next, int len) {
    for (int i = 0; i < len; ++i) {
        printf(i == 0 ? "%d " : "-> %d ", next[i]);
    }
    printf("\n");
}


int main(int argc, char *argv[]) {
    String *s = initString();
    String *s1 = initString();
    stringAssign(s, argv[1]);
    stringAssign(s1, argv[2]);
    int *next = getNext(s1);
    printNext(next, s1->len);
    int index = strStr(s, s1, next);
    printf("%d \n", index);
    return 0;
}