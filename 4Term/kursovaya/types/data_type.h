#ifndef DATA_TYPE_H
#define DATA_TYPE_H

#include <iostream>

struct key
{
    unsigned int _id_session;
    unsigned int _id_student;
    std::string _format;
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
