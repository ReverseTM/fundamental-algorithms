#include <stdio.h>
#include <stdlib.h>

void swap(char *number, int count)
{
    char *start = number, *finish = number + count - 1;
    while (start < finish)
    {
        char tmp = *start;
        *start = *finish;
        *finish = tmp;
        start++;
        finish--;
    }
}

char *transform(int number, int r, int *error)
{
    if (r < 1 || r > 5)
    {
        *error = -1;
        return NULL;
    }
    char *result = NULL;
    int count = 0;
    int sign = 0;
    if (number < 0)
    {
        number *= -1;
        sign = 1;
    }
    char *tmp = NULL;
    int remainder = 0;

    while (number)
    {
        remainder = number & ((1 << r) - 1);
        if (!(tmp = (char *)realloc(result, sizeof(char) * (++count + 1))))
        {
            *error = -2;
            free(result);
            result = NULL;
            return result;
        }
        result = tmp;
        result[count - 1] = remainder < 10 ? (remainder + '0') : (remainder + 'A' - 10);
        number = number >> r;
    }
    if (sign)
    {

        if (!(tmp = (char *)realloc(result, sizeof(char) * (++count + 1))))
        {
            *error = -2;
            free(result);
            result = NULL;
            return result;
        }
        result = tmp;
        result[count - 1] = '-';
    }
    result[count] = '\0';
    swap(result, count);
    return result;
}

int main()
{
    char *result = NULL;
    int number = 0;
    int r = 0;
    int error = 0;
    result = transform(-10, 1, &error);
    printf("Enter number: ");
    if (scanf("%d", &number) != 1)
        printf("Incorrect input! Not integer.\n");
    else
    {
        printf("Enter degree of 2: ");
        if (scanf("%d", &r) != 1)
            printf("Incorrect input! Not integer.\n");
        else
            result = transform(number, r, &error);
    }
    switch (error)
    {
    case 0:
        printf("A %d in the %d number system has the following representation: ", number, 1 << r);
        printf("%s\n", result);
        free(result);
        break;
    case -1:
        printf("Incorrect input!\n");
        break;
    case -2:
        printf("Memory allocation error!\n");
        break;
    }

    return 0;
}
