#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include"iterator.h"


template <typename T>
Iterator<T>::Iterator(const Iterator &iterator) : curr(iterator.curr){}

//template <typename T>
//Iterator<T>::Iterator(List_node_ptr &node) : curr(node) {}

template <typename T>
Iterator<T>::Iterator(List_node_ptr node) : curr(node) {}

template <typename T>
Iterator<T> Iterator<T>::next()
{
    if (this->curr.expired())
        throw Iterator_exception(__FILE__, typeid(*this).name(), get_time());
    this->curr = this->curr.lock()->get_next();
    return *this;
}

template <typename T>
Iterator<T> Iterator<T>::shift(size_t offset)
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
bool Iterator<T>::is_invalid() const
{
    return (this->curr.expired());
}

template <typename T>
T *Iterator<T>::operator ->() const
{
    if (this->curr.expired())
        throw Iterator_exception(__FILE__, typeid(*this).name(), get_time());
    return &this->curr.lock()->get_data();
}

template <typename T>
T &Iterator<T>::operator *() const
{
    if (this->curr.expired())
        throw Iterator_exception(__FILE__, typeid(*this).name(), get_time());
    return this->curr.lock()->get_data();

}

template <typename T>
Iterator<T>::operator bool() const
{
    return !this->curr.expired();
}

template <typename T>
Iterator<T> &Iterator<T>::operator = (Type &iterator)
{
    if (!(*this == iterator))
        this->curr = iterator.curr;
    return *this;
}

template <typename T>
Iterator<T> &Iterator<T>::operator ++ ()
{
    this->next();
    return *this;
}

template <typename T>
Iterator<T> &Iterator<T>::operator ++ (int)
{
    Iterator<T> tmp(*this);
    this->next();
    return tmp;
}


template <typename T>
bool Iterator<T>::operator == (Iterator<T> &iterator) const
{
    return (this->curr.lock() == iterator.curr.lock());
}

template <typename T>
Iterator<T> &Iterator<T>::operator + (size_t offset)
{
    Iterator<T> tmp = *this;
    tmp.shift(offset);
    return tmp;
}

template <typename T>
Iterator<T> &Iterator<T>::operator += (size_t offset)
{
    this->shift(offset);
    return *this;
}



#endif // ITERATOR_HPP
