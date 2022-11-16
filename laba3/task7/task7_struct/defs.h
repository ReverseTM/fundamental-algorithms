#ifndef ENUM_H
#define ENUM_H

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

#endif // ENUM_H