#include <stdio.h>
#include <stdlib.h>

int find_rec(int *array, unsigned long long size) {
    if (array == NULL || size <= 0) {
        fprintf(stderr, "error: wrong data.\n");
        exit(EXIT_FAILURE);
    }
    if (size == 1) {
        return array[0];
    }
    int min_of_rest = find_rec(array + 1, size - 1);
    return (array[0] < min_of_rest) ? array[0] : min_of_rest;
}
