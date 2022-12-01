#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "string.h"

ptr_string create_string(const char* str)
{
    ptr_string string = (ptr_string)malloc(sizeof(ptr_string));
    string->length = strlength(str);
    string->data = (char*)malloc(sizeof(char) * (string->length + 1));
    strcpy(string->data, str);
    return string;
}

size_t strlength(const char* str)
{
    size_t len = 0;
    while (*str++ != '\0')
        len++;
    return len;
}

ptr_string strconcat(const char *left, const char *right)
{
    int lenght_left = strlength(left), lenght_right = strlength(right);
    ptr_string string = (ptr_string)malloc(sizeof(ptr_string));
    string->length = lenght_left + lenght_right;
    string->data = (char*)malloc(sizeof(char) * (string->length + 1));
    memcpy(string->data, left, lenght_left);
    memcpy(string->data + lenght_left, right, lenght_right);
    return string;
}

int len(ptr_string string)
{
    return string->length;
}

