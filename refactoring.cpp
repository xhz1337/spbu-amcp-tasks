#include <cmath>
#include <iostream>

float arrayArithmeticAvg(int *array, const int &arrayLen);
void fillArray(int *array, const int &arrayLen);
void printArray(int *array, const int &arrayLen);

const int arrayLen = 10;

int main()
{
    for (int i = 0; i < 3; i++)
    {
        int array[arrayLen];
        fillArray(array, arrayLen);
        std::cout << "Последовательность #" << i + 1 << std::endl;
        printArray(array, arrayLen);
        std::cout << "Среднее последовательности: " << arrayArithmeticAvg(array, arrayLen) << std::endl;
    }
    return 0;
}

void fillArray(int *array, const int &arrayLen)
{
    for (int i = 0; i < arrayLen; i++)
    {
        array[i] = random() % 10;
    }
}

void printArray(int *array, const int &arrayLen)
{
    for (int i = 0; i < arrayLen; i++)
    {
        std::cout << array[i] << ' ';
    }
    std::cout << std::endl;
}

float arrayArithmeticAvg(int *array, const int &arrayLen)
{
    float arrayElemSum = 0;
    for (int i = 0; i < arrayLen; i++)
    {
        arrayElemSum += array[i];
    }
    return arrayElemSum / arrayLen;
}
