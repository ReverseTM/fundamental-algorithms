#include <iostream>
#include "containers/data_base.h"
#include <fstream>

int main(int argc, char *argv[])
{

    data_base * db = new data_base();

    std::string command;

    std::ifstream file("../tests/file_to_test.txt");

    while (std::getline(file, command))
    {
        db->handle_request(command);
    }

    delete db;

    getchar();

    return 0;
}
