#include <stdio.h>
#include <stdlib.h>

void print_error(int error)
{
    switch (error) {
        case -1:
            printf("Incorrect input!\n");
            break;
        case -2:
            printf("The count of units must be less than the number of bits in the number!\n");
            break; 
        case -3:
            printf("Factorial is not defined!\n");
            break;
        case -4:
            printf("Memory allocation error!\n");
            break;
        case -5:
            printf("Something wrong!\n");
    }
}

void print_array(int *array, int size)
{
    if (!array)
        return;
    printf("[ ");
    for (int i = 0; i < size; i++) {
        if (i == size - 1)
            printf("%d ", array[i]);
        else 
            printf("%d, ", array[i]);
    }
    printf("]\n");
}

int factorial(int n)
{
    if (n == 0)
        return 1;
    if (n > 0) {
        int result = 1;
        for (int i = 2; i <= n; i++)
            result *= i;
        return result;
    }
    else
        return -3;
}

int combination(int n, int k)
{
    if (n < 0 || k <= 0)
        return -5;
    if (k > n)
        return -5;
    int numerator = 1;
    int denominator = factorial(n - k);
    if (denominator == -3)
        return -3;
    for (int i = k + 1; i <= n; i++)
        numerator *= i;
    
    return (numerator / denominator);
}

int count_of_units(int number , int l)
{
    int count = 0;
    for (; number; number >>= 1)
        count += number & 1;
    return count == l;
}

int count_of_consecutive_units(int number, int l)
{
    int count = 0;
    for (; number; number >>= 1) {
        count = number & 1 ? count + 1 : 0;
        if (count == l && ((number >> 1) & 1) == 0)
            return 1;
    }
    return 0;
}

void function_1(int k, int l, int **result, int *length, int *error)
{
    if (k <= 0 || l < 0 || l > k) {
        *error = -5;
        return;
    }

    if (l == k || l == 0) {
        (*result) = (int*)malloc(sizeof(int) * ++(*length));
        if (!(*result)) {
            *error = -4;
            return;
        }
        (l == k) ? ((*result)[(*length) - 1] = (1 << k) - 1) : ((*result)[(*length) - 1] = 0);
        return;
    }

    int size = combination(k, l);
    if (size < 0) {
        *error = size;
        return;
    }
    (*result) = (int*)malloc(sizeof(int) * size);
    if (!(*result)) {
        *error = -4;
        return;
    }
    int border = 1 << k;
    for (int number = 0; number < border; number++) {
        if (count_of_units(number, l)) {
            (*result)[(*length)++] = number;
        }
    }
}

void function_2(int k, int l, int **result, int *length, int *error)
{
    if (k <= 0 || l < 0 || l > k) {
        *error = -5;
        return;
    }

    int size = 1;

    *result = (int*)malloc(sizeof(int) * size);
        if (!(*result)) {
            *error = -4;
            return;
        }

    if (l == k || l == 0) {
        (l == k) ? ((*result)[(*length)++] = (1 << k) - 1) : ((*result)[(*length)++] = 0);
        return;
    }

    int *tmp = NULL;
    int border = 1 << k;

    for (int number = 0; number < border; number++) {
        if (count_of_consecutive_units(number, l)) {
            if (*length >= size) {
                size *= 2; 
                if (!(tmp = (int*)realloc(*result, sizeof(int) * size))) {
                    *error = -4;
                    free(*result);
                    *result = NULL;
                    return;
                }
                *result = tmp;
            }
            (*result)[(*length)++] = number;
        }
    }
}

int main(int argc, char *argv[])
{
    int *result_f1 = NULL;
    int *result_f2 = NULL;
    int length_f1 = 0;
    int length_f2 = 0;
    int error = 0;
    int k = 0, l = 0;

    printf("Enter k bit: ");
    if (scanf("%d", &k) == 1 && (k > 0 && k < 32)) {
        printf("Enter l: ");
        if (scanf("%d", &l) == 1 && l >= 0) {
            if (l <= k) {
                function_1(k, l, &result_f1, &length_f1, &error);
                function_2(k, l, &result_f2, &length_f2, &error);
                if (error == 0) {
                    printf("%d-bit numbers with exactly %d units in binary notation: ", k, l);
                    print_array(result_f1, length_f1);
                    printf("%d-bit numbers, in the binary notation of which there are exactly %d consecutive units: ", k, l);
                    print_array(result_f2, length_f2);
                }
                else print_error(error);
            }
            else print_error(-2);
        }
        else print_error(-1);
    }
    else print_error(-1);

    if (result_f1) {
        free(result_f1);
        result_f1 = NULL;
    }
    if (result_f2) {
        free(result_f2);
        result_f2 = NULL;
    }

    return 0;
}
