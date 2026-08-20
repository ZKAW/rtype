/*
** EPITECH PROJECT, 2024
** Arcade [WSL: Ubuntu]
** File description:
** InputQueue
*/

#pragma once

#include <queue>
#include <cstdint>
#include <iostream>

#include "cross_attributes.hpp"

enum class KeyType : uint8_t {
    KEYDOWN = 0x01,
    KEYUP = 0x02
};

enum class KeyState : uint8_t {
    PRESSED = 0x01,
    RELEASED = 0x02
};

enum class InputKey : uint16_t {
    NONE       = 0x00,
    A          = 0x01,
    B          = 0x02,
    C          = 0x03,
    D          = 0x04,
    E          = 0x05,
    F          = 0x06,
    G          = 0x07,
    H          = 0x08,
    I          = 0x09,
    J          = 0x0A,
    K          = 0x0B,
    L          = 0x0C,
    M          = 0x0D,
    N          = 0x0E,
    O          = 0x0F,
    P          = 0x10,
    Q          = 0x11,
    R          = 0x12,
    S          = 0x13,
    T          = 0x14,
    U          = 0x15,
    V          = 0x16,
    W          = 0x17,
    X          = 0x18,
    Y          = 0x19,
    Z          = 0x1A,
    NUM0       = 0x1B,
    NUM1       = 0x1C,
    NUM2       = 0x1D,
    NUM3       = 0x1E,
    NUM4       = 0x1F,
    NUM5       = 0x20,
    NUM6       = 0x21,
    NUM7       = 0x22,
    NUM8       = 0x23,
    NUM9       = 0x24,
    F1         = 0x25,
    F2         = 0x26,
    F3         = 0x27,
    F4         = 0x28,
    F5         = 0x29,
    F6         = 0x2A,
    F7         = 0x2B,
    F8         = 0x2C,
    F9         = 0x2D,
    F10        = 0x2E,
    F11        = 0x2F,
    F12        = 0x30,
    UP         = 0x31,
    DOWN       = 0x32,
    LEFT       = 0x33,
    RIGHT      = 0x34,
    SPACE      = 0x35,
    TAB        = 0x36,
    ENTER      = 0x37,
    ESCAPE     = 0x38,
    BACKSPACE  = 0x39,
    DELETE     = 0x3A,
    CLOSE      = 0x3B
};

struct InputEvent {
    KeyType type;
    KeyState state;
    double timestampSec;
    bool repeat;
    InputKey key;
};

class InputQueueError : public std::exception {
    public:
        explicit InputQueueError(const std::string &message) : _message(message) {}
        const char *what() const noexcept override { return _message.c_str(); }

    private:
        std::string _message;
};

class InputQueue {
    public:
        InputQueue() = default;
        ~InputQueue() = default;
        InputQueue(const InputQueue &other) : _queueEvent(other._queueEvent) {}

        InputQueue &operator=(const InputQueue &other) {
            if (this != &other)
                _queueEvent = other._queueEvent;
            return *this;
        }

        void addInputEvent(const InputEvent &key);
        auto getFrontInputEvent(void) const -> InputEvent;
        auto getInputEvent(void) -> InputEvent;
        bool isEmpty(void) const { return _queueEvent.empty(); }
        void reset(void);

    private:
        std::queue<InputEvent> _queueEvent;
};
