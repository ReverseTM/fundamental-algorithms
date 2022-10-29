#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define PI 3.14
#define epsilon 0.000000000000000000001

int check_epsilon_validity(double eps)
{
    if (!(*(((int*)&eps) + 1) >> (sizeof(int) * 8 - 1)))
        if (!(*((int*)&eps) == 0 && *((int*)&eps) == 0))
            return 1;
    return 0;
}

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
    double numerator = 1.0;
    double denominator = factorial(m - k);

    for (int i = k + 1; i <= m; i++)
        numerator *= i;
    
    return (numerator / denominator);
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
    if (!check_epsilon_validity(eps))
        return -1;
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
    if (!check_epsilon_validity(eps))
        return -1;
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
    if (!check_epsilon_validity(eps))
        return -1;
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
    if (!check_epsilon_validity(eps))
        return -1;
    int n = 0;
    double element = 0.0;
    double sum = 0.0;
    double fuc = 1.0;
    do {
        if (n == 0)
            fuc = 1;
        else
            fuc *= n;
        element = 1.0 / fuc;
        sum += element;
        n++;
    } while (fabs(element) > eps);
    return sum;
}

double pi_limit(double eps)
{
    if (!check_epsilon_validity(eps))
        return -1;
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
    if (!check_epsilon_validity(eps))
        return -1;
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
    if (!check_epsilon_validity(eps))
        return -1;
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
    if (!check_epsilon_validity(eps))
        return -1;
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
    if (!check_epsilon_validity(eps))
        return -1;
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
    if (!check_epsilon_validity(eps))
        return -1;
    int n = 2;
    double element = 0.0;
    double mult = 0.0;
    double mult_new = 1.0;
    double power = 0.25;
    do {
        mult = mult_new;
        element = pow(2, power);
        power *= 0.5;
        mult_new *= element;
        n++;
    } while (fabs(mult_new - mult) > eps);
    return mult;
}

double gamma_limit(double eps)
{
    if (!check_epsilon_validity(eps))
        return -1;
    eps = 0.01;
    double m = 2;
    double result = 0.0;
    double result_new = 0.0;
    double element = 0.0;
    double sum = 0.0;
    int fuc = 0;
    do {
        result = result_new;
        sum = 0.0;
        fuc = 1;
        for (int k = 1; k <= m; k++) {
            fuc *= k;
            element = (C(m, k) * (pow(-1.0, k) / k) * log(fuc));
            sum += element;
        }
        result_new = sum;
        m++;
    } while (fabs(result_new - result) > eps);
    return result;
}

double gamma_row(double eps)
{   
    if (!check_epsilon_validity(eps))
        return -1;
    eps = 0.0000000000001;
    int k = 3;
    double sum = 0.0;
    double sum_new = 0.5;
    double element= 0.0;
    do {
        sum = sum_new;
        element = ((1.0 / pow(floor(sqrt(k)), 2)) - (1.0 / k));
        sum_new += element;
        if (element < epsilon)
            sum = 0.0;
        k++;
    } while (fabs(sum_new - sum) > eps);
    return (sum_new - pow(PI, 2) / 6.0);
}

/*int check_epsilon_validity_var_1(double eps)
{
    if (!(*((char*)&eps + sizeof(double) - 1) >> (sizeof(char) * 8 - 1)))
        if (!(*((int*)&eps) == 0 && *((int*)&eps) == 0))
            return 1;
    return 0;
}*/

/*double generate_double_value()
{
    /*int i = 0;
    const int values_count = sizeof(double) / sizeof(int);

    int value[values_count];

    for (; i < values_count; i++)
    {
        value[i] = rand();
        value[i] |= ((rand() % 2) << sizeof(int) * 8 - 1);
    }

    return *((double*)value);*/

    //return ((double)rand() * (1000 + 1000)) / (double)RAND_MAX - 1000;
//} 

int main(int argc, char *argv[])
{
    int accuracy = 0;
    double result = 0.0;
    printf("Enter up to what sign you need accuracy\n");
    scanf("%d", &accuracy);
    double eps = pow(10, -accuracy);

    if ((result = exhibitor_limit(eps)) == -1)
        printf("Incorrect epsilon\n");
    else
        printf("e with limit: %.8lf\n", result);
    if ((result = exhibitor_row(eps)) == -1)
        printf("Incorrect epsilon\n");
    else    
        printf("e with row: %.8lf\n", exhibitor_row(eps));
    if ((result = dichotomy(function_e, 2.0, 3.0, eps)) == -1)
        printf("Incorrect epsilon\n");
    else    
        printf("e with equation: %.8lf\n", dichotomy(function_e, 2.0, 3.0, eps));
    printf("-------------------------\n");
    if ((result = pi_limit(eps)) == -1)
        printf("Incorrect epsilon\n");
    else
        printf("pi with limit: %.8lf\n", pi_limit(eps));
    if ((result = pi_row(eps)) == -1)
        printf("Incorrect epsilon\n");
    else
        printf("pi with row: %.8lf\n", pi_row(eps));
    if ((result = dichotomy(function_pi, 3.0, 4.0, eps)) == -1)
        printf("Incorrect epsilon\n");
    else
        printf("pi with equation: %.8lf\n", dichotomy(function_pi, 3.0, 4.0, eps));
    printf("-------------------------\n");
    if ((result = ln2_limit(eps)) == -1)
        printf("Incorrect epsilon\n");
    else
        printf("ln2 with limit: %.8lf\n", ln2_limit(eps));
    if ((result = ln2_row(eps)) == -1)
        printf("Incorrect epsilon\n");
    else
        printf("ln2 with row: %.8lf\n", ln2_row(eps));
    if ((result = dichotomy(function_ln2, 0.0, 1.0, eps)) == -1)
        printf("Incorrect epsilon\n");
    else
        printf("ln2 with equation: %.8lf\n", dichotomy(function_ln2, 0.0, 1.0, eps));
    printf("-------------------------\n");
    if ((result = sqrt2_limit(eps)) == -1)
        printf("Incorrect epsilon\n");
    else
        printf("sqrt(2) with limit: %.8lf\n", sqrt2_limit(eps));
    if ((result = sqrt2_row(eps)) == -1)
        printf("Incorrect epsilon\n");
    else
        printf("sqrt(2) with row: %.8lf\n", sqrt2_row(eps));
    if ((result = dichotomy(function_sqrt2, 1.0, 2.0, eps)) == -1)
        printf("Incorrect epsilon\n");
    else
        printf("sqrt(2) with equation: %.8lf\n", dichotomy(function_sqrt2, 1.0, 2.0, eps));
    printf("-------------------------\n");
    if ((result = gamma_limit(eps)) == -1)
        printf("Incorrect epsilon\n");
    else
        printf("gamma with limit: %.8lf\n", gamma_limit(eps));
    if ((result = gamma_row(eps)) == -1)
        printf("Incorrect epsilon\n");
    else
        printf("gamma with row: %.8lf\n", gamma_row(eps));
    if ((result = dichotomy(function_gamma, 0.0, 1.0, eps)) == -1)
        printf("Incorrect epsilon\n");
    else
        printf("gamma with equation: %.8lf\n", dichotomy(function_gamma, 0.0, 1.0, eps));

    return 0;
}
