#include <stdio.h>
#include <stdlib.h>

int main()
{
    char *str = (char *)malloc(sizeof(char) * 5);

    str = "00123";

    int i = 0;
    int count = 0;
    while (*str == '0')
    {
        str++;
        count++;
    }
    for (int j = count; j > 0; j--)
    {
        free(str - j);
    }
    printf("%s\n", str);
    return 0;
}
