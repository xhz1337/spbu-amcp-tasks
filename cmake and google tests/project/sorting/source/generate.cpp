#include "generate.hpp"

void mmh::generate::generate_array(int *arr, const int max_val, const int n) {
    for(int i = 0; i < n; i++) {
        arr[i] = random() % max_val;
    }
}