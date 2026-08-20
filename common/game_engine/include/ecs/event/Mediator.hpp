/*
** EPITECH PROJECT, 2024
** Rtype [WSL: Ubuntu]
** File description:
** Mediator
*/

#pragma once

#pragma once
#include <functional>
#include <unordered_map>
#include <vector>
#include <typeindex>
#include <any>

class Mediator {
public:
    template<typename Event>
    void subscribe(std::function<void(const Event&)> callback) {
        auto& subscribers = _subscribers[typeid(Event)];
        subscribers.push_back([callback](const auto& event) {
            callback(static_cast<const Event&>(event));
        });
    }

    template<typename Event>
    void publish(const Event& event) {
        auto it = _subscribers.find(typeid(Event));
        if (it != _subscribers.end()) {
            for (auto& subscriber : it->second) {
                subscriber(event);
            }
        }
    }

private:
    std::unordered_map<std::type_index, std::vector<std::function<void(const std::any&)>>> _subscribers;
};
