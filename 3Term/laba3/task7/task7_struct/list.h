#ifndef LIST_H
#define LIST_H

#include "defs.h"

int add_node(list **root, ptr_residents data, int(*compare)(ptr_residents, ptr_residents));
void del_node(list **root, ptr_list node);
int search_node(ptr_list root, list **node, char *surname, char *name, char *patronymic, char *dob, enum GENDER gender, double aimp);
void print_list(ptr_list list, FILE *output);
void free_list(ptr_list list);
int get_list(list **list, char *path);
int list_in_file(ptr_list root, char *filename);

#endif // LIST_H