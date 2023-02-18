#include <stdio.h>
#include <stdlib.h>
#include "string.h"

int main()
{

    FILE *file = fopen("file.txt", "r");
    ptr_string string = getStringFromFile(file);
    fclose(file);

    int size = 0;
    string_array array = strSplit(string, " ", &size);
    printf("[");
    for (int i = 0; i < size; i++) {
        if (i == size - 1)
            printf("\"%s\"", array[i]->data); 
        else 
            printf("\"%s\", ", array[i]->data);
    }
    printf("]\n");
    

    freeStringArray(array, size);
    freeString(string);
    
    return 0;
}