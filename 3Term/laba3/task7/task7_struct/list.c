#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "list.h"
#include "defs.h"
#include "str.h"
#include "person.h"

#define EPS 0.000000001

int add_node(list **root, ptr_residents data, int(*compare)(ptr_residents, ptr_residents))
{
    if (!(*root))
    {
        (*root) = (ptr_list)malloc(sizeof(list));
        if (!(*root))
            return no_memory;

        (*root)->person = data;
        (*root)->next = NULL;

        return success;
    }
    
    int cmp = 0;

    ptr_list p = (*root);
    ptr_list t = p;
    ptr_list tmp = (ptr_list)malloc(sizeof(list));
    if (!tmp)
        return no_memory;
    tmp->person = data;
    tmp->next = NULL;
    
    while(p != NULL && (cmp = compare(p->person, tmp->person)) >= 0) {
        t = p;
        p = p->next;
    }
    
    if (p == (*root) && cmp < 0) {
        tmp->next = (*root);
        (*root) = tmp;
    }
    else {
        tmp->next = t->next;
        t->next = tmp;
    }
    
    return success;
}

void del_node(list **root, ptr_list node)
{
    ptr_list tmp = (*root);

    if (node == (*root)) {
        (*root) = (*root)->next;
        free_person(tmp->person);
        free(tmp);
    }
    else {
        while (tmp->next != node)
            tmp = tmp->next;
        tmp->next = node->next;
        free_person(node->person);
        free(node);
    }
}

int search_node(ptr_list root, list **node, char *surname, char *name, char *patronymic, char *dob, enum GENDER gender, double aimp)
{
    if (!root)
        return empty_list;
    
    ptr_list ptr = root;

    while (ptr != NULL) {
        if (!strcmp(ptr->person->surname, surname) && !strcmp(ptr->person->name, name) && !strcmp(ptr->person->patronymic, patronymic) 
        && !strcmp(ptr->person->dob, dob) && ptr->person->gender == gender && fabs(ptr->person->aipm - aimp) < EPS) {
            (*node) = ptr;
            return success;
        }
        ptr = ptr->next;
    }

    return no_person;
}

void print_list(ptr_list list, FILE *output)
{
    while (list != NULL)
    {
        print_person(list->person, output);
        list = list->next;
    }
}

void free_list(ptr_list list)
{
    ptr_list tmp = NULL;

    while (list)
    {
        tmp = list;
        list = list->next;
        free_person(tmp->person);
        free(tmp);
    }
}

int get_list(list **list, char *path)
{
    if (!path)
        return runtime_error;

    int error = 0;

    FILE *fout;
    if (!(fout = fopen(path, "r")))
    {
        return file_isnt_open;
    }

    ptr_residents person = NULL;
    char *string = NULL;

    while (!feof(fout))
    {
        if ((error = get_string(fout, &string)) == success)
        {
            if ((error = get_data(string, &person)) == success)
            {
                if ((error = add_node(list, person, compare)) != success)
                {
                    if (*list)
                        free_list(*list);
                    else
                        free_person(person);
                    free(string);
                    string = NULL;
                    fclose(fout);
                    return error;
                }
            }
            else
            {
                free_person(person);
                free(string);
                string = NULL;
                fclose(fout);
                return error;
            }
        }
        else
        {
            free(string);
            string = NULL;
            fclose(fout);
            return error;
        }
        free(string);
        string = NULL;
    }

    fclose(fout);

    error = success;
    return error;
}

int list_in_file(ptr_list root, char *filename)
{
    if (!root)
        return empty_list;
    if (!filename)
        return runtime_error;

    FILE *file;
    if (!(file = fopen(filename, "w")))
        return file_isnt_open;
    
    print_list(root, file);
    fclose(file);
    return success;
}