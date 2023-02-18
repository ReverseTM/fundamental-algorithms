#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum ERRORS
{
    success = 0,
    incorrect_arguments = -1,
    invalid_data = -2,
    no_memory = -3,
    file_isnt_open = -4,
    runtime_error = -5,
    no_person = -6,
    empty_list = -7
};

int isAlnum(char c)
{
    return (c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z');
}

int isNumber(char *string)
{
    for (int i = 0; string[i] != '\0'; i++) {
        if (i == 0 && (string[i] == '-' || string[i] == '+'))
            continue;
        if (!isAlnum(string[i]))
            return 0;
    }
    return 1;
}

int base_10(char *number, int base)
{
    if (!number)
        return 0;
    int sign = 1;
    char *ptr = NULL;
    int result = 0;

    if (*number == '-') {
        sign = -1;
        ptr = number;
    }
    else if (*number == '+')
        ptr = number;
    else
        ptr = number - 1;
    
    while (*++ptr)
        result = result * base + (((*ptr) >= '0' && (*ptr) <= '9') ? *ptr - '0' : *ptr - 'A' + 10);
    
    return result * sign;
}

int minBase(char *number)
{
    char max = '0';
    for (int i = 0; number[i] != '\0'; i++) {
        if (i == 0 && (number[i] == '-' || number[i] == '+'))
            continue;
        if (number[i] > max)
            max = number[i];
    }
    return (max >= '0' && max <= '9') ? max - '0' + 1 : max -'A' + 11;
}

int getLexem(FILE *inputFile, char **string)
{
    int size = 2;
    int currentPosition = 0;
    char *tmp = NULL;

    (*string) = (char *)malloc(sizeof(char) * size);
    if (!(*string))
    {
        return no_memory;
    }

    char symbol;
    while (symbol = fgetc(inputFile))
    {
        if (currentPosition == 0 && (symbol == '\n' || symbol == ' ' || symbol == '\t'))
            continue;
        if (symbol == '\n' || symbol == ' ' || symbol == '\t' || symbol == EOF)
            break;

        if (currentPosition >= size)
        {
            size *= 2;

            if (!(tmp = (char *)realloc((*string), sizeof(char) * size)))
            {
                free((*string));
                *string = NULL;
                return no_memory;
            }
            else
                *string = tmp;
        }
        (*string)[currentPosition++] = symbol;
    }
    (*string)[currentPosition] = '\0';

    return success;
}

int main()
{
    FILE *inputFile, *outputFile;
    char *currentNumber = NULL;
    int min_base = 0;
    int decim = 0;

    inputFile = fopen("input.txt", "r");
    outputFile = fopen("output.txt", "w");

    if (inputFile == NULL || outputFile == NULL)
    {
        printf("Error opening file\n");
        exit(1);
    }

    while (!feof(inputFile))
    {
        getLexem(inputFile, &currentNumber);
        if (isNumber(currentNumber)) {
            min_base = minBase(currentNumber);
            decim = base_10(currentNumber, min_base);
            fprintf(outputFile, "%s    %d    %d\n", currentNumber, min_base, decim);
        }
        free(currentNumber);
        currentNumber = NULL;
    }
    fclose(inputFile);
    fclose(outputFile);
    return 0;
}
