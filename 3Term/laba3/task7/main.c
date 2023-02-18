#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define EPS 0.000000001

enum ERRORS
{
    success = 0,
    incorrect_arguments = -1,
    invalid_data = -2,
    no_memory = -3,
    file_isnt_open = -4,
    runtime_error = -5,
    no_person = -6,
    empty_list = -7
};

enum GENDER
{
    male = 0,
    female = 1
};

enum data_types
{
    fullname = 0,
    birthday = 1,
    sex = 2,
    money = 3
};

typedef struct residents
{
    char *name;
    char *surname;
    char *patronymic;
    char *dob; // date of birth
    enum GENDER gender;
    double aipm; // average income per month
} residents, *ptr_residents;

typedef struct list
{
    ptr_residents person;
    struct list *next;
} list, *ptr_list;

int add_symbol(char **string, char symbol, int *size)
{
    if (!(*string))
    {
        *size = 2;
        (*string) = (char *)malloc(sizeof(char) * (*size));
        if (!*string)
            return no_memory;
        (*string)[0] = symbol;
        (*string)[1] = '\0';

        return success;
    }

    int length = strlen(*string);
    char *tmp = NULL;

    if (length >= *size)
    {
        (*size) *= 2;

        if (!(tmp = (char *)realloc((*string), sizeof(char) * (*size))))
        {
            free((*string));
            *string = NULL;
            return no_memory;
        }
        else
            *string = tmp;
    }
    (*string)[length] = symbol;
    (*string)[length + 1] = '\0';

    return success;
}

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

int compare(ptr_residents person1, ptr_residents person2)
{
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

int get_string(FILE *fout, char **string)
{
    int count = 2;
    int cur_pos = 0;
    char *tmp = NULL;

    (*string) = (char *)malloc(sizeof(char) * count);
    if (!(*string))
    {
        return no_memory;
    }

    char symbol = fgetc(fout);
    while (symbol != '\n' && symbol != EOF)
    {
        if (cur_pos >= count)
        {
            count *= 2;

            if (!(tmp = (char *)realloc((*string), sizeof(char) * count)))
            {
                free((*string));
                *string = NULL;
                return no_memory;
            }
            else
                *string = tmp;
        }
        (*string)[cur_pos++] = symbol;
        symbol = fgetc(fout);
    }
    (*string)[cur_pos] = '\0';

    return success;
}

int get_data(char *string, residents **person)
{
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

int get_list(list **list, char *path)
{
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

int list_in_file(ptr_list root, char *filename)
{
    if (!root)
        return empty_list;
    
    FILE *file;
    if (!(file = fopen(filename, "w")))
        return file_isnt_open;
    
    print_list(root, file);
    fclose(file);
    return success;
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
