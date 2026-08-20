/*
** EPITECH PROJECT, 2024
** Rtype [WSL: Ubuntu]
** File description:
** SparseArray
*/

#pragma once

#include <memory>
#include <optional>
#include <vector>
#include <limits>
#include <stdexcept>

template <typename Component, typename Allocator = std::allocator<std::optional<Component>>>
class SparseArray {
public:
    using value_type = std::optional<Component>;
    using reference_type = value_type&;
    using const_reference_type = value_type const&;
    using container_t = std::vector<value_type, Allocator>;
    using size_type = typename container_t::size_type;

    using iterator = typename container_t::iterator;
    using const_iterator = typename container_t::const_iterator;

public:
    SparseArray() : _data() {}
    explicit SparseArray(size_type size) : _data(size) {}
    SparseArray(size_type size, const value_type& default_value) : _data(size, default_value) {}
    explicit SparseArray(const Allocator& alloc) : _data(alloc) {}
    SparseArray(const SparseArray& other) : _data(other._data) {}
    SparseArray(SparseArray&& other) noexcept : _data(std::move(other._data)) {}
    ~SparseArray() = default;

    SparseArray& operator=(const SparseArray& other) {
        if (this != &other)
            _data = other._data;
        return *this;
    }

    SparseArray& operator=(SparseArray&& other) noexcept {
        if (this != &other)
            _data = std::move(other._data);
        return *this;
    }

    reference_type operator[](size_t idx) {
        if (idx >= _data.size())
            throw std::out_of_range("Index out of range");
        return _data[idx];
    }
    const_reference_type operator[](size_t idx) const {
        if (idx >= _data.size())
            throw std::out_of_range("Index out of range");
        return _data[idx];
    }

    iterator begin() { return _data.begin(); }
    const_iterator begin() const { return _data.begin(); }
    const_iterator cbegin() const { return _data.cbegin(); }

    iterator end() { return _data.end(); }
    const_iterator end() const { return _data.end(); }
    const_iterator cend() const { return _data.cend(); }

    size_type size() const { return _data.size(); }

    reference_type insert_at(size_type pos, const Component& value) {
        if (pos >= _data.size())
            _data.resize(pos + 1);
        _data[pos] = value;
        return _data[pos];
    }

    reference_type insert_at(size_type pos, Component&& value) {
        if (pos >= _data.size())
            _data.resize(pos + 1);
        _data[pos] = std::move(value);
        return _data[pos];
    }

    template <class... Params>
    reference_type emplace_at(size_type pos, Params&&... params) {
        if (pos >= _data.size())
            _data.resize(pos + 1);

        auto allocator = _data.get_allocator();

        std::allocator_traits<decltype(allocator)>::destroy(allocator, std::addressof(_data[pos]));

        std::allocator_traits<decltype(allocator)>::construct(
            allocator, std::addressof(_data[pos]), std::forward<Params>(params)...);

        return _data[pos];
    }

    void erase(size_type pos) {
        if (pos < _data.size())
            _data[pos].reset();
    };

    void clear() {
        _data.clear();
    }

    size_type get_index(value_type const& value) const {
        for (size_type i = 0; i < _data.size(); ++i) {
            if (std::addressof(_data[i]) == std::addressof(value))
                return i;
        }
        return std::numeric_limits<size_type>::max();
    }

private:
    container_t _data;
};
