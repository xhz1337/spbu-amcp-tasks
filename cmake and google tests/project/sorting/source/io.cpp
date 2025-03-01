#include "io.hpp"

#include <iostream>


int mmh::io::input_user_max_value() {
	std::cout << "Введите максимум для массива:" << std::endl;
	int max_value;
	std::cin >> max_value;
	return max_value;
}

int mmh::io::input_user_size() {
	std::cout << "Введите длину массива:" << std::endl;
	int size;
	std::cin >> size;
	return size;
}

void mmh::io::print_array(const char* const comment, const int * const arr, const int arr_size){
	const char format = ' ';
	std::cout << comment;
	std::cout << std::endl;
	for (int i = 0; i < arr_size; i++) {
		std::cout << arr[i] << format;
    }
	std::cout << std::endl;
}