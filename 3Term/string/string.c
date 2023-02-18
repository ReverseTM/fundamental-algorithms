#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "string.h"

ptr_string createString(const char* string)
{
    ptr_string str = (ptr_string)malloc(sizeof(myString));
    if (!str)
        return NULL;
    str->len = strLength(string);
    str->data = (char*)malloc(sizeof(char) * (str->len + 1));
    if (!(str->data)) {
        free(str);
        str = NULL;
        return NULL;
    }
    strcpy(str->data, string);
    return str;
}

size_t strLength(const char* string)
{
    if (!string)
        return 0;
    size_t len = 0;
    while (*string++ != '\0')
        len++;
    return len;
}

void freeString(ptr_string string)
{
    if (string) {
        if (string->data) { 
            free(string->data);
            string->data = NULL;
        }
        free(string);
        string = NULL;
    }
}

void freeStringArray(string_array array, int size)
{
    if (array) {
        for (int i = 0; i < size; i++) {
            if (array[i]) {
                if (array[i]->data) {
                    free(array[i]->data);
                    array[i]->data = NULL;
                }
                free(array[i]);
                array[i] = NULL;
            }
        }
        free(array);
        array = NULL;
    }
}

ptr_string strConcat(const char *left, const char *right)
{
    int lenght_left = strLength(left), lenght_right = strLength(right);
    ptr_string string = (ptr_string)malloc(sizeof(ptr_string));
    if (!string)
        return NULL;
    string->len = lenght_left + lenght_right;
    string->data = (char*)malloc(sizeof(char) * (string->len + 1));
    memcpy(string->data, left, lenght_left);
    memcpy(string->data + lenght_left, right, lenght_right);
    return string;
}

/*
char *strtoken(char *string, const char *delim)
{
    static char *data;
    if (string) {
        data = string;
        while (*data && *data == *delim)
            *data++ = '\0';
    }
    if (!*data)
        return NULL;
    string = data;
    while (*data && *data != *delim && *data != '\0')
        data++;
    while (*data && *data == *delim)
        *data++ = '\0';
    return string;
}
*/

ptr_string strToken(ptr_string string, const char *delim)
{
    if (!delim)
        return NULL;
    static char *data;
    if (string) {
        data = string->data;
        while (*data && *data == *delim)
            *data++ = '\0';
    }
    if (!*data)
        return NULL;
    char *tmp = data;
    while (*data && *data != *delim && *data != '\0')
        data++;
    while (*data && *data == *delim)
        *data++ = '\0';

    ptr_string str = createString(tmp);
    if (!str)
        return NULL;

    return str;
}

ptr_string getStringFromFile(FILE *file)
{
    int count = 2;
    int cur_pos = 0;

    char *string = (char*)malloc(sizeof(char) * count);
    if (!string)
        return NULL;

    char *tmp = NULL;
    
    char symbol = fgetc(file);
    while (symbol != '\n' && symbol != EOF) {
        if (cur_pos >= count) {
            count *= 2;
            if (!(tmp = (char*)realloc(string, sizeof(char) * count))) {
                free(string);
                string = NULL;
                return NULL;
            }
            else
                string = tmp;
        }
        string[cur_pos++] = symbol;
        symbol = fgetc(file);
    }
    string[cur_pos] = '\0';

    ptr_string str = createString(string);

    free(string);
    string = NULL;

    if (str)
        return str;
    else
        return NULL;
}

/*
char **strSplit(char* string, const char* delim, int *size)
{
    if (!string || !delim)
        return NULL;
    
    for (int i = 0; string[i] != '\0'; i++) {
        if (string[i] == *delim && (string[i + 1] && string[i + 1] != *delim))
            (*size)++;
    }

    char **result = (char**)malloc(sizeof(char*) * ++(*size));
    if (!result)
        return NULL;
    int cur_pos = 0;
    for (char *str = strToken(string, delim); str && cur_pos < (*size); str = strToken(NULL, delim)) {
        printf("%d\n", strlen(str));
        result[cur_pos] = (char*)malloc(sizeof(char) * (strlen(str) + 1));
        if (!result[cur_pos]) {
            for (int i = 0; i < *size; i++) {
                if (result[i]) {
                    free(result[i]);
                    result[i] = NULL;
                }
            }
            free(result);
            result = NULL;
            return NULL;
        }
        strcpy(result[cur_pos++], str);
    }
    return result;
}
*/

string_array strSplit(ptr_string string, const char* delim, int *size)
{
    if (!string || !delim)
        return NULL;

    //int size = 0;
    
    for (int i = 0; string->data[i] != '\0'; i++) {
        if (string->data[i] == *delim)
            (*size)++;
    }

    string_array result = (string_array)malloc(sizeof(ptr_string) * ++(*size));
    if (!result)
        return NULL;
    int cur_pos = 0;
    for (ptr_string str = strToken(string, delim); str && cur_pos < (*size); str = strToken(NULL, delim)) {
        result[cur_pos++] = str;
    }
    return result;
}
