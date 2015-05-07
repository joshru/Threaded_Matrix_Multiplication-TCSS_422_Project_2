#include <stdio.h>

const int SIZE = 20;

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

int main(void) {

    int matrix1[SIZE][SIZE], identity[SIZE][SIZE], result[SIZE][SIZE];
    int i, j, k, fill = 1;

    for (i = 0; i < SIZE; i++) {

        for (j = 0; j < SIZE; j++) {
            matrix1[i][j] = fill++;
        }
    }

    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            if (i == j) {
                identity[i][j] = 1;
            } else {
                identity[i][j] = 0;
            }
        }
    }

    int product = 0;
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            for (k = 0; k < SIZE; k++) {
                product += matrix1[i][k] * identity[k][j];
            }
            result[i][j] = product;
            product = 0;
        }
    }


    printf("Matrix 1:\n");
    printMatrix(matrix1);
    printf("Matrix 2:\n");
    printMatrix(identity);
    printf("Result: \n");
    printMatrix(result);

    return 0;
}