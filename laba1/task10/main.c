#include <stdio.h>
#include <stdlib.h>
#include <time.h>

enum ERRORS{
    success = 0,
    incorrect_arguments = -1,
    invalid_message = -2,
    no_memory = -3,
    file_isnt_open = -4,
    runtime_error = -5
};

void print_error(int error)
{
    switch (error) {
        case incorrect_arguments:
            printf("Incorrect_argumets!\n");
            break;
        case invalid_message:
            printf("Invalid_message, attempts are over!\n");
            break;
        case no_memory:
            printf("Memory allocation error!\n");
            break;
        case file_isnt_open:
            printf("File is not open!\n");
            break;
        case runtime_error:
            printf("Runtime error!\n");
            break;
    }
}

void freeMatrix(double **matrix, int n, int m)
{
    if (matrix) {
        for (int i = 0; i < n; i++) {
            if (matrix[i]) {
                free(matrix[i]);
                matrix[i] = NULL;
            }
        }
        free(matrix);
        matrix = NULL;
    }
}

void printMatrix(double **matrix, int n, int m)
{
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++)
            printf("%.2f ", matrix[i][j]);
        printf("\n");
    }
}

int generateMatrix(double ***matrix, int n, int m)
{
    (*matrix) = (double**)malloc(sizeof(double*) * n);
    if (!(*matrix))
        return no_memory;

    for (int i = 0; i < n; i++) {
        (*matrix)[i] = (double*)malloc(sizeof(double) * m);
        if (!(*matrix)[i]) {
            freeMatrix(*matrix, n, m);
            return no_memory;
        }
    }

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            (*matrix)[i][j] = (double)(-100 + rand() % (201));
}

int main(int argc, char *argv[])
{
    srand((unsigned)time(NULL));
    double **matrix = NULL;
    generateMatrix(&matrix, 3, 3);
    printMatrix(matrix, 3, 3);
    freeMatrix(matrix, 3, 3);

    return 0;
}