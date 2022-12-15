#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define EPS 0.000000001

enum ERRORS{
    success = 0,
    incorrect_input = -1,
    matrix_does_not_exist = -2,
    no_memory = -3,
    no_determinant = -4,
    matrices_are_not_compatible = -5
};

void print_error(int error)
{
    switch (error) {
        case incorrect_input:
            printf("Incorrect input!\n");
            break;
        case matrix_does_not_exist:
            printf("Matrix does not exist\n");
            break;
        case no_memory:
            printf("Memory allocation error!\n");
            break;
        case no_determinant:
            printf("determinant does not exist!\n");
            break;
        case matrices_are_not_compatible:
            printf("Matrices are not compatible\n");
    }
}

void freeMatrix(double **matrix, int n)
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

int generateMatrix(double ***matrix, int *n, int *m)
{
    *n = 1 + rand() % 10;
    *m = 1 + rand() % 10;

    (*matrix) = (double**)malloc(sizeof(double*) * *n);
    if (!(*matrix))
        return no_memory;

    for (int i = 0; i < *n; i++) {
        (*matrix)[i] = (double*)malloc(sizeof(double) * *m);
        if (!(*matrix)[i]) {
            freeMatrix(*matrix, i);
            return no_memory;
        }
    }

    for (int i = 0; i < *n; i++)
        for (int j = 0; j < *m; j++)
            (*matrix)[i][j] = (double)(-100 + rand() % (201));



    return success;
}

void printMatrix(double **matrix, int n, int m)
{
    if (!matrix)
        return;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++)
            printf("%d ", (int)matrix[i][j]);
        printf("\n");
    }
    printf("\n");
}

int check_zero_row_or_col(double **matrix, int size)
{
    if (!matrix)
        return matrix_does_not_exist;
    int count_row = 0;
    int count_col = 0;

    for (int i = 0; i < size; i++) {
        if (count_row == size || count_col == size)
                return 1;
        count_row = 0;
        count_col = 0;
        for (int j = 0; j < size; j++) {
            if (abs(matrix[i][j]) < EPS)
                count_row++;
            if (abs(matrix[j][i]) < EPS)
                count_col++;
        }
    }
    return 0;
}

int swap_row_or_col(double ***matrix, int current_pose, int size, int *sign)
{
    if (!*(matrix))
        return matrix_does_not_exist;

    for (int i = current_pose; i < size; i++) {
        if (!(abs((*matrix)[i][current_pose]) < EPS)) {
            for (int j = current_pose; j < size; j++) {
                double tmp = (*matrix)[i][j];
                (*matrix)[i][j] = (*matrix)[current_pose][j];
                (*matrix)[current_pose][j] = tmp;
            }
            *sign = ~(*sign) + 1;
            break;
        }
        if (!(abs((*matrix)[current_pose][i]) < EPS)) {
            for (int k = current_pose; k < size; k++) {
                double tmp = (*matrix)[k][i];
                (*matrix)[k][i] = (*matrix)[k][current_pose];
                (*matrix)[k][current_pose] = tmp;
            }
            *sign = ~(*sign) + 1;
            break;
        }
    }
    return success;
}

