/*
** EPITECH PROJECT, 2024
** Rtype [WSL: Ubuntu]
** File description:
** Hybrid_array
*/

#pragma once

#include <variant>
#include <algorithm>
#include <vector>
#include <optional>

// don't work !!!!!!

template <typename Component/*, typename Allocator = std::allocator<std::optional<Component>>*/>
class HybridArray {
public:
    using value_type = std::optional<Component>;
    using reference_type = value_type&;
    using const_reference_type = value_type const&;
    using size_type = typename std::vector<value_type>::size_type;

    using iterator = typename std::vector<value_type>::iterator;
    using const_iterator = typename std::vector<value_type>::const_iterator;

private:
    struct Sparse {
        std::vector<value_type> data;
    };

    struct Dense {
        std::vector<size_type> entity_ids;
        std::vector<value_type> components;
    };

    std::variant<Sparse, Dense> storage;
    size_type threshold;

public:
    HybridArray(size_type threshold = 10) : storage(Sparse()), threshold(threshold) {}
    ~SparseArray() = default;

    HybridArray& operator=(const HybridArray& other) {
        if (this != &other) {
            storage = other.storage;
            threshold = other.threshold;
        }
        return *this;
    }

    HybridArray& operator=(HybridArray&& other) noexcept {
        if (this != &other) {
            storage = std::move(other.storage);
            threshold = other.threshold;
        }
        return *this;
    }

    reference_type operator[](size_type idx) {
        return std::visit([idx](auto& storage) -> reference_type {
            if constexpr (std::is_same_v<decltype(storage), Sparse&>) {
                if (idx >= storage.data.size())
                    throw std::out_of_range("Index out of range");
                return storage.data[idx];
            } else {
                auto it = std::find(storage.entity_ids.begin(), storage.entity_ids.end(), idx);
                if (it == storage.entity_ids.end())
                    throw std::out_of_range("Index out of range");
                return storage.components[std::distance(storage.entity_ids.begin(), it)];
            }
        }, storage);
    }

    const_reference_type operator[](size_type idx) const {
        return std::visit([idx](const auto& storage) -> const_reference_type {
            if constexpr (std::is_same_v<decltype(storage), Sparse&>) {
                if (idx >= storage.data.size())
                    throw std::out_of_range("Index out of range");
                return storage.data[idx];
            } else {
                auto it = std::find(storage.entity_ids.begin(), storage.entity_ids.end(), idx);
                if (it == storage.entity_ids.end())
                    throw std::out_of_range("Index out of range");
                return storage.components[std::distance(storage.entity_ids.begin(), it)];
            }
        }, storage);
    }

    void insert_at(size_type pos, const Component& value) {
        std::visit([this, pos, &value](auto& storage) {
            if constexpr (std::is_same_v<decltype(storage), Sparse&>) {
                if (pos >= storage.data.size())
                    storage.data.resize(pos + 1);
                storage.data[pos] = value;
            } else {
                storage.entity_ids.push_back(pos);
                storage.components.push_back(value);
            }
        }, storage);
        update_storage();
    }

    void insert_at(size_type pos, Component&& value) {
        std::visit([this, pos, &value](auto& storage) {
            if constexpr (std::is_same_v<decltype(storage), Sparse&>) {
                if (pos >= storage.data.size())
                    storage.data.resize(pos + 1);
                storage.data[pos] = std::move(value);
            } else {
                storage.entity_ids.push_back(pos);
                storage.components.push_back(std::move(value));
            }
        }, storage);
        update_storage();
    }

    void erase(size_type pos) {
        std::visit([pos](auto& storage) {
            if constexpr (std::is_same_v<decltype(storage), Sparse&>) {
                if (pos < storage.data.size())
                    storage.data[pos].reset();
            } else {
                auto it = std::find(storage.entity_ids.begin(), storage.entity_ids.end(), pos);
                if (it != storage.entity_ids.end()) {
                    auto index = std::distance(storage.entity_ids.begin(), it);
                    storage.entity_ids.erase(it);
                    storage.components.erase(storage.components.begin() + index);
                }
            }
        }, storage);
        update_storage();
    }

