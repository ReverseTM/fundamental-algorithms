#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

typedef struct list
{
    char *file;
    int *index;
    struct list *next;
} list;

list *create_node(char *file_name, int *data, int count)
{
    list *node = (list*)malloc(sizeof(list));
    if (!node)
        return NULL;

    node->file = (char*)malloc(sizeof(char) * strlen(file_name) + 1);
    if (!node->file) {
        return node;
    }
    strcpy(node->file, file_name);

    node->index = (int*)malloc(sizeof(int) * count);
    if (!node->index) {
        free(node->file);
        return node;
    }
    for (int i = 0; i < count; i++)
        node->index[i] = data[i];
    
    node->next = NULL;

    return node;
}

list *add_node(list *node, char *file_name, int *data, int count)
{
    list *tmp = (list*)malloc(sizeof(list));
    if (!tmp)
        return NULL;

    tmp->file = (char*)malloc(sizeof(char) * strlen(file_name) + 1);
    if (!tmp->file) {
        return node;
    }
    strcpy(tmp->file, file_name);

    tmp->index = (int*)malloc(sizeof(int) * count);
    if (!tmp->index) {
        free(tmp->file);
        return node;
    }
    for (int i = 0; i < count; i++)
        tmp->index[i] = data[i];
    
    tmp->next = NULL;

    list *p = node;
    while(p->next != NULL)
        p = p->next;
    p->next = tmp;

    return node;
}

void print(list* node, char *substring)
{
    while (node) {
        printf("In file %s the substring '%s' was found from indices: ", node->file, substring);
        for (int i = 0; i < sizeof(node->index) / sizeof(node->index[0]); i++)
            printf("%d ", node->index[i]);
        printf("\n");
            
        node = node->next;
    }
}

void free_list(list *node)
{
    list *tmp = NULL;

    while (node) {
        tmp = node;
        node = node->next;

        if (tmp->file) 
            free(tmp->file);
        if (tmp->index) 
            free(tmp->index);

        free(tmp);

    }
}

list *find_substring(list *finds, char* substring, char *file_name)
{
    FILE *fin;

    if (!(fin = fopen(file_name, "r"))) {
        free_list(finds);
        return NULL;
    }

    char symbol;
    int index = 0;
    int tmp_index = 0;
    int gipotiza = 0;
    int sovpalo = 0;
    int success = 0;
    int count = 0;
    int *data = NULL;
    int *tmp = NULL;
    list *tmp_list = NULL;

    while ((symbol = fgetc(fin)) != EOF) {

        if (symbol == substring[0] && !gipotiza) {
            tmp_index = index;
            sovpalo = 1;
            gipotiza = 1;
        }

        if (gipotiza) {
            for (int i = 1; i < strlen(substring); i++) {
                if ((symbol = fgetc(fin)) != EOF) {
                    if (symbol != substring[i]) {
                        index = tmp_index;
                        fseek(fin, index + 1, SEEK_SET);
                        sovpalo = 0;
                        break;
                    }
                    else
                        index++;
                }
                else
                    break;
            }
            if (sovpalo) {
                success = 1;
                count++;
                if (!(tmp = (int*)realloc(data, sizeof(int) * count))) {
                    free(data);
                    free_list(finds);
                    return NULL;
                }
                data = tmp;
                data[count - 1] = tmp_index;
            }
            gipotiza = 0;
        }
        index++;
    }
    fclose(fin);

    if (success) {
        if (!finds) {
            if (tmp_list = create_node(file_name, data, count))
                finds = tmp_list;
            else {
                free(data);
                return finds;
            }
        }
        else {
            if (tmp_list = add_node(finds, file_name, data, count))
                finds = tmp_list;
            else {
                free(data);
                return finds;
            }
        }
    }

    if (data)
        free(data);

    return finds;
}

list *file_crawling(int count, char* substring, ...)
{   
    list *finds = NULL;
    list *tmp = NULL;
    
    va_list iter;
    va_start(iter, substring);
    
    for (int i = 0; i < count; i++) {
        if (tmp = find_substring(finds, substring, va_arg(iter, char*)))
            finds = tmp;
        else if (!tmp && i == count - 1) {
            va_end(iter);
            return finds;
        }
    }

    va_end(iter);

    return finds;
}

int main(int argc, char *argv[])
{
    char *substring = "abc";

    list *finds = file_crawling(3, substring, "file1.txt", "file3.txt", "file2.txt");

    if (!finds)
        printf("List does not exist!\n");
    else {
        print(finds, substring);
        free_list(finds);
    }

    return 0;
}