#include <iostream>
#include "containers/data_base.h"

int main(int argc, char *argv[])
{

    data_base * db = new data_base();
    db->read_file((std::string &) "file.txt");
//    try
//    {
//        db->read_file((std::string &) argv[1]);
//    }
//    catch (std::exception const & ex)
//    {
//        ex.what();
//    }

    delete db;

    return 0;
}
