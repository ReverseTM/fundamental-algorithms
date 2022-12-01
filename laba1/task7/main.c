#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 8

enum error {
    success = 0,
    no_array = -1,
    runtime_error = -2
};

void print_error(int error)
{
    switch (error) {
        case no_array:
            printf("No array!\n");
            break;
        case runtime_error:
            printf("Something went wrong!\n");
            break;
    }
}

int fill_array(int *array)
{
    if (array) {
        for (int i = 0; i < SIZE; i++)
            array[i] = -10 + rand() % (30 - 10 + 1);
        return success;
    }
    return no_array;
}

int find_min(int *array, int *min)
{
    if (array && min) {
        for (int i = 0; i < SIZE; i++)
            if (array[i] < array[*min])
                *min = i;
        return success;
    }
    return runtime_error;
}

int find_max(int *array, int *max)
{
    if (array && max) {
        for (int i = 0; i < SIZE; i++)
            if (array[i] > array[*max])
                *max = i;
        return success;
    }
    return runtime_error;
}

int swap(int *a, int *b)
{
    if (a && b) {
        int tmp = *a;
        *a = *b;
        *b = tmp;
        return success;
    }
    return runtime_error;
}

void print_array(int *array)
{
    if (array) {
        for (int i = 0; i < SIZE; i++)
            printf("%d ", array[i]);
        printf("\n");
    }
}

int main(int argc, char *argv[])
{
    int error = 0;
    srand(time(NULL));
    int array[SIZE];
    if ((error = fill_array(array)) == success) {
        printf("Array before:\n");
        print_array(array);
        int min = 0;
        int max = 0;
        if ((error = find_min(array, &min)) == success && find_max(array, &max) == success) {
            if ((error = swap((array + min), (array + max))) == success) {
                printf("Array after swap:\n");
                print_array(array);
            }
            else
                print_error(error);
        }
        else
            print_error(error);
    }
    else
        print_error(error);

    return 0;
}