#include <stdio.h>
#include <limits.h>
#include <time.h>
#include <stdlib.h>
#include "../include/search_min.h"

void generate_array(int *arr, long long size){
	srand(time(NULL));
	for (long long i = 0; i < size; ++i){
		arr[i] = (rand() % 20001) - 10000;
	}
}

int main(int argc, char *argv[]){
	if (argc != 2) {
		printf("wrond data from console!");
		return 1;
	}

	long long size = atoll(argv[1]);

	if (size <= 0 || size > LLONG_MAX / sizeof(int)) {
        printf("wrong size. set max.\n");
        size = LLONG_MAX / sizeof(int);
    	}

	int *arr = malloc(size * sizeof(int));
	if (!arr){
		printf("err. cannot allocate memory\n");
		return 3;
	}

	generate_array(arr, size);
	int min_value = find_it(arr, size);

	printf("[IT] array size: %lld | min: %d\n", size, min_value);

	free(arr);
	return 0;
}
