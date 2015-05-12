#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <sys/time.h>


#define SIZE 2000
#define THREADS 16
//int THREADS;

/**
 * Threaded Matrix Multiplication - TCSS 422 Project 2
 * @author Josh Rueschenberg
 * @author Brandon Bell
 */

int matrix1[SIZE][SIZE], matrix2[SIZE][SIZE], result[SIZE][SIZE];

//Specifically formatted print method for checking matrix multiplication through wolfram alpha
void printMatrix(int matrix[][SIZE]) {
    int i, j;
    printf("{");
    for (i = 0; i < SIZE; i++) {
        printf("{");
        for (j = 0; j < SIZE; j++) {
            printf("%d", matrix[i][j]);
            if (j != SIZE - 1) {
                printf(",");
            }
        }
        printf("},");
        printf("\n");
    }
    printf("}");

    printf("\n\n");
}

//fills the passed matrix with random numbers between 1 and 1000
void fillMatrix(int trix[SIZE][SIZE]) {
    int i, j, r;
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            r = rand() % 1000 + 1;
            trix[i][j] = r;
        }
    }
}

//multiplies two matricies and stores their result in a third matrix
void* doMult(void* chunk) {
    int i, j, k;
    int c = (int)(long) chunk;
    int threadStart = (c * SIZE) / THREADS;
    int threadEnd = ((c + 1) * SIZE) / THREADS;

    printf("Computing chunk %d (from row %d to %d)\n", c, threadStart, threadEnd-1);
    for (i = threadStart; i < threadEnd; i++) {
        for (j = 0; j < SIZE; j++) {
            result[i][j] = 0;
            for (k = 0; k < SIZE; k++) {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }
    return 0;
}

int main(int argc, char* argv[]) {
    srand(time(NULL));
    struct timeval t1, t2;
    pthread_t* thread;
    int i;

//    THREADS = atoi(argv[1]);

    printf("Number of threads: %d\n", THREADS);

    fillMatrix(matrix1);
    fillMatrix(matrix2);

    gettimeofday(&t1, NULL);
    thread = (pthread_t*) malloc(THREADS*sizeof(pthread_t));
    for (i = 1; i < THREADS; i++) {
        pthread_create(&thread[i], NULL, doMult, (void *)(long) i);
    }

    doMult(0);

    for (i = 1; i < THREADS; i++) {
        pthread_join(thread[i], NULL);
    }

//    puts("Matrix 1");
//    printMatrix(matrix1);
//    puts("Matrix 2");
//    printMatrix(matrix2);
//    puts("Result");
//    printMatrix(result);

    gettimeofday(&t2, NULL);
    unsigned long long elapsed = 1000 * (t2.tv_sec - t1.tv_sec) + (t2.tv_usec - t1.tv_usec) / 1000;
    printf("Time elapsed in seconds: %llu", elapsed / 1000);

    return 0;
}