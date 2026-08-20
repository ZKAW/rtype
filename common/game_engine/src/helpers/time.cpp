/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** time
*/

#include "time.hpp"

int64_t getTime()
{
    auto now = std::chrono::system_clock::now();
    auto duration = now.time_since_epoch();
    return std::chrono::duration_cast<std::chrono::nanoseconds>(duration).count();
}
