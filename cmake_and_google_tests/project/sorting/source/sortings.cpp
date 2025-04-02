#include "sortings.hpp"

#include <iostream>

void mmh::sortings::insert_sort(int *arr, const int size)
{
    for (int i = 1; i < size; ++i)
    {
        int j = i;
        while (j > 0 && arr[j - 1] > arr[j])
        {
            std::swap(arr[j - 1], arr[j]);
            j--;
        }
    }
}