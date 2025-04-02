#include "source/io.hpp"
#include "source/sortings.hpp"
#include "source/generate.hpp"

int main()
{
    const int arr_size = mmh::io::input_user_size();
    int* arr = new int[arr_size];
    const int max_value = mmh::io::input_user_max_value();

    mmh::io::print_array("Массив до сортировки:", arr, arr_size);

    mmh::sortings::insert_sort(arr, arr_size);

    mmh::io::print_array("Массив после сортировки:", arr, arr_size);

    return 0;
}