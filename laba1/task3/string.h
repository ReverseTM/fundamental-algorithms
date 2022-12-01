#ifndef STRING_H
#define STRING_H

typedef struct string{
    unsigned char *data;
    unsigned int length; 
}string, *ptr_string;

ptr_string create_string(const char* str);
size_t strlength(const char* str);
ptr_string strconcat(const char *left, const char *right);
int len(ptr_string string);

#endif //STRING_H