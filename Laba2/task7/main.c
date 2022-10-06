#include <stdio.h>
#include <stdbool.h>
#include <stdarg.h>

bool convex(int count, ...)
{
    if (count < 6 || count % 2 != 0)
        return false;
    va_list iter;
    va_start(iter, count);

    bool sign = false;
    
    int n = count / 2;
    int X[n], Y[n];
    int x = 0, y = 0;

    for (int i = 0; i < count; i ++) {
        if (i % 2 == 0)
            X[x++] = va_arg(iter, int);
        else
            Y[y++] = va_arg(iter, int);
    }

    va_end(iter);

    for (int i = 0; i < n; i++) {
        int x1 = X[(i + 1) % n] - X[i % n];
        int y1 = Y[(i + 1) % n] - Y[i % n];

        int x2 = X[(i + 2) % n] - X[i % n];
        int y2 = Y[(i + 2) % n] - Y[i % n];

        int det = x1 * y2 - x2 * y1;

        if (i == 0)
            sign = (det > 0);
        else if (sign != (det > 0))
            return false;
    }
    return true;
}

double polynomial(int count, ...)
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
    if (convex(10, 2,1,4,1,5,3,3,5,1,3)) // convex(12, 3,0,5,2,4,4,3,2,2,4,1,2)
        printf("The polygon convex!\n");
    else
        printf("The polygon is not convex!\n");

    printf("%f\n", polynomial(5, 5.3, 5, 5.0, 4.0, 3.0, 2.0, 1.0, 1.1));
    return 0;
}
