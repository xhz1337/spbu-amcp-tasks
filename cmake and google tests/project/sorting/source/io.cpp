#include "io.hpp"

#include <iostream>

void mmh::print_array(const char *const comment, int *arr, const int size)
{
    const char format = ' ';
    std::cout << comment;
    for (int i = 0; i < size; i++)
    {
        std::cout << arr[i] << format;
    }
    std::cout << std::endl;
}