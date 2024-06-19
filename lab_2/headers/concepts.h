#ifndef CONCEPTS_H
#define CONCEPTS_H

#include<concepts>

template <typename T>
concept storageable = std::copyable<T> && std::three_way_comparable<T>;

#endif
