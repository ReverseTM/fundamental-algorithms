#include <stdio.h>
#include <math.h>
#include <stdarg.h>

#define EPS 0.0000001

//Возведение в степень
double pow_(double number, int index)
{
    if (index == 0)
        return 1;
    else if (index == 1)
        return number;
    else if (index > 1)
        if (index % 2 == 0)
            return pow_(number * number, index / 2);
        else
            return pow_(number * number, index / 2) * number;
    else 
        return 1.0 / pow_(number, index * (-1));
}

//Среднее геометрическое
double avg_geom(int count, ...)
{
    double res = 1.0;
    va_list iter;
    va_start(iter, count);

    for (int i = 0; i < count; i++) {
        res *= va_arg(iter, double);
    }

    va_end(iter);
    
    if (count % 2 == 0 && res < 0.0)
        return EPS;
    return pow(res, 1.0 / count);
}

int main(int argc, char *argv[])
{
    double res = avg_geom(5, (double)13.4, (double)5.2, (double)23.4, (double)4.1, (double)3.8);
    if (res == EPS)
        printf("Error!\n");
    else
        printf("Average geometric: %f\n", res);
    printf("Exponentiation: %f\n", pow_(2, -4));
    return 0;
}
