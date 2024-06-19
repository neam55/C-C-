#ifndef LIST_H
#define LIST_H

#include<forward_list>
#include<iterator>
#include"base_container.h"
#include"concepts.h"
#include"list_node.h"
#include"const_iterator.h"
#include"iterator.h"
#include"exceptions.h"
template <typename T>
class List : public Base_container
{
    using  List_node_ptr = std::shared_ptr<List_node<T>>;
    using Type = List<T>;
    using Base = Base_container;
public:
    using value_type = T;
    using iterator = Iterator<T>;
    using const_iterator = Const_iterator<T>;
    using size_type = size_t;

    List() = default;
    explicit List(const Type &list);
    List(Type &&list) noexcept;
    explicit List(std::initializer_list<value_type> &list);
    List(const value_type *arr, const size_type len);
    explicit List(std::forward_list<value_type> &list);
    List(std::iterator<std::input_iterator_tag, value_type> beg, std::iterator<std::input_iterator_tag, value_type> end);
    virtual ~List() = default;

    virtual void clear() override;

    iterator push_tail(const value_type &data);
    value_type pop_tail();
    iterator push_head(const value_type &data);
    value_type pop_head();

    iterator merge(const Type &list);
    iterator insert_before(const iterator &iterator, const value_type &data);
    iterator insert_before(const iterator &iterator, const Type &list);
    //
    iterator insert_after(const iterator &iterator, const value_type &data);
    iterator insert_after(const iterator &iterator, const Type &list);
    //
    value_type remove(const iterator &iterator);
    iterator find(iterator beg, iterator end, const value_type &data);
    iterator find_last(iterator beg, iterator end, const value_type &data);//
    iterator add_list(Type &list);
    value_type* to_array(size_type &size);
    std::forward_list<T> &to_forward_list();

    iterator begin() const;
    const_iterator cbegin() const;
    iterator end() const;
    const_iterator cend() const;

    bool cycle_check() const;
    void apply(void (*func) (value_type &));
    //
    bool contains(const iterator &iter) const;
    bool contains(const value_type &data) const;
    bool contains_all(std::initializer_list<T> &data) const;
    bool contains_all(Type &list) const;
    bool contains_all(iterator beg, iterator end) const;
    Type &slice(iterator beg, iterator end); //меняет исходный, возвращает новый
    Type &sub_list(iterator beg, iterator end) const; // не меняет исходный, возвращает новый
    iterator reverse();
    Type &reversed() const;
    size_type index(const value_type &data) const;
    size_type index(const iterator &iter) const;
    size_type index_last(const value_type &data) const;
    size_type index_last(const iterator &iter) const;
    void replace(const value_type &data, const value_type &replacement);
    iterator min() const;
    iterator max() const;
    //

    iterator operator += (const value_type &data);
    iterator operator += (const Type &list);
    Type &operator = (const Type &list);
    Type &operator = (const std::initializer_list<T> &list);
    Type &operator = (const std::forward_list<T> &list);
    Type &operator = (Type &&list);
    Type &operator + (const Type &list);
    Type &operator + (const value_type data);
    value_type &operator [](const size_type index);

    bool operator == (const Type &list) const;


    void list_cout() const;

    friend std::ostream& operator<<(std::ostream& stream, Type& list)
    {
        stream << "LIST: ";
        iterator iter = list.begin();
        if (!iter.is_invalid())
            stream << "EMPTY";
        else
        {
            for (; iter.is_invalid(); iter++)
                stream << " " << *iter;
        }
        return stream;
    }


    friend std::istream& operator>>(std::istream& stream, Type& list)
    {
        size_type size;
        std::cout << "Enter size: ";
        stream >> size;
        std::cout << "Enter elems: ";
        value_type elem;
        for (size_type i = 0; i < size; i++)
        {
            stream >> elem;
            list.push_tail(elem);
        }
        return stream;
    }


private:
    List_node_ptr head;
    List_node_ptr tail;
    size_type size;

    List_node_ptr node_init(const value_type& data, List_node_ptr next = nullptr);
    void list_concat(const Type &list);
    bool nodes_cmp(const Type &list) const;
};

#include "list.hpp"

#endif // LIST_H
