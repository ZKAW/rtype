/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** cross_attributes
*/

#pragma once

#include <chrono>
#include <thread>

#ifdef _WIN32
    #ifdef DELETE
        #undef DELETE
    #endif

    #define usleep(ms) std::this_thread::sleep_for(std::chrono::milliseconds(ms))
#endif