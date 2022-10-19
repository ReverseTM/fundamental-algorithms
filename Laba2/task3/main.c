#include <stdio.h>
#include <math.h>

#define PI 3.14
#define epsilon 0.000000000000000000001

int isprime(int x)
{
    if (x > 1) {
        for (int i = 2; i < x; i++)
            if (x % i == 0)
                return 0;
        return 1;
    }
    else
        return 0;
}

int factorial(int n)
{
    return (n < 2) ? 1 : n * factorial(n - 1);
}

double C(double m, double k)
{
    return factorial(m) / (factorial(k) * factorial(m - k));
}

double _mult(int t) {
    double mult = 1.0;

    for (int i = 2; i <= t; i++)
        if (isprime(i))
            mult *= (i - 1.0) / i;
    return mult;
}

double limit_for_gamma(double eps)
{
    int t = 2;
    double result = 0.0;
    double result_new = 0.0;
    do {
        result = result_new;
        result_new = log(t) * _mult(t);
        t++;
    } while (fabs(result_new - result) > eps);
    return result_new;
}

double function_e(double x)
{
    return (log(x) - 1);
}

double function_pi(double x)
{
    return (sin(x));
}

double function_ln2(double x)
{
    return (exp(x) - 2);
}

double function_sqrt2(double x)
{
    return (pow(x, 2) - 2);
}

double function_gamma(double x)
{
    return (exp(-x) - limit_for_gamma(0.0001));
}

double dichotomy(double (*f)(double x), double a, double b, double eps)
{
    double x = 0.0;
    while (fabs(b - a) > eps) {
        x = (a + b) / 2.0;
        if (f(a) * f(x) < 0)
            b = x;
        else
            a = x;
    }
    return x;
}

double exhibitor_limit(double eps)
{
    int n = 1;
    double result = 0.0;
    double result_new = 0.0;
    do {
        result = result_new;
        result_new = pow(1.0 + 1.0 / n, n);
        n++;
    } while (fabs(result_new - result) > eps);
    return result;
}

double exhibitor_row(double eps)
{
    int n = 0;
    double element = 0.0;
    double sum = 0.0;
    do {
        element = 1.0 / factorial(n);
        sum += element;
        n++;
    } while (fabs(element) > eps);
    return sum;
}

double pi_limit(double eps)
{
    int n = 1;
    double result = 0.0;
    double result_new = 4.0;
    do {
        result = result_new;
        result_new *= (4 * n * (n + 1)) / pow(2 * n + 1, 2);
        n++;
    } while (fabs(result_new - result) > eps);
    return result;
}

double pi_row(double eps)
{
    int n = 1;
    double element = 0.0;
    double sum = 0.0;
    do {
        element = (pow(-1, n - 1)) / (2 * n - 1);
        sum += element;
        n++;
    } while (fabs(element) > eps);
    return (4 * sum);
}

double ln2_limit(double eps)
{
    int n = 1;
    double result = 0.0;
    double result_new = 0.0;
    do {
        result = result_new;
        result_new = n * (pow(2, 1.0 / n) - 1);
        n++;
    } while (fabs(result_new - result) > eps);
    return result;
}

double ln2_row(double eps)
{
    int n = 1;
    double element = 0.0;
    double sum = 0.0;
    do {
        element = (pow(-1, n - 1)) / n;
        sum += element;
        n++;
    } while (fabs(element) > eps);
    return sum;
}

double sqrt2_limit(double eps)
{
    int n = 1;
    double result = 0.0;
    double result_new = -0.5;
    do {
        result = result_new;
        result_new = result - (pow(result, 2) / 2.0) + 1.0;
        n++;
    } while (fabs(result_new - result) > eps);
    return result;
}

double sqrt2_row(double eps)
{
    int n = 2;
    double element = 0.0;
    double mult = 0.0;
    double mult_new = 1.0;
    do {
        mult = mult_new;
        element = pow(2, pow(2, -n));
        mult_new *= element;
        n++;
    } while (fabs(mult_new - mult) > eps);
    return mult;
}

double gamma_limit(double eps)
{
    eps = 0.01;
    double m = 2;
    double result = 0.0;
    double result_new = 0.0;
    double element = 0.0;
    double sum = 0.0;
    do {
        result = result_new;
        sum = 0.0;
        for (int k = 1; k <= m; k++) {
            element = (C(m, k) * (pow(-1.0, k) / k) * log(factorial(k)));
            sum += element;
        }
        result_new = sum;
        m++;
    } while (fabs(result_new - result) > eps);
    return result;
}

double gamma_row(double eps)
{   
    eps = 0.0000000000001;
    int k = 3;
    double result = 0.0;
    double result_new = 0.5;
    double element= 0.0;
    do {
        result = result_new;
        element = ((1.0 / pow(floor(sqrt(k)), 2)) - (1.0 / k));
        result_new += element;
        if (element < epsilon)
            result = 0.0;
        k++;
    } while (fabs(result_new - result) > eps);
    return (result_new - pow(PI, 2) / 6.0);
}

int main(int argc, char *argv[])
{
    int accuracy = 0;
    printf("Enter up to what sign you need accuracy\n");
    scanf("%d", &accuracy);
    double eps = pow(10, -accuracy);

    printf("e with limit: %.8lf\n", exhibitor_limit(eps));
    printf("e with row: %.8lf\n", exhibitor_row(eps));
    printf("e with equation: %.8lf\n", dichotomy(function_e, 2.0, 3.0, eps));
    printf("-------------------------\n");
    printf("pi with limit: %.8lf\n", pi_limit(eps));
    printf("pi with row: %.8lf\n", pi_row(eps));
    printf("pi with equation: %.8lf\n", dichotomy(function_pi, 3.0, 4.0, eps));
    printf("-------------------------\n");
    printf("ln2 with limit: %.8lf\n", ln2_limit(eps));
    printf("ln2 with row: %.8lf\n", ln2_row(eps));
    printf("ln2 with equation: %.8lf\n", dichotomy(function_ln2, 0.0, 1.0, eps));
    printf("-------------------------\n");
    printf("sqrt(2) with limit: %.8lf\n", sqrt2_limit(eps));
    printf("sqrt(2) with row: %.8lf\n", sqrt2_row(eps));
    printf("sqrt(2) with equation: %.8lf\n", dichotomy(function_sqrt2, 1.0, 2.0, eps));
    printf("-------------------------\n");
    printf("gamma with limit: %.8lf\n", gamma_limit(eps));
    printf("gamma with row: %.8lf\n", gamma_row(eps));
    printf("gamma with equation: %.8lf\n", dichotomy(function_gamma, 0.0, 1.0, eps));

    return 0;
}
