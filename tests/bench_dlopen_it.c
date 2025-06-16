#include <stdio.h>
#include <limits.h>
#include <time.h>
#include <stdlib.h>
#include <dlfcn.h>

void generate_array(int *arr, long long size){
    srand(time(NULL));
    for (long long i = 0; i < size; ++i){
        arr[i] = (rand() % 20001) - 10000;
    }
}

int main(int argc, char *argv[]){
    if (argc != 2) return 1;

    long long n = atoll(argv[1]);

    if (n <= 0 || n > LLONG_MAX / sizeof(int)) {
        printf("wrong size. set max.\n");
        n = LLONG_MAX / sizeof(int);
    }

    int *arr = malloc(n * sizeof(int));
    if (!arr){
        printf("err. cannot allocate memory\n");
        return 3;
    }

    generate_array(arr, n);

    void *handle = dlopen(
	"/home/ivanchetvergov/prac/libs/libsearch_min_shared.so", RTLD_LAZY
    );

    if (!handle) {
        printf("err loading lib: %s\n", dlerror());
        free(arr);
        return 1;
    }

    int (*search_min)(int *, int) = dlsym(handle, "find_it");
    if (!search_min) {
        printf("er loading func: %s\n", dlerror());
        dlclose(handle);
        free(arr);
        return 1;
    }

    int min_value = search_min(arr, n);

    printf("[DL_IT] array size: %lld | min: %d\n", n, min_value);

    dlclose(handle);
    free(arr);

    return 0;
}

