#ifndef PERSON_H
#define PERSON_H

#include "defs.h"

int compare(ptr_residents person1, ptr_residents person2);
void free_person(ptr_residents person);
int delete_person(list **root, char *surname, char *name, char *patronymic, char *dob, enum GENDER gender, double aimp);
void print_person(ptr_residents person, FILE *output);
int add_person(list **root, char *surname, char *name, char *patronymic, char *dob, char *gender, char *aimp);
int get_data(char *string, residents **person);

#endif // PERSON_H