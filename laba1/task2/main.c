#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define EPS 0.000000001

int is_digit(char *str)
{
    if (*str == '-' || *str == '+')
        str++;
    int count_dot = 0;
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (count_dot > 1)
            return 0;
        if (str[i] == '.')
            count_dot++;
        if (!isdigit(str[i]) && str[i] != '.')
            return 0;
    }
    return 1;
}

double toNumber(char *str)
{
    int sign = 1;
    int number = 0;
    int flag = 0;
    int power = 0;

    if (*str == '-') {
        sign = -1;
        str++;
    } else if (*str == '+')
        str++;
    
    while (*str != '\0') {
        if (flag)
            power++;
        if (*str == '.') {
            str++;
            flag = 1;
        }
        else {
            number = number * 10 + (*str - '0');
            str++;
        }
    }

    return number / pow(10, power) * sign;
}

int validArgc(int argc, char* argv[])
{
    if (argc == 5 && (argv[1][0] == '-' || argv[1][0] == '/')) {
        if (argv[1][1] == 'q' && is_digit(argv[2]) && is_digit(argv[3]) && is_digit(argv[4]))
            return 1;
        else if (argv[1][1] == 't' && is_digit(argv[2]) && is_digit(argv[3]) && is_digit(argv[4])
        && toNumber(argv[2]) != 0.0 && toNumber(argv[3]) != 0.0 && toNumber(argv[4]) != 0.0)
            return 1;
    }
    else if (argc == 4 && (argv[1][0] == '-' || argv[1][0] == '/') && argv[1][1] == 'm' && is_digit(argv[2]) && is_digit(argv[3])
        && toNumber(argv[2]) != 0.0 && toNumber(argv[3]) != 0.0)
            return 1;
    
    return 0;
}

void quadraticEquation(double num1, double num2, double num3)
{
    double a = num1, b = num2, c = num3;
    double D = sqrt(b * b - 4 * a * c);
    printf("For a=%f b=%lf c=%f:\n", a, b, c);
    if (D > EPS)
        printf("x1 = %f; x2 = %f\n\n", ((-b - D) / (2 * a)), ((-b + D) / (2 * a)));
    else if (D == 0.0)
        printf("x = %f\n\n", ((-b) / (2 * a))); 
    else
        printf("The equation has no roots\n\n");

    a = num1, b = num3, c = num2;
    D = sqrt(b * b - 4 * a * c);
    printf("For a=%f b=%lf c=%f:\n", a, b, c);
    if (D > EPS)
        printf("x1 = %f; x2 = %f\n\n", ((-b - D) / (2 * a)), ((-b + D) / (2 * a)));
    else if (D == 0.0)
        printf("x = %f\n\n", ((-b) / (2 * a))); 
    else
        printf("The equation has no roots\n\n");

    a = num2, b = num1, c = num1;
    D = sqrt(b * b - 4 * a * c);
    printf("For a=%f b=%lf c=%f:\n", a, b, c);
    if (D > EPS)
        printf("x1 = %f; x2 = %f\n\n", ((-b - D) / (2 * a)), ((-b + D) / (2 * a)));
    else if (D == 0.0)
        printf("x = %f\n\n", ((-b) / (2 * a))); 
    else
        printf("The equation has no roots\n\n");

    a = num2, b = num3, c = num2;
    D = sqrt(b * b - 4 * a * c);
    printf("For a=%f b=%lf c=%f:\n", a, b, c);
    if (D > EPS)
        printf("x1 = %f; x2 = %f\n\n", ((-b - D) / (2 * a)), ((-b + D) / (2 * a)));
    else if (D == 0.0)
        printf("x = %f\n\n", ((-b) / (2 * a))); 
    else
        printf("The equation has no roots\n\n");

    a = num3, b = num1, c = num2;
    D = sqrt(b * b - 4 * a * c);
    printf("For a=%f b=%lf c=%f:\n", a, b, c);
    if (D > EPS)
        printf("x1 = %f; x2 = %f\n\n", ((-b - D) / (2 * a)), ((-b + D) / (2 * a)));
    else if (D == 0.0)
        printf("x = %f\n\n", ((-b) / (2 * a))); 
    else
        printf("The equation has no roots\n\n");

    a = num3, b = num2, c = num1;
    D = sqrt(b * b - 4 * a * c);
    printf("For a=%f b=%lf c=%f:\n", a, b, c);
    if (D > EPS)
        printf("x1 = %f; x2 = %f\n\n", ((-b - D) / (2 * a)), ((-b + D) / (2 * a)));
    else if (D == 0.0)
        printf("x = %f\n\n", ((-b) / (2 * a))); 
    else
        printf("The equation has no roots\n\n");
}

int checkMultiples(double num1, double num2)
{
    int first = (int)num1, second = (int)num2;
    if (first != 0 && second != 0)
        if (first % second == 0)
            return 1;
    return 0;
}

int checkTriangle(double num1, double num2, double num3)
{   
    if (num1 > EPS && num2 > EPS && num3 > EPS) 
        if (num1 + num2 > num3 && num1 + num3 > num2 && num2 + num3 > num1)
            return 1;
    return 0;
}

int main(int argc, char *argv[])
{
    if (validArgc(argc, argv)) {
        double num1 = toNumber(argv[2]);
        double num2 = toNumber(argv[3]);
        double num3 = 0;
        if (argc == 5) 
            num3 = toNumber(argv[4]);
        char state = argv[1][1];
        switch (state) {
            case 'q':
                quadraticEquation(num1, num2, num3);
                break;
            case 'm':
                if (checkMultiples(num1, num2))
                    printf("The first number is a multiple of the second\n");
                else
                    printf("The first number isn't a multiple of the second\n");
                break;
            case 't':
                if (checkTriangle(num1, num2, num3))
                    printf("Entered numbers can be sides of triagle\n");
                else
                    printf("Entered numbers can't be sides of triangle\n");
                break;
        }
    }
    else
        printf("Incorrect arguments!\n");

    return 0;
}