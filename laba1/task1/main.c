#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

void printMultiples(int number)
{
    int count = 0;
    int digit = 1;
    int result = 0;
    if (number > 0) {
        while ((result = digit * number) <= 100) {
            printf("%d ", result);
            digit++;
            count++;
        }
    }
    if (count == 0) {
        printf("There are no multiples of %d within 100\n", number);
        return;
    }
    printf("\n");

}

int isprime(int number)
{
    if (number > 1) {
        for (int i = 2; i <= (int)sqrt(number); i++)
            if (number % i == 0)
                return 0;
        return 1;
    }
    else
        return 0;
}

void printNumber(int number, int length)
{   
    if (number > 0) {
        int reverse_number = 0;
        while (number) {
            reverse_number = reverse_number * 10 + (number % 10);
            number /= 10;
        }
        while (reverse_number) {
            printf("%d ", reverse_number % 10);
            reverse_number /= 10;
        }
        printf("\n");
    }
    else printf("%d\n", 0);
}

int printPower(int number)
{
    if (number > 0 && number <= 10) {
        for (int i = 1; i <= 10; i++) {
            for (int j = 1; j <= number; j++)
                printf("%d^%d=%d ",i, j, (int)pow(i, j));
            printf("\n");
        }
    }
    else
        return -1;
}

int summator(int number)
{
    if (number > 0) {
        return number * (number + 1) / 2;
    }
    else
        return -1;
}

int factorial(int n)
{
    return (n < 2) ? 1 : n * factorial(n - 1);
}

int is_digit(char *str)
{
    if (strlen(str) && (str[0] == '+' || str[0] == '-'))
        str++;
    for (int i = 0; str[i] != '\0'; i++)
        if (!isdigit(str[i]))
            return 0;
    return 1;
}

int _atoi(char *str)
{
    int sign = 1;
    int number = 0;

    if (*str == '-') {
        sign = -1;
        str++;
    } else if (*str == '+')
        str++;
    
    while (*str != '\0') {
        number = number * 10 + (*str - '0');
        str++;
    }

    return number * sign;
}

int main(int argc, char*argv[])
{
    if ((argc == 3)
        && (is_digit(argv[1]))
        && (strlen(argv[2]) == 2)
        && (argv[2][0] == '-' || argv[2][0] == '/')
        && (argv[2][1] == 'h' || argv[2][1] == 'p' || argv[2][1] == 's' || argv[2][1] == 'e' || argv[2][1] == 'a' || argv[2][1] == 'f'))
    {
        int number = _atoi(argv[1]);
        if (number > 0) {
            int length = strlen(argv[1]);
            char state = argv[2][1];

            switch (state) {
                case 'h':
                    printMultiples(number);
                    break;
                case 'p':
                    if (isprime(number))
                        printf("%d is a prime!\n", number);
                    else {
                        if (number == 1)
                            printf("%d the number 1 is neither a prime nor a composite number\n", number);
                        else
                            printf("%d is a composite number!\n", number);
                    }
                    break;
                case 's':
                    printNumber(number, length);
                    break;
                case 'e':
                    if (printPower(number) == -1) 
                        printf("Number must be > 0 and <= 10\n");
                    break;
                case 'a':
                    int result = summator(number);
                    if (result == -1)
                        printf("Number must be more then 0!\n");
                    else
                        printf("Sum numbers 1 to %d = %d\n", number, result);
                    break;
                case 'f':
                    printf("Factorial of %d = %d\n", number, factorial(number));
                    break;
            }
        }
        else
            printf("Number must be more then 0\n");
    }
    else 
        printf("Invalid arguments!\n");
    
    return 0;
}