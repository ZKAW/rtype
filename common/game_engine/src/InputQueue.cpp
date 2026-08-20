/*
** EPITECH PROJECT, 2024
** Arcade [WSL: Ubuntu]
** File description:
** InputQueue
*/

#include "InputQueue.hpp"

void InputQueue::addInputEvent(const InputEvent &key)
{
    _queueEvent.push(key);
}

auto InputQueue::getFrontInputEvent() const -> InputEvent
{
    if (_queueEvent.empty()) {
        throw InputQueueError("No input event in queue");
    }
    return _queueEvent.front();
}

auto InputQueue::getInputEvent() -> InputEvent
{
    InputEvent key;

    if (_queueEvent.empty()) {
        throw InputQueueError("No input event in queue");
    }
    key =  _queueEvent.front();
    _queueEvent.pop();
    return key;
}

void InputQueue::reset()
{
    while (!_queueEvent.empty()) {
        _queueEvent.pop();
    }
}