int determinant(double *result, double **matrix, int n, int m)
{
    if (n != m)
        return no_determinant;
    if (n == 1) {
        *result = matrix[0][0];
        return success;
    }
    if (n == 2) {
        *result = (matrix[0][0] * matrix[1][1]) - (matrix[0][1] * matrix[1][0]);
        return success;
    }
    if (n > 2) {
        int error = 0;
        int size = n;

        double **tmp_matrix = (double**)malloc(sizeof(double*) * n);
        if (!(tmp_matrix))
            return no_memory;

        for (int i = 0; i < n; i++) {
            (tmp_matrix)[i] = (double*)malloc(sizeof(double) * m);
            if (!(tmp_matrix)[i]) {
                freeMatrix(tmp_matrix, i);
                return no_memory;
            }
        }

        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++)
                tmp_matrix[i][j] = matrix[i][j]; 

        if (check_zero_row_or_col(tmp_matrix, n) == 1) {
            *result = 0.0;
            return success;
        }
        else if (check_zero_row_or_col(tmp_matrix, n) == matrix_does_not_exist)
            return matrix_does_not_exist;

        int sign = 1;

        for (int i = 0; i < size - 1; i++) {
            for (int j = i + 1; j < size; j++) {
                if (abs(tmp_matrix[i][i]) < EPS) {
                    if ((error = swap_row_or_col(&tmp_matrix, i, size, &sign)) == success) {
                        printMatrix(tmp_matrix, size, size);
                        if (abs(tmp_matrix[i][i]) < EPS) {
                            *result = 0;
                            freeMatrix(tmp_matrix, size);
                            return success;
                        }
                    }
                    else {
                        freeMatrix(tmp_matrix, size);
                        return error;
                    }
                }

                double multiplier = tmp_matrix[j][i] / tmp_matrix[i][i];

                for (int k = size - 1; k >= i; k--)
                    tmp_matrix[j][k] -= tmp_matrix[i][k] * multiplier;
            }
        }
        for (int i = 0; i < size; i++)
            *result *= tmp_matrix[i][i];
        *result *= sign;
        freeMatrix(tmp_matrix, n);
        
    }
    return success;
}

int multiplicationMatrix(double ***C, double **A, int n1, int m1, double **B, int n2, int m2)
{
    if (m1 != n2)
    {
        return matrices_are_not_compatible;
    }

    int error = 0;

    (*C) = (double**)malloc(sizeof(double*) * n1);
    if (!(*C))
        return no_memory;

    for (int i = 0; i < n1; i++) {
        (*C)[i] = (double*)malloc(sizeof(double) * m2);
        if (!(*C)[i]) {
            freeMatrix(*C, i);
            return no_memory;
        }
    }

    for (int i = 0; i < n1; i++) {
        for (int j = 0; j < m2; j++) {
            (*C)[i][j] = 0;
            for (int k = 0; k < m1; k++) {
                (*C)[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return success;
}

int main(int argc, char *argv[])
{
    srand((unsigned)time(NULL));

    int error = 0;

    int n1 = 0, m1 = 0, n2 = 0, m2 = 0;

    double **A = NULL, **B = NULL, **C = NULL;

    if ((error = generateMatrix(&A, &n1, &m1)) == success) {
        if ((error = generateMatrix(&B, &n2, &m2)) == success) {
            printf("Matrix A\n");
            printMatrix(A, n1, m1);
            printf("Matrix B\n");
            printMatrix(B, n2, m2);
            if ((error = multiplicationMatrix(&C, A, n1, m1, B, n2, m2)) == success) {
                printf("Product of matrices A and B\n");
                printMatrix(C, n1, m2);
            }
            else
                print_error(error);
            double result = 1.0;
            if ((error = determinant(&result, A, n1, m1)) == success) {
                printf("Determinant of matrix A = %d\n", (int)result);
            }
            else {
                printf("At matrix A ");
                print_error(error);
            }
            result = 1.0;
            if ((error = determinant(&result, B, n2, m2)) == success) {
                printf("Determinant of matrix B = %d\n", (int)result);
            }
            else {
                printf("At matrix B ");
                print_error(error);
            }
            result = 1.0;
            if (C) { 
                if ((error = determinant(&result, C, n1, m2)) == success) {
                    printf("Determinant of matrix C = %d\n", (int)result);
                }
                else {
                    printf("At matrix C ");
                    print_error(error);
                }
            }
        }
        else
            print_error(error);
    }
    else
        print_error(error);

    freeMatrix(A, n1);
    freeMatrix(B, n2);
    freeMatrix(C, n1);

    return 0;
}