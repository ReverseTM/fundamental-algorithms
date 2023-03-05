#include <iostream>
#include "logger_implementation.h"
#include "json_implementation.h"

int main()
{
    builder *logger_builder = new builder_implementation();

    logger *logger1 = logger_builder
            ->add_stream("file1.txt", logger::severity::information)
            ->add_stream("file2.txt", logger::severity::warning)
            ->build();


    json *logger_json = new json_implementation("../config.json");

    logger *logger2 = logger_json->create();

    logger1->log("Hello", logger::severity::trace);
    logger1->log("everyone", logger::severity::warning);
    logger2->log("hey", logger::severity::trace);
    logger2->log("123", logger::severity::information);

    delete logger1;
    delete logger2;
    delete logger_json;
    delete logger_builder;

    return 0;
}