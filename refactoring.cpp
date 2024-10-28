#include <cmath>
#include <iostream>

double calcArrayArithmeticAvg(const int* const arr, const int arrayLen);
void fillArray(int const *array, const int arrayLen);
void printArray(const int* const arr, const int arrayLen);



int main()
{
    for (int i = 0; i < 3; i++)
    {
        const int arrayLen = 10;
        int array[arrayLen];
        fillArray(array, arrayLen);
        
        std::cout << "Последовательность #" << i + 1 << std::endl;
        printArray(array, arrayLen);
        
        std::cout << "Среднее последовательности: " << calcArrayArithmeticAvg(array, arrayLen) << std::endl;
    }
    return 0;
}

void fillArray(int const *array, const int arrayLen);
{
    for (int i = 0; i < arrayLen; i++)
    {
        array[i] = random() % 10;
    }
}

void printArray(const int* const arr, const int arrayLen);
{
    static const char format = ' ';
    for (int i = 0; i < arrayLen; i++)
    {
        std::cout << array[i] << format;
    }
    std::cout << std::endl;
}

double calcArrayArithmeticAvg(const int* const arr, const int arrayLen);
{
    float arrayElemSum = 0;
    for (int i = 0; i < arrayLen; i++)
    {
        arrayElemSum += array[i];
    }
    return arrayElemSum / arrayLen;
}
