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
        try
        {
            db->handle_request(command);
        }
        catch (std::exception const &ex)
        {
            std::cout << ex.what() << std::endl;
        }
    }

//    try
//    {
//        db->add_pool("pool1", allocator_types::SORTED_LIST , 1000000, memory::allocation_mode::first_match);
//        db->add_scheme("pool2", "scheme1");
//    }
//    catch (std::exception const &ex)
//    {
//        std::cout << ex.what() << std::endl;
//    }

    delete db;

    return 0;
}
