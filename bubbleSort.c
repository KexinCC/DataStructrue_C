//
// Created by kexin on 9/22/22.
//

#include <stdio.h>

void printArray(int array[], int length) {
    for (int i = 0; i < length; ++i) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

void bubbleSort(int array[], int length) {
    int temp;
    for (int i = 0; i < length - 1; ++i) {
        for (int j = 0; j < length - i - 1; ++j) {
            if (array[j] > array[j+1]) {
                temp = array[j];
                array[j] = array[j+1];
                array[j+1] = temp;
            }
        }
    }
    printArray(array, length);
}

int main() {
    int array[8] = {49, 38, 65, 97, 76, 13, 27, 49};
    bubbleSort(array, 8);
    return 0;
}