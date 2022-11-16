#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "valid.h"
#include "defs.h"
#include "str.h"

#define EPS 0.000000001

int fullnameValid(char *string)
{
    for (int i = 0; string[i] != '\0'; i++)
        if (!isalpha(string[i]))
            return 0;
    return 1;
}

int dateofbirthValid(char *string)
{
    int error = 0;
    char *ptr = string;
    char *day = NULL;
    char *month = NULL;
    char *year = NULL;
    char *str = NULL;
    int size = 0;
    int index = 1;
    int count = 0;
    int length = strlen(string);
    int length_day = 0;
    int length_month = 0;
    int length_year = 0;

    while (count != length + 1)
    {
        if (*ptr == '.' || *ptr == '\0')
        {
            size = 0;
            switch (index)
            {
            case 1:
                length_day = strlen(str);
                day = (char *)malloc(sizeof(char) * (length_day + 1));
                strcpy(day, str);
                break;
            case 2:
                length_month = strlen(str);
                month = (char *)malloc(sizeof(char) * (length_month + 1));
                strcpy(month, str);
                break;
            case 3:
                length_year = strlen(str);
                year = (char *)malloc(sizeof(char) * (length_year + 1));
                strcpy(year, str);
                break;
            }
            free(str);
            str = NULL;
            index++;
        }
        else
        {
            if ((error = add_symbol(&str, *ptr, &size)) != success)
                return error;
        }
        ptr++;
        count++;
    }

    if (length_day == 2 && atoi(day) >= 1 && atoi(day) <= 31)
    {
        for (int i = 0; day[i] != '\0'; i++)
            if (!isdigit(day[i]))
            {
                free(day);
                free(month);
                free(year);
                return 0;
            }
    }
    else
    {
        free(day);
        free(month);
        free(year);
        return 0;
    }

    if (length_month == 2 && atoi(month) >= 1 && atoi(month) <= 12)
    {
        for (int i = 0; month[i] != '\0'; i++)
            if (!isdigit(month[i]))
            {
                free(day);
                free(month);
                free(year);
                return 0;
            }
        if (atoi(month) == 2 && atoi(day) > 28)
        {
            free(day);
            free(month);
            free(year);
            return 0;
        }
    }
    else
    {
        free(day);
        free(month);
        free(year);
        return 0;
    }

    if (length_year != 4 || atoi(year) < 2000)
    {
        free(day);
        free(month);
        free(year);
        return 0;
    }
    
    free(day);
    free(month);
    free(year);

    return 1;
}

int genderValid(char *string)
{
    for (int i = 0; string[i] != '\0'; i++) {
        string[i] = tolower(string[i]);
    }
    if (strcmp(string, "male") && strcmp(string, "female"))
        return 0;
    return 1;
}

int aimpValid(char *string)
{
    int count_dot = 0;
    for (int i = 0; string[i] != '\0'; i++)
    {
        if (count_dot > 1)
            return 0;
        if (string[i] == '.')
            count_dot++;
        if (!isdigit(string[i]) && string[i] != '.')
            return 0;
    }
    if (atof(string) < EPS)
        return 0;
    return 1;
}

int reverse_date(char *string, char **reverse_res) 
{
    int error = 0;
    char *ptr = string;
    char *day = NULL;
    char *month = NULL;
    char *year = NULL;
    char *str = NULL;
    int size = 0;
    int index = 1;
    int count = 0;
    int length = strlen(string);
    int length_day = 0;
    int length_month = 0;
    int length_year = 0;

    while (count != length + 1)
    {
        if (*ptr == '.' || *ptr == '\0')
        {
            size = 0;
            switch (index)
            {
            case 1:
                length_day = strlen(str);
                day = (char *)malloc(sizeof(char) * (length_day + 1));
                strcpy(day, str);
                break;
            case 2:
                length_month = strlen(str);
                month = (char *)malloc(sizeof(char) * (length_month + 1));
                strcpy(month, str);
                break;
            case 3:
                length_year = strlen(str);
                year = (char *)malloc(sizeof(char) * (length_year + 1));
                strcpy(year, str);
                break;
            }
            free(str);
            str = NULL;
            index++;
        }
        else
        {
            if ((error = add_symbol(&str, *ptr, &size)) != success)
                return error;
        }
        ptr++;
        count++;
    } 

	*reverse_res = (char*)malloc(sizeof(char) * (length + 1));

	if (!*reverse_res) {
		return no_memory;
	}
    
    strcpy((*reverse_res), year);
    strcat((*reverse_res), month);
    strcat((*reverse_res), day);

    free(year);
    free(month);
    free(day);

    return success;
}