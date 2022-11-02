#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

enum ERRORS{
    success = 0,
    incorrect_arguments = -1,
    invalid_message = -2,
    no_memory = -3,
    file_isnt_open = -4,
    runtime_error = -5
};

typedef struct message {
    int id;
    char *text;
    int length;
} message, *ptr_message;

void print_error(int error)
{
    switch (error) {
        case incorrect_arguments:
            printf("Incorrect_argumets!\n");
            break;
        case invalid_message:
            printf("Invalid_message, attempts are over!\n");
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

int valid (char *text) {
    for (int i = 0; text[i] != '\0'; i++)
        if (text[i] == ',' || text[i] == ';' || text[i] == '"')
            return 0;
    return 1;
}

int generateFileName(char **file_name)
{
    srand(time(NULL));
    int digit = 0;
    int upper = 0;
    int length = (rand() % 8) + 1;

    *file_name = (char*)malloc(sizeof(char) * (length + 1));
    if (!(*file_name))
        return no_memory;

    (*file_name)[length] = '\0';

    for (int i = 0; i < length; i++) {
        if (digit = rand() % 2)
            (*file_name)[i] = (rand() % 10) + '0';
        else {
            if (upper = rand() % 2)
                (*file_name)[i] = (rand() % 26) + 'A';
            else
                (*file_name)[i] = (rand() % 26) + 'a';
        }
    }
    strcat((*file_name), ".csv");

    return success;
}

int get_text(char **string)
{
    char symbol;
    int count = 2;
    int cur_pos = 0;
    char *tmp = NULL;

    (*string) = (char*)malloc(sizeof(char) * count);
    if (!(*string)) {
        return no_memory;
    }

    while ((symbol = getchar()) != '\n') {
        if (cur_pos >= count) {
            count *= 2;

            if (!(tmp = (char*)realloc((*string), sizeof(char) * count))) {
                free((*string));
                *string = NULL;
                return no_memory;
            }
            else
                *string = tmp;
        }
        (*string)[cur_pos++] = symbol;
    }
    (*string)[cur_pos] = '\0';

    return success;
}

int text_in_file(char *filename, char *stop_word, int *count)
{
    if (!filename || !stop_word)
        return runtime_error;

    int error = success;
    int index = 1;
    int length = 0;
    int trys = 3;
    char *string = NULL;

    ptr_message messages = (ptr_message)malloc(sizeof(message));
    if (!messages)
        return no_memory;

    FILE *fin = fopen(filename, "w");
    if (!fin)
        return file_isnt_open;

    while (1) {
        printf("Enter your message: ");

        if ((error = get_text(&string)) == success) {
            if (valid(string)) {
                trys = 3;

                if (!strcmp(string, stop_word)) {
                    free(string);
                    string = NULL;
                    break;
                }

                length = strlen(string);
                messages->id = index++;
                messages->text = (char*)malloc(sizeof(char) * (length + 1));
                strcpy(messages->text, string);
                messages->length = length;
                fprintf(fin, "%d,%s,%d\n", messages->id, messages->text, messages->length);
                (*count)++;
            }
            else {
                if (trys == 0) 
                    return invalid_message;

                printf("Incorrect message, %d trys left, please try again.\n", trys--);
            }
            if (string) {
                free(string);
                string = NULL;
            }
            if (messages->text) {
                free(messages->text);
                messages->text = NULL;
            }
        }
        else 
            return error;
    }

    fclose(fin);
    free(messages);

    return success;
}

int get_data_from_file(FILE *fin, char **data)
{
    int count = 2;
    int cur_pos = 0;
    char *tmp = NULL;

    (*data) = (char*)malloc(sizeof(char) * count);
    if (!(*data)) 
        return no_memory;

    char symbol = fgetc(fin);

    while (symbol != '\n' && symbol != ',') {
        if (cur_pos >= count) {
            count *= 2;

            if (!(tmp = (char*)realloc((*data), sizeof(char) * count))) {
                free((*data));
                *data = NULL;
                return no_memory;
            }
            else
                *data = tmp;
        }

        (*data)[cur_pos++] = symbol;
        symbol = fgetc(fin);
    }
    (*data)[cur_pos] = '\0';
    
    return success;
}

int from_file_to_array(char *filename, int count_messages, message ***messages)
{
    if (!filename || count_messages < 0)
        return runtime_error;

    int error = success;
    char *data = NULL;

    FILE *fin = fopen(filename, "r");
    if (!fin)
        return file_isnt_open;
    
    *messages = (message**)malloc(sizeof(ptr_message) * count_messages);
    if (!(*messages))
        return no_memory;

    for (int i = 0; i < count_messages; i++) {
        (*messages)[i] = (ptr_message)malloc(sizeof(message));
        if (!((*messages)[i]))
            return no_memory;

        if ((error = get_data_from_file(fin, &data)) == success) {
            (*messages)[i]->id = atoi(data);
            free(data);
            data = NULL;
        }
        else
            return error;

        if ((error = get_data_from_file(fin, &data)) == success) {
            (*messages)[i]->text = (char*)malloc(sizeof(char) * (strlen(data) + 1));
            if (!((*messages)[i]->text))
                return no_memory;
            strcpy((*messages)[i]->text, data);
            free(data);
            data = NULL;
        }
        else
            return error;

        if ((error = get_data_from_file(fin, &data)) == success) {
            (*messages)[i]->length = atoi(data);
            free(data);
            data = NULL;
        }
        else
            return error;
    }
    
    fclose(fin);
    return success;
}

void print_array(message **messages, int count_messages)
{
    for (int i = 0; i < count_messages; i++) 
        printf("id:%d text:%s length:%d\n", messages[i]->id, messages[i]->text, messages[i]->length);
}

void free_array(message **messages, int count_messages)
{
    for (int i = 0; i < count_messages; i++) {
        if (messages[i]->text)
            free(messages[i]->text);
        if (messages[i])
            free(messages[i]);
    }
    if (messages)
        free(messages);
}

int main(int argc, char *argv[])
{
    int error = success;
    char *file_name = NULL;
    message **messages = NULL;
    int count_messages = 0;

    if (argc == 2) {
        char *stop_word = argv[1];
        if ((error = generateFileName(&file_name)) == success) {
            if ((error = text_in_file(file_name, stop_word, &count_messages)) == success) {
                if ((error = from_file_to_array(file_name, count_messages, &messages)) == success) {
                    print_array(messages, count_messages);
                }
                else 
                    print_error(error);
            }
            else
                print_error(error);
        }
        else 
            print_error(error);
    }
    else {
        error = incorrect_arguments;
        print_error(error);
    }
    if (file_name) {
        free(file_name);
        file_name = NULL;
    }
    free_array(messages, count_messages);

    return 0;
}