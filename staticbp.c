#include "stdio.h"
#include "stdlib.h"
#include "time.h"

#define likely(x)  __builtin_expect((x), 1)
#define unlikely(x) __builtin_expect((x), 0)

void likelyInsertionSort(int *vec, int vecsize) {
    for (int i = 0; i < vecsize; i++) {
        int min, minidx, swap;
        min = vec[i];
        minidx = i;
        for (int j = i + 1; j < vecsize; j++) {
            if (likely(vec[j] < min)) {
                min = vec[j];
                minidx = j;
            }
        }
        swap = vec[minidx];
        vec[minidx] = vec[i];
        vec[i] = swap;
    }
}

void unlikelyInsertionSort(int *vec, int vecsize) {
    for (int i = 0; i < vecsize; i++) {
        int min, minidx, swap;
        min = vec[i];
        minidx = i;
        for (int j = i + 1; j < vecsize; j++) {
            if (unlikely(vec[j] < min)) {
                min = vec[j];
                minidx = j;
            }
        }
        swap = vec[minidx];
        vec[minidx] = vec[i];
        vec[i] = swap; 
    }
}

int *vecAoContrario(int vecsize) {
    int *vec;  
    vec = malloc(vecsize * sizeof(int));
    for (int i = 0; i < vecsize; i++)
        vec[i] = vecsize - i;
    return vec;
}

double getTime() {
    double result = 0;
    struct timespec time;
    clock_gettime(CLOCK_REALTIME, &time);
    result += (double) time.tv_sec;
    result += (double) time.tv_nsec / 1000000000;
    return result;
}


int main(int argc, char* argv[]) {
    int *vec;
    int vecsize;
    double timbef, timaft;
    
    printf("Experimento em Static Branch Prediction\n");
    printf("InsertionSort em vetor inverso passando flags de compilador\n");

    if (argc < 2) {
        printf("Uso: %s [tamanho vetor]\n", argv[0]);
        return -1;
    }

    vecsize = atoi(argv[1]);

    printf("Vetor invertido - likely\n");
    vec = vecAoContrario(vecsize);
    timbef = getTime();
    likelyInsertionSort(vec, vecsize);
    timaft = getTime();
    printf("%lfs para ordenar\n", timaft - timbef);
    free(vec);
    printf("\n");

    printf("Vetor invertido - unlikely\n");
    vec = vecAoContrario(vecsize);
    timbef = getTime();
    unlikelyInsertionSort(vec, vecsize);
    timaft = getTime();
    printf("%lfs para ordenar\n", timaft - timbef);
    free(vec);
    printf("\n");
    return 0;
}
