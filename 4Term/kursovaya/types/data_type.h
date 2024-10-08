#ifndef DATA_TYPE_H
#define DATA_TYPE_H

#include <iostream>

enum form
{
    COURSE_WORK,
    EXAM,
    TEST
};

struct key
{
    unsigned int _id_session;
    unsigned int _id_student;
    form _format;
    std::string _subject;
};

struct value
{
    std::string _surname;
    std::string _name;
    std::string _patronymic;
    std::string _date;
    std::string _time;
    unsigned int _mark;
};


#endif //DATA_TYPE_H
