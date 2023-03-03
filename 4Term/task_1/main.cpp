#include <iostream>
#include "logger_implementation.h"

int main()
{
    builder *logger_builder = new builder_implementation();

    logger *logger = logger_builder
    ->add_stream("file1.txt", logger::severity::trace)
    ->add_stream("file2.txt", logger::severity::information)
    ->build();

    logger->log("Hello", logger::severity::trace);

    delete logger;
    delete logger_builder;

    return 0;
}