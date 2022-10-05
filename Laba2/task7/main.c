#include <stdio.h>
#include <stdbool.h>
#include <stdarg.h>

//todo выпуклость многогранника.

double mnogochlen(int count, ...)
{
    va_list iter;
    va_start(iter, count);
    double x = va_arg(iter, double);
    int index = va_arg(iter, int);
    double res = 0;

    for (int i = 0; i <= index; i++)
        res = res * x + va_arg(iter, double);


    va_end(iter);

    return res;
}

int main(int argc, char *argv[])
{
    printf("%f\n", mnogochlen(5, 5.3, 5, 5.0, 4.0, 3.0, 2.0, 1.0, 1.1));
    return 0;
}