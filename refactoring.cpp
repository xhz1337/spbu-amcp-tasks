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
        int array[N];
        fillArray(array, N);
        std::cout << "Последовательность #" << i << std::endl;
        printArray(array, N);
        std::cout << "Среднее последовательности: " << arrayArithmeticAvg(array, N) << std::endl;
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