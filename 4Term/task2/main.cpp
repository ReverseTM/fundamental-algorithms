#include <iostream>
#include "memory_implementation.h"

class A final
{
private:
    int _x = 0;
    int _y = 0;

public:
    A(int x, int y)
    {
        _x = x;
        _y = y;
    }
    void sum() const
    {
        std::cout << _y + _x << std::endl;
    }
};

int main() {

    Json *json = new Json_implementation("../config.json");
    Logger *logger = json->create();

    Memory *allocator = new Memory_implementation();

    A *obj = reinterpret_cast<A*>(allocator->allocate(*logger, sizeof(A)));
    *obj = A(5, 4);
    obj->sum();
    allocator->deallocate(*logger, reinterpret_cast<void*>(obj));

    int *digit = reinterpret_cast<int*>(allocator->allocate(*logger, sizeof(int)));
    *digit = 25;
    std::cout << *digit << std::endl;
    allocator->deallocate(*logger, reinterpret_cast<void*>(obj));

    char *symbols = reinterpret_cast<char*>(allocator->allocate(*logger, sizeof(char) * 3));
    symbols[0] = '1';
    symbols[1] = '2';
    symbols[2] = 0;
    std::cout << symbols << std::endl;
    allocator->deallocate(*logger, reinterpret_cast<void*>(symbols));

//    std::string *str = reinterpret_cast<std::string*>(allocator->allocate(*logger, sizeof(std::string)));
//    *str = "1234";
//    std::cout << *str << std::endl;
//    allocator->deallocate(*logger, reinterpret_cast<void*>(str));

    delete allocator;
    delete logger;

    return 0;
}
