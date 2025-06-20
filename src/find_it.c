#include <stdio.h>
#include <stdlib.h>

int find_it(int *array, unsigned long long size) {
    if (array == NULL || size <= 0) {
        fprintf(stderr, "error: wrong data.\n");
        exit(EXIT_FAILURE);
    }
    int min = array[0];
    for (int i = 1; i < size; i++) {
        if (array[i] < min) {
            min = array[i];
        }
    }
    return min;
}
