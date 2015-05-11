#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

//https://zhaowuluo.wordpress.com/2011/01/03/pthread-atrix-multiplication-on-unixlinux/

#define SIZE 200
#define THREADS 2


void printMatrix(int matrix[][SIZE]) {
    int i, j;
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }

    printf("\n\n");
}

void fillMatrix(int trix[SIZE][SIZE]) {
    int i, j, r;
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            r = rand() % 1000 + 1;
            trix[i][j] = r;
        }
    }
}

void* doMult(void* chunk, int matrix1[][SIZE], int matrix2[][SIZE], int result[][SIZE]) {
    int i, j, k;
    int c = (int) chunk;
    int threadStart = (c * SIZE) / THREADS;
    int threadEnd = ((c + 1) * SIZE) / THREADS;

    for (i = threadStart; i < threadEnd; i++) {
        for (j = 0; j < SIZE; j++) {
            for (k = 0; k < SIZE; k++) {
                result[i][j] = matrix1[i][k] * matrix2[i][k];
            }
        }
    }
    return 0;
}

int main(void) {
    srand(time(NULL));

    clock_t initTime = clock();

//    pthread_t* thread = (pthread_t*) malloc(THREADS * sizeof(pthread_t));
    pthread_t thread[THREADS];
    pthread_attr_t attr;


    pthread_attr_init(&attr);

    int matrix1[SIZE][SIZE], matrix2[SIZE][SIZE], result[SIZE][SIZE];
    int i, j, k;

    fillMatrix(matrix1);
    fillMatrix(matrix2);

    for (i = 1; i < THREADS; i++) {
//        if (pthread_create(&thread[i], NULL, doMult, (void *) i) != 0) {
        if (pthread_create(&thread[i], &attr, doMult, (void *) i) != 0) {
            perror("Can't create thread");
            free(thread);
            exit(-1);
        }
    }

    doMult(0, matrix1, matrix2, result);

    for (i = 1; i < THREADS; i++) {
        pthread_join(thread[i], NULL);
    }

    int product = 0;
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            for (k = 0; k < SIZE; k++) {
                product += matrix1[i][k] * matrix2[k][j];
            }
            result[i][j] = product;
            product = 0;
        }
    }



    printf("Matrix 1:\n");
    printMatrix(matrix1);
    printf("Matrix 2:\n");
    printMatrix(matrix2);
    printf("Result: \n");
    printMatrix(result);
    free(thread);

    clock_t endTime = clock();
    double elapsed = (double) (endTime - initTime) / CLOCKS_PER_SEC;
    printf("Time elapsed in seconds: %f", elapsed);

    return 0;
}