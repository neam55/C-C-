#ifndef CONST_ITERATOR_H
#define CONST_ITERATOR_H

#include"exceptions.h"
#include"base_iterator.h"
#include"list_node.h"

template <typename T>
class Const_iterator : Base_iterator
{
    using List_node_ptr = std::shared_ptr<List_node<T>>;
    using Type = Const_iterator<T>;
public:
    using iterator_tag = std::input_iterator_tag;
    using value_type = T;
    using diff_type = ptrdiff_t;
    using cpointer = const T*;
    using creference = const T&;

    Const_iterator() = default;
    ~Const_iterator() = default;
    Const_iterator(const Type &iterator);
    Const_iterator(List_node_ptr node);

    virtual Type next();
    virtual bool is_invalid() const override;
    Type shift(size_t offset);

    cpointer operator ->() const;
    creference operator *() const;
    operator bool() const;

    Type &operator = (const Type &iterator);
    Type &operator ++ ();
    Type &operator ++ (int);
    Type &operator + (size_t offset);
    Type &operator += (size_t offset);

    bool operator == (const Type &iterator) const;

protected:
    std::weak_ptr<List_node<value_type>> curr;
};

#include"const_iterator.hpp"
#endif // CONST_ITERATOR_H
