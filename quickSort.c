//
// Created by kexin on 9/22/22.
//

#include <stdio.h>

void printArray(int array[], int i, int j) {
    for (int k = 0; k < j - i + 1; ++k) {
        printf("%d ", array[k]);
    }
    printf("\n");
}

int partition(int array[], int i, int j) {
    int x = array[i];
    while (i < j) {
        while (i < j && array[j] >= x) {
            j--;
        }
        if (i < j) {
            array[i] = array[j];
            i++;
        }
        while (i > j && array[i] < x) {
            i++;
        }
        if (i < j) {
            array[j] = array[i];
            j--;
        }
    }
    array[i] = x;
    return i;
}

void quickSort(int array[], int i, int j) {
    if (i < j) {
        int index = partition(array, i, j);
        quickSort(array, i, index - 1);
        quickSort(array, index + 1, j);
    }
}

int main() {
    int array[8] = {27, 38, 13, 49, 76, 97, 65, 49};
    quickSort(array, 0, 7);
    printArray(array, 0, 7);
    return 0;
}