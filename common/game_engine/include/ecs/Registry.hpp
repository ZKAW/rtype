/*
** EPITECH PROJECT, 2024
** Rtype [WSL: Ubuntu]
** File description:
** Registry
*/

#pragma once

#include "containers/SparseArray.hpp"
#include "Entity.hpp"
#include <unordered_map>
#include <typeindex>
#include <any>
#include <exception>
#include <string>
#include <queue>
#include <functional>
#include <utility>

class RegistryError : public std::exception {
public:
    RegistryError(const std::string &message) : _message(message) {}
    const char *what() const noexcept override { return _message.c_str(); }
private:
    std::string _message;
};

class Registry {
public:
    Registry() = default;
    ~Registry() = default;

    template <typename Component>
    SparseArray<Component> &registerComponent() {
        std::type_index type = std::type_index(typeid(Component));

        if (_components_arrays.find(type) != _components_arrays.end())
            throw RegistryError("Component already registered");
        _components_arrays[type] = SparseArray<Component>();

        _erase_functions[type] = [](Registry &registry, Entity const &entity) {
            registry.getComponents<Component>().erase(entity);
        };

        return getComponents<Component>();
    }

    template <typename Component>
    SparseArray<Component> &getComponents() {
        std::type_index type = std::type_index(typeid(Component));

        if (_components_arrays.find(type) == _components_arrays.end())
            throw RegistryError("Component not registered");
        return std::any_cast<SparseArray<Component> &>(_components_arrays[type]);
    }

    template <typename Component>
    SparseArray<Component> const &getComponents() const {
        std::type_index type = std::type_index(typeid(Component));

        if (_components_arrays.find(type) == _components_arrays.end())
            throw RegistryError("Component not registered");
        return std::any_cast<SparseArray<Component> const &>(_components_arrays.at(type));
    }

    // Entity management
    Entity spawnEntity() {
        if (_dead_entities.empty())
            return Entity(_next_entity_id++);
        Entity e(_dead_entities.front());
        _dead_entities.pop();
        return e;
    }

    template <typename Component>
    bool entityHasComponent(Entity const &e) {
        SparseArray<Component> &components = getComponents<Component>();
        if (components.size() <= e)
            return false;
        return getComponents<Component>()[e].has_value();
    }

    template <typename Component>
    bool entityHasComponent(size_t e) {
        SparseArray<Component> &components = getComponents<Component>();
        if (components.size() <= e)
            return false;
        return getComponents<Component>()[e].has_value();
    }

    void killEntity(Entity const &e) {
        _dead_entities.push(e);
        for (auto &[type, erase_function] : _erase_functions)
            erase_function(*this, e);
    }

    void killEntity(size_t id) {
        killEntity(Entity{id});
    }

    template <typename Component>
    typename SparseArray<Component>::reference_type addComponent(Entity const &to, Component &&c) {
        return getComponents<Component>().insert_at(to, std::forward<Component>(c));
    }

    template <typename Component, typename... Params>
    typename SparseArray<Component>::reference_type emplaceComponent(Entity const &to, Params &&... p) {
        return getComponents<Component>().insert_at(to, Component(std::forward<Params>(p)...));
    }

    template <typename Component>
    void removeComponent(Entity const &from) {
        getComponents<Component>().erase(from);
    }

    // Builders management
    template <typename ParamsType>
    void registerBuilder() {
        _builders[std::type_index(typeid(ParamsType))] = [this](std::any raw_params) {
            ParamsType& params = std::any_cast<ParamsType&>(raw_params);
            Entity entity = this->spawnEntity();

            auto components = params.as_tuple();
            addComponentsBuilder(*this, entity, components);

            return entity;
        };
    }

    template<typename Params>
    Entity createEntity(const Params& params) {
        using ParamsType = std::decay_t<Params>;
        auto it = _builders.find(std::type_index(typeid(ParamsType)));
        if (it != _builders.end())
            return it->second(params);
        throw RegistryError("No builder found for Params type: " + std::string(typeid(ParamsType).name()));
    }

    // Systems management
    template <class... Components, typename Function>
    void addSystem(Function&& f) {
        auto system = [this, f = std::forward<Function>(f)]() {
            f(*this, getComponents<Components>()...);
        };
        _systems.emplace_back(system);
    }

    template <class... Components, typename Function>
    void addSystem(Function const& f) {
        auto system = [this, f]() {
            f(*this, getComponents<Components>()...);
        };
        _systems.emplace_back(system);
    }

    void runSystems() {
        for (auto& system : _systems) {
            system();
        }
    }

    // Context management
    template <typename T>
    T &getContext() {
        try {
            return std::any_cast<T &>(_context);
        } catch (std::bad_any_cast const &) {
            throw RegistryError("Context not set");
        }
    }

    void setContext(std::any context) {
        _context = context;
    }

private:
    template <typename Registry, typename Entity, typename... Components>
    void addComponentsBuilder(Registry &r, Entity entity, std::tuple<Components...>& components) {
        std::apply([&](auto&&... args) {
            ((r.template addComponent<std::decay_t<decltype(args)>>(entity, std::move(args))), ...);
        }, components);
    }

private:
    std::unordered_map<std::type_index, std::any> _components_arrays;
    std::unordered_map<std::type_index, std::function<Entity(std::any)>> _builders;
    std::unordered_map<std::type_index, std::function<void(Registry&, Entity const&)>> _erase_functions;
    std::vector<std::function<void()>> _systems;
    std::queue<Entity> _dead_entities;
    Entity::type _next_entity_id = 0;
    std::any _context;
};
