#include <iostream>
#include "containers/data_base.h"
#include <fstream>

int main(int argc, char *argv[])
{
    data_base * db = new data_base();

    std::string command;

    std::ifstream file(argv[1]);

    if (file.is_open())
    {
        while (std::getline(file, command)) {
            db->handle_request(command);
        }
    }
    else
    {
        std::cout << "File with name:" << argv[1] << " can't be opened" << std::endl;
    }

    delete db;

    getchar();

    return 0;
}