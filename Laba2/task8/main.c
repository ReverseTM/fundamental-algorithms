#include <stdio.h>
#include <math.h>

double function1(double x) {
	return log(x);
}

double function(double x) {
	return exp(x) - 5 * x + 1;
}

double dichotomy(double(*f)(double x), double a, double b, double eps)
{
    double x = 0.0;

    do {
        x = (a + b) / 2.0;
        if (f(a) * f(x) < 0)
            b = x;
        else if (f(x) * f(b) < 0)
            a = x;
        else
            return -1;

    } while (fabs(b - a) > eps);

    return x;
}

int main(int argc, char *argv[])
{
    double root = dichotomy(function1, -5, 2.0, 0.01);

    if (root == -1)
        printf("Root not found!\n");
    else
        printf("Root of the equation: %f\n", root);
    return 0;
}