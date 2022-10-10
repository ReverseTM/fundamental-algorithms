#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>

//Нахождение максимума
int max(int a, int b)
{
    return (a > b ? a : b);
}

//Из символа получить число
int to_number(char symbol)
{
    if (symbol >= 'A' && symbol <= 'Z')
        return symbol - 'A' + 10;
    else if (symbol >= '0' && symbol <= '9')
        return symbol - '0';
}

//Из числа получить символ
int to_char(char number)
{
    if (number >= 10 && number <= 26)
        return number + 'A' - 10;
    else if (number >= 0 && number <= 9)
        return number + '0';
}

//Проверка на валидность числа
char *valid(char *string)
{
    if (strlen(string) > 1)
        while (*string == '0' || !isalnum(*string))
            string++;

    int length = strlen(string);

    for (int i = 0; i < length; i++)
        if (!isalnum(string[i]) || (isalpha(string[i]) && !isupper(string[i])))
            return "invalid";
            
    return string;
}

//Сложение столбиком
char *stacking(char *num1, char *num2, int base)
{
    int len_num1 = strlen(num1);
    int len_num2 = strlen(num2);
    int len_sum = max(len_num1, len_num2) + 1;
    char *sum = (char*)malloc(len_sum * sizeof(char) + 1);

    for (int i = 0; i < len_sum; i++)
        sum[i] = '0';
    sum[len_sum] = '\0';

    int add = 0;
    int tmp = 0;
    int a = 0, b = 0;
    for (int i = len_sum - 1; i >= 0; i--) {
        if (len_num1 - 1 >= 0)
            a = to_number(num1[len_num1 - 1]);
        else a = 0;
        
        if (len_num2 - 1 >= 0)
            b = to_number(num2[len_num2 - 1]);
        else b = 0;

        tmp = a + b + add;
        add = tmp / base;
        sum[i] = to_char(tmp % base);
        len_num1--;
        len_num2--;;
    }

    char *tmp_sum = NULL;
    char *ptr = sum;

    for (int i = 0; i < len_sum - 1 && sum[i] == '0'; i++)
        ptr++;

    int len_ptr = strlen(ptr);

    for (int i = 0; i < len_ptr; i++)
        sum[i] = ptr[i];
    sum[len_ptr] = '\0';

    if (!(tmp_sum = (char*)realloc(sum, sizeof(char) * strlen(ptr) + 1))) {
        free(sum);
        return "error";
    }
    sum = tmp_sum;

    return sum;
}

//Сложение элементов
char *sum(int count, int base, ...)
{
    va_list iter;
    va_start(iter,base);

    char *result = (char*)malloc(sizeof(char) + 1);
    result[0] = '0';
    result[1] = '\0';
    char *tmp = NULL;
    char *number = NULL;

    for (int i = 0; i < count; i++) {
        if (!strcmp(number = valid(va_arg(iter, char*)), "invalid"))
            continue;
        else
            tmp = stacking(result, number, base);
            if (result)
                free(result);
            result = tmp;
            
            if (!strcmp(result, "error")) {
                va_end(iter);
                return "error";
            }
    }
    
    va_end(iter);

    return result;
}

int main(int argc, char *argv[])
{   
    int base = 16;
    char *result = sum(4, base, "5AF3B", "F42-2", "00118E4", "123f4E");

    if (!strcmp(result, ""))
        printf("No valid numbers were sent!\n");
    else if (!strcmp(result, "error"))
        printf("Execution error!\n");
    else {
        printf("Sum = %s\n", result);
        free(result);
    }

    return 0;
}