    template <class... Params>
    reference_type emplace_at(size_type pos, Params&&... params) { // pas sur
        return std::visit([this, pos, &params...](auto& storage) -> reference_type {
            if constexpr (std::is_same_v<decltype(storage), Sparse&>) {
                if (pos >= storage.data.size())
                    storage.data.resize(pos + 1);
                storage.data[pos].emplace(std::forward<Params>(params)...);
            } else {
                storage.entity_ids.push_back(pos);
                storage.components.emplace_back(std::forward<Params>(params)...);
                return storage.components.back();
            }
        }, storage);
        update_storage();
    }

    iterator begin() {
        return std::visit([](auto& storage) -> iterator {
            if constexpr (std::is_same_v<decltype(storage), Sparse&>) {
                return storage.data.begin();
            } else {
                return storage.components.begin();
            }
        }, storage);
    }

    const_iterator begin() const {
        return std::visit([](const auto& storage) -> const_iterator {
            if constexpr (std::is_same_v<decltype(storage), Sparse&>) {
                return storage.data.begin();
            } else {
                return storage.components.begin();
            }
        }, storage);
    }

    const_iterator cbegin() const {
        return std::visit([](const auto& storage) -> const_iterator {
            if constexpr (std::is_same_v<decltype(storage), Sparse&>) {
                return storage.data.cbegin();
            } else {
                return storage.components.cbegin();
            }
        }, storage);
    }

    iterator end() {
        return std::visit([](auto& storage) -> iterator {
            if constexpr (std::is_same_v<decltype(storage), Sparse&>) {
                return storage.data.end();
            } else {
                return storage.components.end();
            }
        }, storage);
    }


    const_iterator end() const {
        return std::visit([](const auto& storage) -> const_iterator {
            if constexpr (std::is_same_v<decltype(storage), Sparse&>) {
                return storage.data.end();
            } else {
                return storage.components.end();
            }
        }, storage);
    }

    const_iterator cend() const {
        return std::visit([](const auto& storage) -> const_iterator {
            if constexpr (std::is_same_v<decltype(storage), Sparse&>) {
                return storage.data.cend();
            } else {
                return storage.components.cend();
            }
        }, storage);
    }

    size_type size() const {
        return std::visit([](const auto& storage) -> size_type {
            if constexpr (std::is_same_v<decltype(storage), Sparse&>) {
                return storage.data.size();
            } else {
                return storage.entity_ids.size();
            }
        }, storage);
    }

private:
    void switch_to_dense() {
        Sparse& sparse = std::get<Sparse>(storage);
        Dense dense;
        for (size_type i = 0; i < sparse.data.size(); ++i) {
            if (sparse.data[i].has_value()) {
                dense.entity_ids.push_back(i);
                dense.components.push_back(*sparse.data[i]);
            }
        }
        storage = std::move(dense);
    }

    void switch_to_sparse() {
        Dense& dense = std::get<Dense>(storage);
        Sparse sparse;
        size_type max_id = *std::max_element(dense.entity_ids.begin(), dense.entity_ids.end());
        sparse.data.resize(max_id + 1);
        for (size_type i = 0; i < dense.entity_ids.size(); ++i)
            sparse.data[dense.entity_ids[i]] = dense.components[i];
        storage = std::move(sparse);
    }

    void update_storage() {
        size_type count = std::visit([](auto& storage) -> size_type {
            if constexpr (std::is_same_v<decltype(storage), Sparse&>) {
                return std::count_if(storage.data.begin(), storage.data.end(), [](const_reference_type v) { return v.has_value(); });
            } else {
                return storage.entity_ids.size();
            }
        }, storage);

        if (count > threshold && std::holds_alternative<Sparse>(storage)) {
            switch_to_dense();
        } else if (count <= threshold && std::holds_alternative<Dense>(storage)) {
            switch_to_sparse();
        }
    }
};
