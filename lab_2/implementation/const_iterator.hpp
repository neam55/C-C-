#ifndef CONST_ITERATOR_HPP
#define CONST_ITERATOR_HPP

#include"const_iterator.h"

template <typename T>
Const_iterator<T>::Const_iterator(const Type &iterator) : curr(iterator->curr){}

template <typename T>
Const_iterator<T>::Const_iterator(List_node_ptr node) : curr(node) {}



template <typename T>
Const_iterator<T> Const_iterator<T>::next()
{
    if (this->curr.expired())
        throw Iterator_exception(__FILE__, typeid(*this).name(), get_time());
    this->curr = this->curr.lock()->get_next();
    return *this;
}

template <typename T>
bool Const_iterator<T>::is_invalid() const
{
    return (this->curr.expired());
}

template <typename T>
Const_iterator<T> Const_iterator<T>::shift(size_t offset)
{
    for (size_t i = 0; i < offset; i++)
    {
        if (this->curr.expired())
            throw Iterator_exception(__FILE__, typeid(*this).name(), get_time());
        this->curr = this->curr.lock()->get_next();
    }
    return *this;
}


template <typename T>
const T* Const_iterator<T>::operator->() const
{
    if (this->curr.expired())
        throw Iterator_exception(__FILE__, typeid(*this).name(), get_time());
    return &this->curr.lock()->get_data();
}

template <typename T>
const T& Const_iterator<T>::operator*() const
{
    if (this->curr.expired())
        throw Iterator_exception(__FILE__, typeid(*this).name(), get_time());
    return this->curr.lock()->get_data();
}

template <typename T>
Const_iterator<T>::operator bool() const
{
    return !this->curr.expired();
}

template <typename T>
Const_iterator<T> &Const_iterator<T>::operator = (const Type &iterator)
{
    if (this != iterator)
        this->curr = iterator.curr;
    return *this;
}

template <typename T>
Const_iterator<T> &Const_iterator<T>::operator ++ ()
{
    this->next();
    return *this;
}

template <typename T>
Const_iterator<T> &Const_iterator<T>::operator ++ (int)
{
    Const_iterator<T> tmp(*this);
    this->next();
    return *tmp;
}

template <typename T>
bool Const_iterator<T>::operator == (const Const_iterator<T> &iterator) const
{
    return (this->curr.lock() == iterator.curr.lock());
}

template <typename T>
Const_iterator<T> &Const_iterator<T>::operator + (size_t offset)
{
    Const_iterator<T> tmp = *this;
    tmp.shift(offset);
    return tmp;
}

template <typename T>
Const_iterator<T> &Const_iterator<T>::operator += (size_t offset)
{
    this->shift(offset);
    return *this;
}

#endif // CONST_ITERATOR_HPP
