#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

enum ERRORS {
    success = 0,
    no_memory = -1,
    incorrect_input = -2,
    invalid_data = -3
};

void print_error(int error)
{
    switch (error)
    {
    case incorrect_input:
        printf("Incorrect input!\n");
        break;
    case no_memory:
        printf("Memory allocation error!\n");
        break;
    case invalid_data:
        printf("Invalid data!\n");
        break;
    }
}

int strLen(const char *string)
{
    if (!string)
        return 0;
    int count = 0;
    while (*string++ != '\0') count++;
    return count;
}

int strCmp(const char* s1, const char* s2)
{
    while(*s1 && (*s1 == *s2))
    {
        s1++;
        s2++;
    }
    return *(const unsigned char*)s1 - *(const unsigned char*)s2;
}

int get_string(FILE *fin, char **string)
{
    if (!fin)
        return invalid_data;
    int count = 2;
    int cur_pos = 0;
    char *tmp = NULL;

    (*string) = (char *)malloc(sizeof(char) * count);
    if (!(*string))
    {
        return no_memory;
    }

    char symbol = fgetc(fin);

    while (symbol != '\n' && symbol != EOF && symbol != '\t' && symbol != ' ')
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
        symbol = fgetc(fin);
    }
    (*string)[cur_pos] = '\0';

    return success;
}

double logarithm(double a, double b)
{
    return log(a) / log(b);
}

int is_digit(char c)
{
    return (c >= '0' && c <= '9');
}

int to_upper_string(char *string)
{
    if (!string)
        return invalid_data;
    while (*string != '\0') {
        if (*string >= 'a' && *string <= 'z') {
            *string -= ('a' - 'A');
        }
        string++;
    }
    return success;
}

int is_alnum(char c)
{
    return ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}

int is_number(char *str)
{
    if (strLen(str) && (str[0] == '+' || str[0] == '-'))
        str++;
    for (int i = 0; str[i] != '\0'; i++)
        if (!is_alnum(str[i]))
            return 0;
    return 1;
}

int base_10(char *number, int base)
{
    if (!number)
        return 0;
    int sign = 1;
    char *ptr = NULL;
    int result = 0;

    if (*number == '-') {
        sign = -1;
        ptr = number;
    }
    else if (*number == '+')
        ptr = number;
    else
        ptr = number - 1;
    
    while (*++ptr)
        result = result * base + (is_digit(*ptr) ? *ptr - '0' : *ptr - 'A' + 10);
    
    return result * sign;
}

int convert_base(int number, int base, char **result)
{
    int size = 0;
    int sign = 0;

    if (number == 0)
        size = 1;
    else {
        if (number < 0) {
            number = ~number + 1;
            size++;
            sign = 1;
        }
        
        size += (int)logarithm(number, base) + 1;
    }
    (*result) = (char*)malloc(sizeof(char) * (size + 1));
    if (!(*result))
        return no_memory;
    char *ptr = (*result);
    if (sign)
        *ptr = '-';

    ptr += size;
    *ptr-- = '\0';

    if (number == 0) {
        *ptr = '0';
        return success;
    }

    int tmp = 0;
    while (number) {
        tmp = number % base;
        *ptr-- = tmp > 9 ? tmp - 10 + 'A' : tmp + '0';
        number /= base;
    } 
    return success;
}

int main(int argc, char *argv[])
{  
    int error = 0;
    int base = 0;
    char *max = (char*)malloc(sizeof(char) * 2);
    max[0] = '0';
    max[1] = '\0';
    char *number = NULL;
    char *tmp = NULL;
    int flag = 0;

    if (scanf("%d", &base) == 1 && base >= 2 && base <= 32) {
        getchar();
        while (1) {
            if ((error = get_string(stdin, &number)) == success) {
                if (strCmp(number, "stop")) {
                    if (is_number(number)) {
                        if ((error = to_upper_string(number)) == success) {
                            if (abs(base_10(number, base)) > abs(base_10(max, base))) {
                                tmp = max;
                                max = number;
                                free(tmp);
                                tmp = NULL;
                                flag = 1;
                            }
                        }
                        else {
                            free(number);
                            number = NULL;
                            print_error(error);
                            break;
                        }
                    }
                    else printf("Incorrect number\n");
                }
                else {
                    free(number);
                    number = NULL;
                    break;
                }
            }
            else {
                print_error(error);
                break;
            }

            free(number);
            number = NULL;
        }
        if (flag) {
            if (error == success) {
                for (int i = 9; i <= 36; i += 9) {
                    char *result = NULL;
                    if ((error = convert_base(base_10(max, base), i, &result)) == success) {
                        printf("%s(base=%d) in %d number system = %s\n", max, base, i, result);
                        free(result);
                        result = NULL;
                    }
                    else {
                        print_error(error);
                        break;
                    }
                }
            }
        }
        else printf("Nothing input!\n");
    }
    else {
        error = incorrect_input;
        print_error(error);
    }

    free(max);
    max = NULL;
    
    return 0;
}