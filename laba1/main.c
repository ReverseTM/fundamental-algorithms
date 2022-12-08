#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int power(int digit, int n)
{
    if (n == 0)
        return 1;
    int product = digit;
    for (int i = 1; i < n; i++)
    {
        product *= digit;
    }
    return product;
}

int matrix_determinant(int **matrix, int n, int m)
{
    if (n != m)
    {
        printf("Determinant does not exist\n");
        return 0;
    }

    if (n == 1)
        return matrix[0][0];
    if (n == 2)
        return (matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0]);
    if (n >= 3)
    {
        int **tmp = (int **)malloc(sizeof(int *) * (n - 1));
        for (int i = 0; i < n - 1; i++)
        {
            tmp[i] = (int *)malloc(sizeof(int) * (n - 1));
        }
        int determinant = 0;
        int a, b;

        for (int i = 0; i < n; i++)
        {
            a = 0;
            for (int j = 1; j < n; j++)
            {
                b = 0;
                for (int k = 0; k < n; k++)
                    if (k != i)
                    {
                        tmp[a][b] = matrix[j][k];
                        b++;
                    }
                a++;
            }
            determinant += power(-1, i + 2) * matrix[0][i] * matrix_determinant(tmp, n - 1, m - 1);
            for (int i = 0; i < n - 1; i++)
            {
                free(tmp[i]);
            }
            free(tmp);
        }
        return determinant;
    }
}

int **matrix_multiplication(int **C, int **A, int n1, int m1, int **B, int n2, int m2)
{
    if (m1 != n2)
    {
        printf("Matrices are incompatible\n");
        return 0;
    }
    C = (int **)malloc(sizeof(int *) * n1);

    for (int i = 0; i < n1; i++)
    {
        C[i] = (int *)malloc(sizeof(int) * m2);
    }
    for (int i = 0; i < n1; i++)
    {
        for (int j = 0; j < m2; j++)
        {
            C[i][j] = 0;

            for (int k = 0; k < m1; k++)
            {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return C;
}

int **matrix_generation(int **matrix, int n, int m)
{
    int data = 0;

    matrix = (int **)malloc(sizeof(int *) * n);

    for (int i = 0; i < n; i++)
    {
        matrix[i] = (int *)malloc(sizeof(int) * m);
    }

    printf("Enter matrix values\n");

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            scanf("%d", &data);
            if (data < -100 || data > 100)
            {
                printf("Enter a value in the range [-100,100]\n");
                j--;
            }
            else
            {
                matrix[i][j] = data;
            }
            // matrix[i][j] = -100 + rand() % 101;
        }
    }
    return matrix;
}

int main(int argc, char *argv[])
{
    int **A = NULL, **B = NULL, **C = NULL;
    int n = 0, m = 0;

    while (n < 1 || n > 10 || m < 1 || m > 10)
    {
        printf("Enter the size of the matrix in the range [1,10]:\n");
        scanf("%d %d", &n, &m);
        if (n < 1 || n > 10 || m < 1 || m > 10)
        {
            printf("Incorrect matrix size entered\n\n");
        }
    }

    A = matrix_generation(A, n, m);
    B = matrix_generation(B, n, m);
    C = matrix_multiplication(C, A, n, m, B, n, m);

    printf("A * B\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }

    printf("%Determinant A = %d\n", matrix_determinant(A, n, m));
    printf("%Determinant B = %d\n", matrix_determinant(B, n, m));

    if (A)
    {
        for (int i = 0; i < n; i++)
        {
            free(A[i]);
        }
        free(A);
    }

    if (B)
    {
        for (int i = 0; i < n; i++)
        {
            free(B[i]);
        }
        free(B);
    }

    if (C)
    {
        for (int i = 0; i < n; i++)
        {
            free(C[i]);
        }
        free(C);
    }

    return 0;
}
