#include <stdio.h>
#include <stdlib.h>

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
    int *tmp = NULL;
    for (int number = 0; number < (1 << k); number++) {
        if (count_of_units(number) == l) {
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
    function_2(k, l, &result_f2, &length_f2, &error);

    switch (error)
    {
    case 0:
        if (result_f1) {
            printf("Found %d %d-bit integers, in the binary notation of which there are %d ones: ",length_f1, k, l);
            for (int i = 0; i < length_f1; i++)
                printf("%d ", result_f1[i]);
            printf("\n");
            free(result_f1);
            result_f1 = NULL;
        }
        if (result_f2) {
            printf("Found %d %d-bit integers, in the binary notation of which there are %d consecutive ones: ",length_f2, k, l);
            for (int i = 0; i < length_f2; i++)
                printf("%d ", result_f2[i]);
            printf("\n");
            free(result_f2);
            result_f2 = NULL;
        }
        break;
    case -1:
        printf("Incorrect input!\n");
        break;
    case -2:
        printf("Memory allocation error!\n");
        break;
    }
    return 0;
}
