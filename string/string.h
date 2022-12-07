#ifndef STRING_H
#define STRING_H

typedef struct string{
    unsigned char *data;
    unsigned int len; 
}myString, *ptr_string, **string_array;

ptr_string createString(const char* string);
ptr_string strConcat(const char *left, const char *right);
ptr_string strToken(ptr_string string, const char *delim);
ptr_string getStringFromFile(FILE *file);
string_array strSplit(ptr_string string, const char* delim, int *size);
size_t strLength(const char* string);
void freeString(ptr_string string);
void freeStringArray(string_array array, int size);

#endif //STRING_H