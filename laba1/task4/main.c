#include <stdio.h>
#include <stdlib.h>
#include <time.h>

enum ERRORS
{
    success = 0,
    incorrect_arguments = -1,
    invalid_data = -2,
    no_memory = -3,
    file_isnt_open = -4,
    runtime_error = -5
};

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
    }
}

int strLen(const char *string)
{
    if (!string)
        return 0;
    int count = 0;
    while (*string++ != '\0') count++;
    return count;
}

char *strCat(char *dest, const char *src)
{
    if (!dest || !src)
        return NULL;
    char *tmp = NULL;
    if  (!(tmp = (char*)realloc(dest ,sizeof(char) * (strLen(dest) + strLen(src) + 1))))
        return NULL;
    dest = tmp;
    char *ptr = dest + strLen(dest);    
    while (*ptr++ = *src++);

    return dest;
}

void strCopy(char *dest, const char *src)
{
    if (!dest || !src)
        return;
    while (*dest++ = *src++);
}

int strCmp(const char* s1, const char* s2)
{
    while(*s1 && (*s1 == *s2))
    {
        s1++;
        s2++;
    }
    return *(const unsigned char*)s1 - *(const unsigned char*)s2;
}

char *strToken(char *string, const char *delim)
{
    static char *data;
    if (string) {
        data = string;
        while (*data && *data == *delim)
            *data++ = '\0';
    }
    if (!*data)
        return NULL;
    string = data;
    while (*data && *data != *delim && *data != '\0')
        data++;
    while (*data && *data == *delim)
        *data++ = '\0';
    return string;
}

int get_string(FILE *fin, char **string)
{
    if (!fin)
        return invalid_data;
    int count = 2;
    int cur_pos = 0;
    char *tmp = NULL;

    (*string) = (char *)malloc(sizeof(char) * count);
    if (!(*string))
    {
        return no_memory;
    }

    char symbol = fgetc(fin);
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
        symbol = fgetc(fin);
    }
    (*string)[cur_pos] = '\0';

    return success;
}

void freeStringArray(char **array, int size)
{
    if (array) {
        for (int i = 0; i < size; i++) {
            if (array[i]) {
                free(array[i]);
                array[i] = NULL;
            }
        }
        free(array);
        array = NULL;
    }
}

int transform(FILE *fout, char *string)
{
    if (!fout || !string)
        return invalid_data;
    char **string_array = (char**)malloc(sizeof(char*) * 3);
    if (!string_array)
        return no_memory;
    int i = 0;
    for (char *tmp = strToken(string, " "); tmp; tmp = strToken(NULL, " ")) {
        string_array[i] = (char*)malloc(sizeof(char) * (strLen(tmp) + 1));
        if (!string_array[i]) {
            freeStringArray(string_array, 3);
            return no_memory;
        }
        strCopy(string_array[i++], tmp);
    }
    fprintf(fout, "%s ", string_array[2]);
    fprintf(fout, "%s ", string_array[0]);
    fprintf(fout, "%s\n", string_array[1]);

    freeStringArray(string_array, 3);

    return success;
}

int generateFileName(char **filename)
{
    srand((unsigned)time(NULL));
    int digit = 0;
    int upper = 0;
    int length = (rand() % 8) + 1;

    *filename = (char*)malloc(sizeof(char) * (length + 1));
    if (!(*filename))
        return no_memory;

    (*filename)[length] = '\0';

    for (int i = 0; i < length; i++) {
        if (digit = rand() % 2)
            (*filename)[i] = (rand() % 10) + '0';
        else {
            if (upper = rand() % 2)
                (*filename)[i] = (rand() % 26) + 'A';
            else
                (*filename)[i] = (rand() % 26) + 'a';
        }
    }
    printf("%s\n", *filename);
    strCat((*filename), ".txt");

    return success;
}

int main(int argc, char *argv[])
{
    int error = 0;
    if (argc == 2 && !strCmp((argv[1] + strLen(argv[1]) - 4), ".txt")) {
        FILE *fin = fopen(argv[1], "r");
        if (!fin) {
            error = file_isnt_open;
            print_error(error);
            return 0;
        }
            
        char *filename = NULL;
        if ((error = generateFileName(&filename)) == success) {
            if (strCmp(argv[1], filename)) { 
                FILE *fout = fopen(filename, "w");
                if (!fout) {
                    free(filename);
                    filename = NULL;
                    fclose(fin);
                    error = file_isnt_open;
                    print_error(error);
                    return 0;
                }
                char *string = NULL;

                while (!feof(fin)) {
                    if ((error = get_string(fin, &string)) == success) {
                        if (strLen(string) == 0) {
                            free(string);
                            string = NULL;
                            continue;
                        }
                        if ((error = transform(fout, string)) == success) {
                            free(string);
                            string = NULL;
                        }
                        else {
                            print_error(error);
                            break;
                        }
                    }
                    else {
                        print_error(error);
                        break;
                    }
                }
                fclose(fout);
            }
            else {
                error = runtime_error;
                print_error(error); 
            }
        }
        else
            print_error(error);

        free(filename);
        filename = NULL;
        fclose(fin);
    }
    else {
        error = incorrect_arguments;
        print_error(error);
    }

    return 0;
}