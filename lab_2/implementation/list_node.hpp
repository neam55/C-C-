#ifndef LIST_NODE_HPP
#define LIST_NODE_HPP

#include"list_node.h"
#include"concepts.h"

//using  List_node_ptr = std::shared_ptr<List_node<T>>;

template <storageable T>
List_node<T>::List_node(const T &data) : data(data), next(nullptr){}

template <storageable T>
List_node<T>::List_node(const T &data, List_node_ptr next) : data(data), next(next) {}

template <storageable T>
void List_node<T>::set_data(const T &data)
{
    this->data = data;
}

template <storageable T>
void List_node<T>::set_next(const List_node_ptr &node)
{
    this->next = node;
}

template <storageable T>
void List_node<T>::set_next(const List_node <T> &node)
{
    List_node_ptr node_ptr(node);
    this->next = node_ptr;
}

template <storageable T>
void List_node<T>::set_null()
{
    this->next = nullptr;
}

template <storageable T>
T &List_node<T>::get_data() const
{
    return this->data;
}

template <storageable T>
T List_node<T>::get_data_value() const
{
    return this->data;
}

template <storageable T>
List_node_ptr List_node<T>::get_next() const
{
    return this->next;
}

auto operator <=> (const List_node<T> &node) const
{
    return (this->data <=> node.data);
}



#endif // LIST_NODE_HPP
