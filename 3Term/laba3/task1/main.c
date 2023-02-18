#include <stdio.h>
#include <stdlib.h>

int sum(int a, int b)
{
    int carry	= 0;

	while(b)
	{
		carry	= (a & b);
		a	= a ^ b;
		b	= (carry << 1);
    }
    return a;
}

int sub(int a, int b)
{
    int borrow	= 0;

	while(b)
	{
		borrow = ((~a) & b);
		a = a ^ b;
		b = (borrow << 1);
	}
    return a;
}

char *transform(int number, int r, int *error)
{
    if (r < 1 || r > 5)
    {
        *error = -1;
        return NULL;
    }

    int sign = 0;
    if (number < 0)
    {
        number = sum(~number, 1);
        sign = 1;
    }

    int count = 0;
    int tmp_number = number;
    while (tmp_number) {
        count = sum(count, 1);
        tmp_number >>= r;
    }

    char *result = NULL;

    if (sign) {
        count = sum(count, 1);
        result = (char*)malloc(sizeof(char) * sum(count, 1));
        if (!result) {
            *error = -2;
            return NULL;
        }
        result[count] = '\0';
        result[0] = '-'; 
    }
    else {
        result = (char*)malloc(sizeof(char) * sum(count, 1));
        if (!result) {
            *error = -2;
            return NULL;
        }
        result[count] = '\0';
    }
    
    int remainder = 0;
    while (number) {
        remainder = number & sub((1 << r), 1);
        count = sub(count, 1);
        result[count] = remainder < 10 ? (sum(remainder, '0')) : (sub(sum(remainder, 'A'), 10));
        number = number >> r;
    }

    return result;
}

int main()
{
    char *result = NULL;
    int number = 0;
    int r = 0;
    int error = 0;

    printf("Enter number: ");
    if (scanf("%d", &number) != 1) {
        error = -1;
        printf("Not integer. ");
    }
    else
    {
        printf("Enter degree of 2: ");
        if (scanf("%d", &r) != 1) {
            error = -1;
            printf("Not integer. ");
        }
        else
            result = transform(number, r, &error);
    }
    switch (error)
    {
    case 0:
        printf("A %d in the %d number system has the following representation: ", number, 1 << r);
        printf("%s\n", result);
        if (result)
            free(result);
        break;
    case -1:
        printf("Incorrect input!\n");
        break;
    case -2:
        printf("Memory allocation error!\n");
        break;
    }

    return 0;
}
