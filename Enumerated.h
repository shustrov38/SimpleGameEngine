//
// Created by shusrov38 on 26.07.2021.
//

#ifndef SIMPLEGAMEENGINE_ENUMERATED_H
#define SIMPLEGAMEENGINE_ENUMERATED_H

#include <tuple>

/*
 * returns the tuple of index and reference to object
 */
template<typename T,
        typename TIter = decltype(std::begin(std::declval<T>())),
        typename = decltype(std::end(std::declval<T>()))>
constexpr auto enumerated(T &&iterable) {
    struct iterator {
        size_t i;
        TIter iter;

        bool operator!=(const iterator &other) const { return iter != other.iter; }

        void operator++() {
            ++i;
            ++iter;
        }

        auto operator*() const { return std::tie(i, *iter); }
    };
    struct iterable_wrapper {
        T iterable;

        auto begin() { return iterator{0, std::begin(iterable)}; }

        auto end() { return iterator{0, std::end(iterable)}; }
    };
    return iterable_wrapper{std::forward<T>(iterable)};
}
#endif //SIMPLEGAMEENGINE_ENUMERATED_H
