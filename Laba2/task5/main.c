#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int main(int argc, char *argv[])
{
    int length = 0, min_value = 0, max_value = 0;

    printf("Enter length array: \n");
    scanf("%d", &length);

    if (length <= 0) {
        printf("Incorrect input!\n");
        return 0;
    }

    printf("Enter range: \n");
    scanf("%d%d", &min_value, &max_value);

    if (min_value > max_value) {
        printf("Incorrect input!\n");
        return 0;
    }

    int array[length];

    srand(time(NULL));

    printf("Array: [ ");
    for(int i = 0; i < length; i++) {
        array[i] = min_value + rand() % (max_value - min_value + 1);
        printf("%d ", array[i]);
    }
    printf("]\n");

    char command[7];

    printf("\n\nEnter 'swap' to swap the minimum and maximum array elements\n\n");
    printf("Enter 'unique' to create a new array that contains unique elements from the original\n\n");
    printf("Enter 'quit' to terminate the program\n\n");

    while(1) {
        scanf("%7s", command);

        if (strcmp(command, "swap") && strcmp(command, "unique") && strcmp(command, "quit"))
            printf("Command '%s' does not exist!\n", command);
        else {
            if (!strcmp(command, "swap")) {
                int min = 0, max = 0;

                for (int i = 0; i < length; i++) {
                    if (array[i] < array[min])
                        min = i;
                    if (array[i] > array[max])
                        max = i;
                }
                
                swap(&array[min], &array[max]);

                printf("New array: [ ");
                for (int i = 0; i < length; i++) {
                    printf("%d ", array[i]);
                }
                printf("]\n");
                break;
            }
            else if (!strcmp(command, "unique")) {
                int count = 1;
                int flag = 1;
                int *new_array = (int*)malloc(sizeof(int) * count);
                
                if (new_array == NULL) {
                    printf("Memory not allocated!\n");
                    return 0;
                }

                new_array[0] = array[0];

                for (int i = 0; i < length; i++) {
                    flag = 1;
                    for (int j = 0; j < count; j++) {
                        if (array[i] == new_array[j]) {
                            flag = 0;
                            continue;
                        }
                    }
                    if (flag) {
                        new_array = (int*)realloc(new_array, ++count * sizeof(int));
                        new_array[count - 1] = array[i];
                    }
                }

                printf("New array: [ ");
                for (int i = 0; i < count; i++) {
                    printf("%d ", new_array[i]);
                }
                printf("]\n");

                free(new_array);
                break;
            }
            else if (!strcmp(command, "quit")) {
                break;
            }
        }
    }

    return 0;
}