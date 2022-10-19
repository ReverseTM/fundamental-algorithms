#include <stdio.h>
#include <math.h>

int factorial(int n)
{
    return (n < 2) ? 1 : n * factorial(n - 1);
}

double C(int m, int k)
{
    return factorial(m) / (factorial(k) * factorial(m - k));
}

double function_e(double x)
{
    return (log(x) - 1);
}

double function_pi(double x)
{
    return (cos(x) + 1);
}

double function_ln2(double x)
{
    return (exp(x) - 2);
}

double function_sqrt2(double x)
{
    return (pow(x, 2) - 2);
}

double dichotomy(double (*f)(double x), double a, double b, double eps)
{
    double x = 0.0;
    while (fabs(b - a) > eps)
    {
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
    do
    {
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
    do
    {
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
    do
    {
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
    do
    {
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
    do
    {
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
    do
    {
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
    do
    {
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
    double mult = 1.0;
    do
    {
        element = pow(2, pow(2, -n));
        mult *= element;
        n++;
    } while (fabs(element) > eps);
    return mult;
}

double gamma_limit(double eps)
{
    int m = 1;
    double element = 0.0;
    double sum = 0.0;
    double result = 0.0;
    double result_new = 0.0;
    do
    {
        result = result_new;
        for (int k = 1; k <= m; k++)
        {
            element = C(m, k) * (pow(-1.0, k) / k) * log(factorial(k));
            sum += element;
        }
        result_new = sum;
        m++;
    } while (fabs(result_new - result) > eps);
    return result;
}

int main(int argc, char *argv[])
{
    // int accuracy = 0;
    // printf("Enter up to what sign you need accuracy\n");
    // scanf("%d", &accuracy);
    // double eps = pow(10, -accuracy);
    double eps = pow(10, -6);

    printf("e with limit: %lf\n", exhibitor_limit(eps));
    printf("e with row: %lf\n", exhibitor_row(eps));
    printf("e with equation: %lf\n", dichotomy(function_e, 2.0, 3.0, eps));
    printf("-------------------------\n");
    printf("pi with limit: %lf\n", pi_limit(eps));
    printf("pi with row: %lf\n", pi_row(eps));
    printf("pi with equation: %lf\n", dichotomy(function_pi, 3.0, 4.0, eps));
    printf("-------------------------\n");
    printf("ln2 with limit: %lf\n", ln2_limit(eps));
    printf("ln2 with row: %lf\n", ln2_row(eps));
    printf("ln2 with equation: %lf\n", dichotomy(function_ln2, 0.0, 1.0, eps));
    printf("-------------------------\n");
    printf("sqrt(2) with limit: %lf\n", sqrt2_limit(eps));
    // printf("sqrt(2) with row: %lf\n", sqrt2_row(eps));
    printf("sqrt(2) with equation: %lf\n", dichotomy(function_sqrt2, 1.0, 2.0, eps));
    printf("-------------------------\n");
    printf("gamma with limit: %lf\n", gamma_limit(eps));

    return 0;
}
