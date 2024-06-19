#ifndef ITERATOR_H
#define ITERATOR_H

#include"exceptions.h"
#include"base_iterator.h"
#include"list_node.h"

template <typename T>
class Iterator : Base_iterator
{
    using List_node_ptr = std::shared_ptr<List_node<T>>;
    using Type = Iterator<T>;
public:
    using iterator_tag = std::input_iterator_tag;
    using value_type = T;
    using diff_type = ptrdiff_t;
    using pointer = T*;
    using reference = T&;

    Iterator() = default;
    ~Iterator() = default;
    Iterator(const Type &iterator);
    Iterator(List_node_ptr node);

    virtual Type next();
    virtual bool is_invalid() const override;
    Type shift(size_t offset);

    pointer operator ->() const;
    reference operator *() const;
    operator bool() const;

    Type &operator = (Type &iterator);
    Type &operator ++ ();
    Type &operator ++ (int);
    Type &operator + (size_t offset);
    Type &operator += (size_t offset);

    bool operator == (Type &iterator) const;

protected:
    std::weak_ptr<List_node<value_type>> curr;
};

#include"iterator.hpp"

#endif // ITERATOR_H
