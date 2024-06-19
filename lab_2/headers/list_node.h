#ifndef LIST_NODE_H
#define LIST_NODE_H

#include"concepts.h"
#include<memory>


template <storageable T>
class List_node
{
    using  List_node_ptr = std::shared_ptr<List_node<T>>;
public:
    List_node() = default;
    List_node(const T &data);
    List_node(const T &data, List_node_ptr next);
    ~List_node() = default;

    void set_data(const T &data);
    void set_next(const List_node_ptr &node);
    void set_next(const List_node<T> &node);
    void set_null();

    T &get_data() const;
    T get_data_value() const;
    List_node_ptr get_next() const;

    auto operator <=> (const List_node<T> &node) const;

private:
    T data;
    List_node_ptr next;
};

#endif // LIST_NODE_H
