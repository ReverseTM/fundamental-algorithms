#ifndef DATA_H
#define DATA_H

#include <iostream>

struct key
{
    long _id_session;
    long _id_student;
    std::string _format;
    std::string _subject;
};

struct value
{
    std::string _surname;
    std::string _name;
    std::string _patronymic;
    std::string _data;
    std::string _time;
    unsigned int _mark;
};


#endif //DATA_H
