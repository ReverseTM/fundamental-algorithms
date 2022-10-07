#include <stdio.h>
#include <stdlib.h>

int* matrix_filling(int* matrix, int size)
{
    for (int i = 0; i < size; i++)
    {
        matrix[i] = rand() % 10000;
    }
    return matrix;
}

void output_matrix(int* matrix, int size)
{   
    for (int i = 0; i < size; i++)
    {
        printf("%d ", matrix[i]);
    }
    printf("\n");
}

int main(int argc, char* argv[])
{
    int size_A = 0, size_B = 0;

    printf("Enter size matrix A: \n");
    scanf("%d", &size_A);
    printf("Enter size matrix B: \n");
    scanf("%d", &size_B);

    if (size_A <= 0 || size_B < 0)
    {
        printf("Incorrect input!\n");
        return 0;
    }

    int* A = (int*)malloc(sizeof(int) * size_A);
    int* B = (int*)malloc(sizeof(int) * size_B);
    int* C = (int*)malloc(sizeof(int) * size_A);


    matrix_filling(A, size_A);
    matrix_filling(B, size_B);

    if (size_B == 0)
    {
        output_matrix(A, size_A);
    }
    else
    {
        for (int i = 0; i < size_A; i++)
        {
            if (i >= size_B)
            {
                C[i] = A[i] + B[size_B - 1];
            }
            else
            {
                C[i] = A[i] + B[i];
            }
        }
        output_matrix(A, size_A);
        output_matrix(B, size_B);
        output_matrix(C, size_A);
    }
    return 0;
}
