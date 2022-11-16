#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "str.h"
#include "defs.h"

int add_symbol(char **string, char symbol, int *size)
{
    if (!(*string))
    {
        *size = 2;
        (*string) = (char *)malloc(sizeof(char) * (*size));
        if (!*string)
            return no_memory;
        (*string)[0] = symbol;
        (*string)[1] = '\0';

        return success;
    }

    int length = strlen(*string);
    char *tmp = NULL;

    if (length >= *size)
    {
        (*size) *= 2;

        if (!(tmp = (char *)realloc((*string), sizeof(char) * (*size))))
        {
            free((*string));
            *string = NULL;
            return no_memory;
        }
        else
            *string = tmp;
    }
    (*string)[length] = symbol;
    (*string)[length + 1] = '\0';

    return success;
}

int get_string(FILE *fout, char **string)
{
    if (!fout)
        return file_isnt_open;

    int count = 2;
    int cur_pos = 0;
    char *tmp = NULL;

    (*string) = (char *)malloc(sizeof(char) * count);
    if (!(*string))
    {
        return no_memory;
    }

    char symbol = fgetc(fout);
    while (symbol != '\n' && symbol != EOF)
    {
        if (cur_pos >= count)
        {
            count *= 2;

            if (!(tmp = (char *)realloc((*string), sizeof(char) * count)))
            {
                free((*string));
                *string = NULL;
                return no_memory;
            }
            else
                *string = tmp;
        }
        (*string)[cur_pos++] = symbol;
        symbol = fgetc(fout);
    }
    (*string)[cur_pos] = '\0';

    return success;
}