#include <iostream>
#include "logger_implementation.h"
#include "json_implementation.h"

int main()
{
    Builder *logger_builder = new Builder_implementation();

    Logger *logger1 = logger_builder
            ->add_stream("file1.txt", Logger::severity::information)
            ->add_stream("file2.txt", Logger::severity::warning)
            ->build();


    Json *logger_json = new Json_implementation("../config.json");

    Logger *logger2 = logger_json->create();

    logger1->log("Hello", Logger::severity::trace);
    logger1->log("everyone", Logger::severity::warning);
    logger2->log("hey", Logger::severity::trace);
    logger2->log("123", Logger::severity::information);

    delete logger1;
    delete logger2;
    delete logger_json;
    delete logger_builder;

    return 0;
}