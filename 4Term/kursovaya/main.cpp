#include <iostream>
#include "containers/data_base.h"

int main(int argc, char *argv[])
{
    data_base * db = new data_base();

    db->add_pool("pool1", allocator_types::SORTED_LIST, 1000000, memory::allocation_mode::first_match);
    db->add_scheme("pool1", "scheme1");
    db->add_collection("pool1", "scheme1", "collection1");
    db->add_data("pool1", "scheme1", "collection1", 1, 1, form::EXAM, "fund", "khasanov", "daniil", "rafailovich", "04.06.2023", "15:38", 5);

    delete db;

    return 0;
}
