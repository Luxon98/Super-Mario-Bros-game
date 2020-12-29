#ifndef RandomGenerator_H
#define RandomGenerator_H

#include <random>


thread_local std::mt19937 gen{ std::random_device{}() };

template<typename T>
T getRandomNumber(T beg, T end)
{
    return std::uniform_int_distribution<T>{beg, end}(gen);
}

#endif //RandomGenerator_H