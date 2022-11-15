#include <stdio.h>
#include <stdlib.h>

int factorial(int n) {
    if (n < 0)
        return -1;
    return (n < 2) ? 1 : n * factorial(n - 1);
}

double C(double n, double k)
{
    if (n < 0 || k < 0)
        return -1;
    double numerator = 1.0;
    double denominator = factorial(n - k);
    if (denominator == -1)
        return -1;
    for (int i = k + 1; i <= n; i++)
        numerator *= i;
    
    return (numerator / denominator);
}

int count_of_units(int number)
{
    int count = 0;
    for (; number; number >>= 1)
        count += number & 1;
    return count;
}

int count_of_consecutive_units(int number, int l)
{
    int count = 0;
    for (; number; number >>= 1) {
        if ((number & 1) == 1)
            count++;
        else
            count = 0;
        if (count == l)
            return 1;
    }
    return 0;
}

void function_1(int k, int l, int **result, int *length, int *error)
{
    if (k < 0 || l < 0 || l > k) {
        *error = -1;
        return;
    }
    int size = C(k, l);
    if (size == -1) {
        *error = -1;
        return;
    }
    (*result) = (int*)malloc(sizeof(int) * size);
    if (!(*result)) {
        *error = -2;
        return;
    }
    int count = 0;
    for (int number = 0; number < (1 << k); number++) {
        if (count_of_units(number) == l) {
            (*result)[(*length)++] = number;
        }
    }
}

void function_2(int k, int l, int **result, int *length, int *error)
{
    if (k < 0 || l < 0 || l > k) {
        *error = -1;
        return;
    }
    if (l == 0) {
        *result = (int*)malloc(sizeof(int) * ++(*length));
        if (!(*result)) {
            *error = -2;
            return;
        }
        (*result)[(*length) - 1] = 0;
        return;
    }
    int *tmp = NULL;
    for (int number = 0; number < (1 << k); number++) {
        if (count_of_consecutive_units(number, l)) {

            if (!(tmp = (int*)realloc(*result, sizeof(int) * ++(*length)))) {
                *error = -2;
                if (*result);
                    free(*result);
                *result = NULL;
                return;
            }
            *result = tmp;
            (*result)[(*length) - 1] = number;
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
    scanf("%d", &k);
    printf("Enter l: ");
    scanf("%d", &l);

    function_1(k, l, &result_f1, &length_f1, &error);
    function_
    return 0;
}
