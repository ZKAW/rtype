/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** BitPacking
*/

#pragma once
#include <cstdint>

class BitPacking {
public:
    static constexpr uint32_t SIZE_BITS = 24;
    static constexpr uint32_t TYPE_BITS = 8;
    static constexpr uint32_t SIZE_MASK = (1u << SIZE_BITS) - 1;
    static constexpr uint32_t TYPE_MASK = (1u << TYPE_BITS) - 1;

    struct Header {
        uint32_t size;
        uint8_t type;
    };

    static uint32_t packHeader(uint32_t size, uint8_t type) {
        return (size & SIZE_MASK) | ((static_cast<uint32_t>(type) & TYPE_MASK) << SIZE_BITS);
    }

    static Header unpackHeader(uint32_t packed) {
        return {
            packed & SIZE_MASK,
            static_cast<uint8_t>((packed >> SIZE_BITS) & TYPE_MASK)
        };
    }
};
