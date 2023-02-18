#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>

char *isvalid(char* number)
{
    int flag = 1;
    int sum = 0;
    if (number[0] == '0' && number[1] == '.' && strlen(number) >= 3) {
        for (int i = 2; i < strlen(number); i++) {
            if (!isdigit(number[i]))
                flag = 0;
            sum += number[i] - '0';
        }
        if (sum <= 0)
            flag = 0;
    }
    else
        flag = 0;
    
    if (flag)
        return number;
    else
        return "invalid";
}

int nod(int a, int b) 
{
    return b ? nod(b, a % b) : a;
}

void common_fraction(char *number, int *numerator, int *denominator)
{
    for (int i = 2; number[i] != '\0'; i++) {
        *numerator = *numerator * 10 + (number[i] - '0');
        *denominator *= 10;
        }

    int NOD = nod(*numerator, *denominator);
    *numerator /= NOD;
    *denominator /= NOD;
}

int in_array(int *array, int count, int number)
{
    for (int i = 0; i < count; i++)
        if (array[i] == number)
            return 1;
    return 0;
}

char **final_representation(int n, int *error, int *cnt, int base, ...)
{
    va_list iter;
    va_start(iter, base);

    int numerator = 0;
    int denominator = 0;
    int count = 0;
    int count_result = 0;
    int remainder = 0;
    int flag = 1;
    char *number = NULL;
    int *data = NULL;
    int *tmp_data = NULL;
    char **result = NULL;
    char **tmp_result = NULL;

    for (int i = 0; i < n; i++) {
        if (!strcmp(number = isvalid(va_arg(iter, char*)), "invalid")) {
            *error = -1;
            return result;
        }
        numerator = 0;
        denominator = 1;
        flag = 1;
        count = 0;

        common_fraction(number, &numerator, &denominator);

        remainder = numerator % denominator;

        if (remainder == 0) {
            if (!(tmp_result = (char**)realloc(result, sizeof(char*) * ++count_result))) {
                *error = -1;
                if (result) {
                    for (int j = 0; j < count_result; j++)
                        free(result[j]);
                    free(result);
                    result = NULL;
                }
                return result;
            }
            else {
                result = tmp_result;
                result[count_result - 1] = (char*)malloc(sizeof(char) * (strlen(number) + 1));
                if (!result[count_result - 1]) {
                    *error = -1;
                    if (result) {
                        for (int j = 0; j < count_result; j++)
                            free(result[j]);
                        free(result);
                        result = NULL;
                    }
                    return result;
                }
                else
                    strcpy(result[count_result - 1], number);
            }
        }
        else {
            while (flag) {
                if (!(tmp_data = (int*)realloc(data, sizeof(int) * ++count))) {
                    *error = -1;
                    if (data)
                        free(data);
                    if (result) {
                        for (int j = 0; j < count_result; j++)
                            free(result[j]);
                        free(result);
                        result = NULL;
                    }
                    return result;
                }
                else {
                    data = tmp_data;
                    data[count - 1] = remainder;
                }

                remainder *= base;
                remainder %= denominator;

                if (remainder == 0) {
                    flag = 0;
                    if (!(tmp_result = (char**)realloc(result, sizeof(char*) * ++count_result))) {
                        *error = -1;
                        if (data)
                            free(data);
                        if (result) {
                            for (int j = 0; j < count_result; j++)
                                free(result[j]);
                            free(result);
                            result = NULL;
                        }
                        return result;
                    }
                    else {
                        result = tmp_result;
                        result[count_result - 1] = (char*)malloc(sizeof(char) * (strlen(number) + 1));
                        if (!result[count_result - 1]) {
                            *error = -1;
                            if (data)
                                free(data);
                            if (result) {
                                for (int j = 0; j < count_result; j++)
                                    free(result[j]);
                                free(result);
                                result = NULL;
                            }
                            return result;
                        }
                        else
                            strcpy(result[count_result - 1], number);
                    }
                }
                else {
                    if (in_array(data, count, remainder))
                        flag = 0;
                }
            }
            free(data);
            data = NULL;
        }
    }
    *cnt = count_result;
    va_end(iter);

    return result;
}

int main(int argc, char *argv[])
{
    int base = 10;
    int error = 0;
    int count_result = 0;

    char **result = final_representation(5, &error, &count_result, base, "0.37", "0.0000001", "0.5", "0.75", "0.2");

    switch(error) {
        case 0:
            printf("Numbers having a final representation in number system '%d': ", base);
            for (int i = 0; i < count_result; i++) {
                if (i == count_result - 1)
                    printf("%s\n", result[i]);
                else
                    printf("%s, ", result[i]);
                free(result[i]);
            }
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