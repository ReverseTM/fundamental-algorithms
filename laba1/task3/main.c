#include <stdio.h>
#include "string.h"

int main()
{
    ptr_string str1 = create_string("hello");
    ptr_string str2 = create_string("world");
    ptr_string str3 = strconcat(str1->data, str2->data);
    printf("%d, %s\n", str3->length, str3->data);
}