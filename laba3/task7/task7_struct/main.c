#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "defs.h"
#include "str.h"
#include "valid.h"
#include "person.h"
#include "list.h"

void print_error(int error)
{
    switch (error)
    {
    case incorrect_arguments:
        printf("Incorrect_argumets!\n");
        break;
    case invalid_data:
        printf("Invalid data!\n");
        break;
    case no_memory:
        printf("Memory allocation error!\n");
        break;
    case file_isnt_open:
        printf("File is not open!\n");
        break;
    case runtime_error:
        printf("Runtime error!\n");
        break;
    case no_person:
        printf("Could not find a person with this information!\n");
        break;
    case empty_list:
        printf("List is empty!\n");
        break;
    }
}

int main(int argc, char *argv[])
{
    int error = success;
    ptr_list list = NULL;
    ptr_list find_node = NULL;
    char *filename = "output.txt";

    if (argc == 2)
    {
        char *path = argv[1];
        if ((error = get_list(&list, path)) == success)
        {
            
            if ((error = search_node(list, &find_node, "Ivanov", "Ivan", "Ivanovich", "23.09.2004", male, 23000.45)) == success)
                print_person(find_node->person, stdout);
            else
                print_error(error);
            
            if ((error = delete_person(&list, "Abramova", "Ivan", "Ivanovich", "23.09.2005", female, 2303535.45)) == success)
                printf("Person was deleted!\n");
            else 
                print_error(error);
            
            
            if ((error = add_person(&list, "Hasanov", "Daniil", "Rafailovich", "28.05.2003", "male", "25000.0")) == success)
                printf("Person was added!\n");
            else
                print_error(error);
            
            if ((error = list_in_file(list, filename)) == success)
                printf("Information uploaded in file!\n");
            else
                print_error(error);
        }
        else
            print_error(error);
    }
    else
    {
        error = incorrect_arguments;
        print_error(error);
    }

    if (list)
        free_list(list);
    return 0;
}
