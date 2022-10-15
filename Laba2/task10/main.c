#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

void common_fraction(char *number, int *numerator, int *denominator)
{
    if (number[0] == '1') {
        *numerator = 1;
        *denominator = 1;
    }
    else {
        for (int i = 2; number[i] != '\0'; i++) {
        *numerator = *numerator * 10 + (number[i] - '0');
        *denominator *= 10;
        }
    }
}

int in_array(int *array, int count, int number)
{
    for (int i = 0; i < count; i++)
        if (array[i] == number)
            return 1;
    return 0;
}

char **final_representation(int n, int *error, int base, ...)
{
    va_list iter;
    va_start(iter, base);
    int numerator = 0;
    int denominator = 0;
    int count = 0;
    int count_result = 0;
    int remainder = 0;
    int flag = 1;
    int *tmp_remainders = NULL;
    int *remainders = NULL;
    char **tmp_result = NULL;
    char **result = NULL;
    char *number = NULL;

    for (int i = 0; i < n; i++) {
        number = va_arg(iter, char*);
        numerator = 0;
        denominator = 1;
        flag = 1;
        count = 0;

        common_fraction(number, &numerator, &denominator);

        if ((remainder = numerator % denominator) == 0) {
            if (!(tmp_result = (char**)realloc(result, sizeof(char*) * ++count_result)))
                *error = 1;
            else {
                result = tmp_result;
                result[count_result - 1] = (char*)malloc(sizeof(char) * (strlen(number) + 1));
                strcpy(result[count_result - 1], number);
            }
        }
        else {
            while(flag) {
                if (!(tmp_remainders = (int*)realloc(remainders, sizeof(int) * ++count)))
                    *error = 1;
                else {
                    remainders = tmp_remainders;                
                    remainders[count - 1] = remainder;
                }
                remainder *= base;
                remainder %= denominator;

                if (remainder == 0) {
                    flag = 0;
                    if(!(tmp_result = (char**)realloc(result, sizeof(char*) * ++count_result)))
                        *error = 1;
                    else {
                        result = tmp_result;
                        result[count_result - 1] = (char*)malloc(sizeof(char) * (strlen(number) + 1));
                        strcpy(result[count_result - 1], number);
                    }
                }
                else {
                    if (in_array(remainders, count, remainder))
                        flag = 0;
                }
            }
            if (remainders)
                free(remainders);
        }
    }
    va_end(iter);
    
    return result;
}

int main(int argc, char *argv[])
{
    int base = 10;
    int error = 0;

    char **result = final_representation(3, &error, base, "0.5", "0.5", "0.2");
    if (result) {
        for (int i = 0; i < 3; i++) {
            printf("%s\n", result[i]);
            free(result[i]);
        }
        free(result);
    }

    return 0;
}