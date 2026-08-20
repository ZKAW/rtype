/*
** EPITECH PROJECT, 2024
** Rtype [WSL: Ubuntu]
** File description:
** Zipper_iterator
*/

#pragma once

#include <tuple>
#include <iterator>
#include <utility>
#include <algorithm>

template <class... Containers>
class Zipper;

template <class... Containers>
class Zipper_iterator {
    template <class Container>
    using iterator_t = decltype(std::begin(std::declval<Container&>()));

    template <class Container>
    using it_reference_t = typename iterator_t<Container>::reference;

public:
    using value_type = std::tuple<std::remove_reference_t<decltype(std::declval<it_reference_t<Containers>>().value())>&...>;
    using reference = value_type;
    using pointer = void;
    using difference_type = size_t;
    using iterator_category = std::forward_iterator_tag;
    using iterator_tuple = std::tuple<iterator_t<Containers>...>;

    friend Zipper<Containers...>;

private:
    Zipper_iterator(iterator_tuple const &it_tuple, size_t max, size_t idx = 0)
        : _current(it_tuple), _max(max), _idx(idx) {
            if (_idx < _max && !all_set(_seq))
                incr_all(_seq);
    }

public:
    Zipper_iterator(Zipper_iterator const &z) = default;

    Zipper_iterator &operator++() {
        incr_all(_seq);
        return *this;
    }
    Zipper_iterator &operator++(int) {
        Zipper_iterator tmp(*this);
        operator++();
        return tmp;
    }

    value_type operator*() { return to_value(_seq); }
    value_type operator->() { return operator*(); }

    friend bool operator==(Zipper_iterator const &lhs, Zipper_iterator const &rhs) {
        return lhs._idx == rhs._idx;
    }
    friend bool operator!=(Zipper_iterator const &lhs, Zipper_iterator const &rhs) {
        return !(lhs == rhs);
    }

private:
    template <size_t... Is>
    void incr_all(std::index_sequence<Is...>) {
        while (true) {
            if (_idx >= _max)
                break;
            (++std::get<Is>(_current), ...);
            _idx++;
            if (all_set(_seq))
                break;
        }
    }

    template <size_t... Is>
    bool all_set(std::index_sequence<Is...>) {
        return (... && std::get<Is>(_current)->has_value());
    }

    template <size_t... Is>
    value_type to_value(std::index_sequence<Is...>) {
        return std::tie(std::get<Is>(_current)->value()...);
    }

private:
    iterator_tuple _current;
    size_t _max;
    size_t _idx;

    static constexpr std::index_sequence_for<Containers...> _seq {};
};

template <class... Containers>
class Zipper {
public:
    using iterator = Zipper_iterator<Containers...>;
    using iterator_tuple = typename iterator::iterator_tuple;

    Zipper(Containers&... cs) {
        _size = _compute_size(cs...);
        _begin = iterator_tuple(std::begin(cs)...);
        _end = _compute_end(cs...);
    }

    iterator begin() { return iterator(_begin, _size); }
    iterator end() { return iterator(_end, _size, _size); }

private:
    static size_t _compute_size(Containers&... containers) {
        return std::min({std::distance(std::begin(containers), std::end(containers))...});
    }

    static iterator_tuple _compute_end(Containers&... containers) {
        return iterator_tuple(std::end(containers)...);
    }

private:
    iterator_tuple _begin;
    iterator_tuple _end;
    size_t _size;
};
