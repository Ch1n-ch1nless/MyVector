#include "my_vector.hpp"

#include <iostream>

int main()
{
    Containers::Vector<int> array(1);

    array[0] = 1;

    array.PushBack(1);

    std::cout << array[0] << ' ' << array[1];

    return 0;
}