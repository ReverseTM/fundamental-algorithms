#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "defs.h"
#include "str.h"
#include "person.h"
#include "valid.h"
#include "list.h"

int compare(ptr_residents person1, ptr_residents person2)
{
    if (!person1 || !person2)
        return runtime_error;

    int error = 0;

    char *reverse_date1 = NULL;
    char *reverse_date2 = NULL;

    if ((error = reverse_date(person1->dob, &reverse_date1)) != success || (error = reverse_date(person2->dob, &reverse_date2)) != success)
        return error;

    int cmp = strcmp(reverse_date1, reverse_date2);
    
    free(reverse_date1);
    free(reverse_date2);

    return cmp;
}

void free_person(ptr_residents person)
{
    if (person)
    {
        if (person->surname)
            free(person->surname);
        if (person->name)
            free(person->name);
        if (person->patronymic)
            free(person->patronymic);
        if (person->dob)
            free(person->dob);
        free(person);
    }
}

int delete_person(list **root, char *surname, char *name, char *patronymic, char *dob, enum GENDER gender, double aimp)
{
    int error = success;

    ptr_list node = NULL;

    if ((error = search_node(*root, &node, surname, name, patronymic, dob, gender, aimp)) == success) {
        del_node(root, node);
        return success;
    }
    else
        return error;

}

void print_person(ptr_residents person, FILE *output)
{
    if (!person)
        return;
    fprintf(output, "%s %s %s %s ", person->surname, person->name, person->patronymic, person->dob);
    if (person->gender == male)
        fprintf(output, "male ");
    else
        fprintf(output, "female ");
    fprintf(output, "%.2f\n", person->aipm);
}

int add_person(list **root, char *surname, char *name, char *patronymic, char *dob, char *gender, char *aimp)
{
    int (*validators[])(char* value) = {
        fullnameValid,
        dateofbirthValid,
        genderValid,
        aimpValid
    };

    if (validators[fullname](surname) && validators[fullname](name) && validators[fullname](patronymic) && validators[birthday](dob)
    && validators[money](aimp)) {
        ptr_residents person = (ptr_residents)malloc(sizeof(residents));
        if (!person)
            return no_memory;
        
        person->surname = (char*)malloc(sizeof(char) * (strlen(surname) + 1));
        if (!person->surname) {
            free(person);
            return no_memory;
        }

        person->name = (char*)malloc(sizeof(char) * (strlen(name) + 1));
        if (!person->surname) {
            free(person->surname);
            free(person);
            return no_memory;
        }

        person->patronymic = (char*)malloc(sizeof(char) * (strlen(patronymic) + 1));
        if (!person->surname) {
            free(person->surname);
            free(person->name);
            free(person);
            return no_memory;
        }

        person->dob = (char*)malloc(sizeof(char) * (strlen(dob) + 1));
        if (!person->surname) {
            free(person->surname);
            free(person->name);
            free(person->patronymic);
            free(person);
            return no_memory;
        }

        strcpy(person->surname, surname);
        strcpy(person->name, name);
        strcpy(person->patronymic, patronymic);
        strcpy(person->dob, dob);

        if (!strcmp(gender, "male"))
            person->gender = male;
        else
            person->gender = female;

        person->aipm = atof(aimp);

        int error = 0;

        if ((error = add_node(root, person, compare)) == success)
            return success;
        else
            return error;
    }
    else {
        return invalid_data;
    }
}

int get_data(char *string, residents **person)
{
    if (!string)
        return runtime_error;

    (*person) = (ptr_residents)malloc(sizeof(residents));

    int length = strlen(string);
    int count = 0;
    int error = 0;
    int size = 0;
    int index = 1;
    char *ptr = string;
    char *str = NULL;

    int (*validators[])(char *value) = {
        fullnameValid,
        dateofbirthValid,
        genderValid,
        aimpValid
    };

    while (count != length + 1)
    {
        if (*ptr == ' ' || *ptr == '\0')
        {
            size = 0;
            switch (index)
            {
            case 1:
                if (validators[fullname](str))
                {
                    (*person)->surname = (char *)malloc(sizeof(char) * (strlen(str) + 1));
                    if (!((*person)->surname))
                    {
                        free(str);
                        str = NULL;
                        return no_memory;
                    }
                    strcpy((*person)->surname, str);
                    break;
                }
                else
                {
                    return invalid_data;
                }
            case 2:
                if (validators[fullname](str))
                {
                    (*person)->name = (char *)malloc(sizeof(char) * (strlen(str) + 1));
                    if (!((*person)->name))
                    {
                        free(str);
                        str = NULL;
                        return no_memory;
                    }
                    strcpy((*person)->name, str);
                    break;
                }
                else
                {
                    return invalid_data;
                }
            case 3:
                if (validators[fullname](str))
                {
                    (*person)->patronymic = (char *)malloc(sizeof(char) * (strlen(str) + 1));
                    if (!((*person)->patronymic))
                    {
                        free(str);
                        str = NULL;
                        return no_memory;
                    }
                    strcpy((*person)->patronymic, str);
                    break;
                }
                else
                {
                    return invalid_data;
                }
            case 4:
                if (validators[birthday](str))
                {
                    (*person)->dob = (char *)malloc(sizeof(char) * (strlen(str) + 1));
                    if (!((*person)->dob))
                    {
                        free(str);
                        str = NULL;
                        return no_memory;
                    }
                    strcpy((*person)->dob, str);
                    break;
                }
                else
                {
                    return invalid_data;
                }
            case 5:
                if (validators[sex](str))
                {
                    if (!strcmp(str, "male"))
                        (*person)->gender = male;
                    else
                        (*person)->gender = female;
                    break;
                }
                else
                {
                    return invalid_data;
                }
            case 6:
                if (validators[money](str))
                {
                    (*person)->aipm = atof(str);
                    break;
                }
                else
                {
                    return invalid_data;
                }
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
    return success;
}