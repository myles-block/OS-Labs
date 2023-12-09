#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define MAX 3 // Change this value to your desired matrix size

int matA[MAX][MAX];
int matB[MAX][MAX];

int matSumResult[MAX][MAX];
int matDiffResult[MAX][MAX];
int matProductResult[MAX][MAX];

// Structure to pass thread arguments
typedef struct {
    int row;
    int col;
} ThreadArgs;

void fillMatrix(int matrix[MAX][MAX]) {
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            matrix[i][j] = rand() % 10 + 1;
        }
    }
}

void printMatrix(int matrix[MAX][MAX]) {
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            printf("%5d", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void* computeSum(void* args) {
    ThreadArgs* threadArgs = (ThreadArgs*)args;
    int row = threadArgs->row;
    int col = threadArgs->col;
    matSumResult[row][col] = matA[row][col] + matB[row][col];
    free(threadArgs);
    pthread_exit(NULL);
}

void* computeDiff(void* args) {
    ThreadArgs* threadArgs = (ThreadArgs*)args;
    int row = threadArgs->row;
    int col = threadArgs->col;
    matDiffResult[row][col] = matA[row][col] - matB[row][col];
    free(threadArgs);
    pthread_exit(NULL);
}

void* computeProduct(void* args) {
    ThreadArgs* threadArgs = (ThreadArgs*)args;
    int row = threadArgs->row;
    int col = threadArgs->col;

    matProductResult[row][col] = 0;
    for (int k = 0; k < MAX; k++) {
        matProductResult[row][col] += matA[row][k] * matB[k][col];
    }

    free(threadArgs);
    pthread_exit(NULL);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: %s <matrix_size>\n", argv[0]);
        return 1;
    }

    int size = atoi(argv[1]);
    if (size <= 0 || size > MAX) {
        printf("Invalid matrix size. Please choose a size between 1 and %d.\n", MAX);
        return 1;
    }

    srand(time(0));

    // 0. Get the matrix size from the command line and assign it to MAX

    // 1. Fill the matrices (matA and matB) with random values.
    fillMatrix(matA);
    fillMatrix(matB);

    // 2. Print the initial matrices.
    printf("Matrix A:\n");
    printMatrix(matA);
    printf("Matrix B:\n");
    printMatrix(matB);

    // 3. Create pthread_t objects for our threads.
    pthread_t threads[MAX][MAX];

    // 4. Create a thread for each cell of each matrix operation.
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            ThreadArgs* args = (ThreadArgs*)malloc(sizeof(ThreadArgs));
            args->row = i;
            args->col = j;
            pthread_create(&threads[i][j], NULL, computeSum, (void*)args);
            // For subtraction and multiplication, create additional threads here
        }
    }

    // 5. Wait for all threads to finish.
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            pthread_join(threads[i][j], NULL);
        }
    }

    // 6. Print the results.
    printf("Results:\n");
    printf("Sum:\n");
    printMatrix(matSumResult);
    printf("Difference:\n");
    printMatrix(matDiffResult);
    printf("Product:\n");
    printMatrix(matProductResult);

    return 0;
}
