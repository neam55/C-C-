#ifndef LIST_HPP
#define LIST_HPP

#include"list.h"
#include"exceptions.h"

//Конструкторы
template<typename T>
List<T>::List(const List<T> &list) : head(nullptr), tail(nullptr), size(0)
{
    this->list_concat(list);
}

template<typename T>
List<T>::List(List<T> &&list) noexcept
{
    this->size = list.size;
    this->head.reset(list.head);
    this->tail.reset(list.tail);
    //this->head = list.head;
    //this->tail = list.tail;
}

template<typename T>
List<T>::List(std::initializer_list<T> &list) : head(nullptr), tail(nullptr), size(0)
{
    for (auto &node: list)
        this->push_tail(node);
}

template<typename T>
List<T>::List(const T *arr, const size_t len) : head(nullptr), tail(nullptr), size(0)
{
    for(size_t i = 0; i < len; i++)
        this->push_tail(arr[i]);
}

template<typename T>
List<T>::List(std::forward_list<T> &list) : head(nullptr), tail(nullptr), size(0)
{
    for (auto &node: list)
        this->push_tail(node);
}

template<typename T>
List<T>::List(std::iterator<std::input_iterator_tag, T> beg, std::iterator<std::input_iterator_tag, T> end)
{
    if (beg.is_invalid() || end.is_invalid()())
        throw Iterator_exception(__FILE__,typeid(*this).name(), get_time());

    for (auto curr = beg; curr != end; ++curr)
        this->push_tail(*curr);
}

//Заприваченые
template<typename T>
std::shared_ptr<List_node<T>> List<T>::node_init(const T& data, std::shared_ptr<List_node<T>> next)
{
    std::shared_ptr<List_node<T>> node = std::make_shared<List_node<T>>();
    node->set_data(data);
    node->set_next(next);
    return node;
}

template<typename T>
void List<T>::list_concat(const List<T> &list)
{
    if (list.is_empty())
        return ;

    T data = list.head->get_data_value();
    std::shared_ptr<List_node<T>> next = list.head->get_next();
    std::shared_ptr<List_node<T>> elem = node_init(data, next);
    std::shared_ptr<List_node<T>> curr = this->head;

    if (this->is_empty())
    {
        curr = elem;
        this->head = elem;
    }
    else
    {
        for(; curr->get_next(); curr = curr->get_next());

        curr->set_next(elem);
        curr = curr->get_next();
    }

    std::shared_ptr<List_node<T>> new_elem = next;
    for (; new_elem; new_elem = new_elem->get_next(), curr = curr->get_next())
    {
        data = new_elem->get_data_value();
        next = new_elem->get_next();
        elem = node_init(data, next);
        curr->set_next(elem);
        this->size++;
    }
    this->tail = elem;
}

template<typename T>
bool List<T>::nodes_cmp(const List<T> &list) const
{
    std::shared_ptr<List_node<T>> initial = this->head;
    std::shared_ptr<List_node<T>> given = list.head;
    for (; initial && given && (initial->get_data() == given->get_data()); initial = initial->get_next(), given = given->get_next());

    if (initial == nullptr && given == nullptr)
        return true;
    return false;
}
//Публики
template<typename T>
Iterator<T> List<T>::find(Iterator<T> beg, Iterator<T> end, const T &value)
{
    if (beg.is_invalid() || end.is_invalid())
        throw Iterator_exception(__FILE__, typeid(List).name(), get_time());

    for (;beg != end; end++)
        if (*beg == value)
            return beg;
    return end;
}

template<typename T>
void List<T>::clear()
{
    this->head = nullptr;
    this->tail = nullptr;
    this->size = 0;
}


template<typename T>
Iterator<T> List<T>::add_list(List<T> &list)
{
    if (list.is_empty())
        return this->end();

    if (this == &list)
    {
        List<T> copy;
        copy = list;
        this->list_concat(copy);
    }

    else
    {
        this->list_concat(list);
    }
    return this->end();
}

template<typename T>
Iterator<T> List<T>::push_tail(const T &data)
{
    std::shared_ptr<List_node<T>> node = node_init(data);
    if (this->is_empty())
    {
        this->head = node;
        this->tail = node;
    }
    else
    {
        this->tail->set_next(node);
    }
    this->tail = node;
    this->size++;
    return this->end();
}

template<typename T>
T List<T>::pop_tail()
{
    if (this->is_empty())
        throw Empty_list_exception(__FILE__, typeid(*this).name(), get_time());
    Iterator<T> iter = this->end();
    return this->remove(iter);
}

template<typename T>
Iterator<T> List<T>::push_head(const T &data)
{
    std::shared_ptr<List_node<T>> node = node_init(data);
    if (this->is_empty())
    {
        this->head = node;
        this->tail = node;
    }
    else
    {
        node->set_next(this->head);
        this->head = node;
    }
    this->size++;
    return this->begin();
}

template<typename T>
T List<T>::pop_head()
{
    if (this->is_empty())
        throw Empty_list_exception(__FILE__, typeid(*this).name(), get_time());
    Iterator<T> iter = this->begin();
    return this->remove(iter);
}

template<typename T>
Iterator<T> List<T>::merge(const List<T> &list)
{
    if (list.is_empty())
        return this->begin();

    this->list_concat(list);
    return this->begin();
}

template<typename T>
Iterator<T> List<T>::insert_before(const Iterator<T> &iterator, const T &data)
{
    if (iterator.is_invalid())
        throw Iterator_exception(__FILE__, typeid(*this).name(), get_time());

    std::shared_ptr<List_node<T>> curr = this->head;
    std::shared_ptr<List_node<T>> prev = nullptr;
    Iterator<T> curr_iter = this->begin();

    if ((this->head == nullptr && this->tail == nullptr) && curr_iter == iterator)
    {
        std::shared_ptr<List_node<T>> node = node_init(data);
        this->head = node;
        this->tail = node;
        this->size++;
        return this->begin();
    }

    for (;curr && curr_iter != iterator; prev = curr, curr = curr->get_next(), curr_iter++);

    if (curr_iter != iterator)
        throw Iterator_exception(__FILE__, typeid(*this).name(), get_time());


    std::shared_ptr<List_node<T>> node = node_init(data, curr);
    if(curr = this->head)
        this->head = node;
    else
        prev->set_next(node);

    return Iterator<T>(node);
}

template<typename T>
Iterator<T> List<T>::insert_before(const Iterator<T> &iterator, const List<T> &list)
{
    if (iterator.is_invalid())
    {
        throw Iterator_exception(__FILE__, typeid(*this).name(), get_time());
    }
    Iterator<T> insert_iterator = this->end();
    if (this->is_empty())
    {
        this->list_concat(list);
    }
    else
    {
        Iterator<T> curr = this->begin();
        Iterator<T> end = this->end();
        if (!this->contains(iterator))
        {
            throw List_index_exception(__FILE__, typeid(*this).name, get_time());
        }

        for (size_t i = 0; i < list.size; i++)
            insert_iterator = this->insert_before(iterator, list[i]);

    }
    return insert_iterator;
}

template<typename T>
T List<T>::remove(const Iterator<T> &iterator)
{

    if (this->is_empty())
        throw Empty_list_exception(__FILE__, typeid(*this).name(), get_time());

    if (iterator.is_invalid())
        throw Iterator_exception(__FILE__, typeid(*this).name(), get_time());

    std::shared_ptr<List_node<T>> cur = this->head;
    std::shared_ptr<List_node<T>> prev = nullptr;
    Iterator<T> cur_iter = this->begin();

    for (; cur && cur_iter != iterator; prev = cur, cur = cur->get_next(), cur_iter.next());


    if (cur == nullptr)
        throw List_index_exception(__FILE__, typeid(*this).name(), get_time());

    T data = *iterator;

    if (cur == this->tail)
        this->tail = prev;
    else if (cur == this->head)
        this->head = cur->get_next();
    else
        prev->set_next(cur->get_next());

    this->size--;

    return data;

}

template<typename T>
T* List<T>::to_array(size_t &size)
{
    size = 0;
    Iterator<T> beg = this->begin();
    Iterator<T> end = this->end();

    T *arr = nullptr;
    if (beg.is_invalid() || end.is_invalid())
        return arr;
    else
    {
        arr = new T[this->size];
        size_t i = 0;
        for (Iterator<T> curr = beg; curr != end; curr++)
        {
            size++;
            arr[i] = *curr;
        }
    }
    return arr;
}

template<typename T>
std::forward_list<T> &List<T>::to_forward_list()
{
    std::forward_list<T> list;
    Iterator<T> beg = this->begin();
    Iterator<T> end = this->end();
    if (beg.expired() || end.expired())
        return list;

    for (Iterator<T> curr = beg; curr != end; curr++)
        list.push_front(*curr);

    return list;
}

template<typename T>
Iterator<T> List<T>::begin() const
{
    return Iterator<T>(this->head);
}

template<typename T>
Const_iterator<T> List<T>::cbegin() const
{
    return Const_iterator<T>(this->head);
}

template<typename T>
Iterator<T> List<T>::end() const
{
    return Iterator<T>(this->tail);
}

template<typename T>
Const_iterator<T> List<T>::cend() const
{
    return Const_iterator<T>(this->tail);
}

template<typename T>
bool List<T>::cycle_check() const
{
    Iterator<T> slow_step = this->begin();
    Iterator<T> fast_step = this->begin();
    for (; !fast_step.is_invalid() && !slow_step.is_invalid(); fast_step++, slow_step += 2)
        if (fast_step == slow_step)
            return true;
    return false;
}

template<typename T>
void List<T>::apply(void (*func) (T&))
{
    Iterator<T> beg = this->begin();
    Iterator<T> end = this->end();
    for (Iterator<T> curr = beg; curr != end; curr++)
        func(*curr);
}

template<typename T>
bool List<T>::contains(const Iterator<T> &iter) const
{
    if (iter.is_invalid())
        return false;

    Iterator<T> curr = this->begin();
    Iterator<T> end = this->end();

    for(; curr != iter & curr != end; curr++);

    if (curr != iter)
        return false;
    return true;
}

template<typename T>
Iterator<T> List<T>::operator += (const T &data)
{
    return this->push_tail(data);
}

template<typename T>
bool List<T>::operator == (const List<T> &list) const
{
    return this->nodes_cmp(list);
}

template<typename T>
List<T> &List<T>::operator = (const List<T> &list)
{
    if (this != &list)
    {
        this->clear();
        this->list_concat(list);
    }
    return *this;
}

template<typename T>
List<T> &List<T>::operator = (const std::initializer_list<T> &list)
{
    this->clear();
    List<T> tmp = &List(list);
    this->list_concat(tmp);
    return *this;
}

template<typename T>
List<T> &List<T>::operator = (const std::forward_list<T> &list)
{
    this->clear();
    List<T> tmp = List(list);
    this->list_concat(tmp);
    return *this;
}

template<typename T>
List<T> &List<T>::operator = (List<T> &&list)
{
    this->size = list.size;
    this->head = list.head;
    this->tail = list.tail;
    return *this;
}


template<typename T>
List<T> &List<T>::operator + (const List<T> &list)
{
    List<T> result;
    result.list_concat(*this);
    result.list_concat(list);
    return result;
}

template<typename T>
List<T> &List<T>::operator + (const T data)
{
    List<T> tmp = *this;
    tmp.push_tail(data);
    return *tmp;
}

template<typename T>
T &List<T>::operator [](const size_t index)
{
    if (this->size < index)
    {
        throw List_index_exception(__FILE__, typeid(*this).name(), get_time());
    }

    Iterator<T> curr = this->begin();
    for (size_t i = 0; i < index; i++, curr++);

    return *curr;
}

template <typename T>
void List<T>::list_cout() const
{
    std::cout << "LIST: ";
    Const_iterator<T> iter = this->cbegin();
    if (!iter.is_invalid())
        std::cout << "EMPTY";
    else
    {
        for (; iter.is_invalid(); iter.next())
            std::cout << " " << *iter;
    }
    std::cout << std::endl;
}

//new
template <typename T>
Iterator<T> List<T>::insert_after(const Iterator<T> &iterator, const T &data)
{
    if (iterator.is_invalid() || !this->contains(iterator))
        throw Iterator_exception(__FILE__, typeid(*this).name(), get_time());

    std::shared_ptr<List_node<T>> curr = this->head;
    Iterator<T> beg = this->begin();
    for( ;beg != iterator; beg++, curr = curr->get_next());

    std::shared_ptr<List_node<T>> node;
    if (beg == this->end())
    {
        node = node_init(data);
        this->tail = node;
    }
    else
        node = node_init(data, curr->get_next());
    curr->set_next(node);
    return beg;
}

template <typename T>
Iterator<T> List<T>::insert_after(const Iterator<T> &iterator, const List<T> &list)
{
    if (iterator.is_invalid()||!this->contains(iterator))
    {
        throw Iterator_exception(__FILE__, typeid(*this).name(), get_time());
    }
    Iterator<T> insert_iterator = this->end();
    if (this->is_empty())
    {
        this->list_concat(list);
    }
    else
    {
        Iterator<T> curr = this->begin();
        Iterator<T> end = this->end();
        for (size_t i = 0; i < list.size; i++)
            insert_iterator = this->insert_after(iterator, list[i]);

    }
    return insert_iterator;
}

template <typename T>
Iterator<T> List<T>::find_last(Iterator<T> beg, Iterator<T> end, const T &data)
{
    if (beg.expired() || end.expired())
        throw Iterator_exception(__FILE__, typeid(List).name(), get_time());

    Iterator<T> ans = this->end();
    for (;beg != end; end++)
        if (*beg == data)
            ans = beg;
    return ans;
}

template <typename T>
bool List<T>::contains(const T &data) const
{
    Iterator<T> end = this->end();
    for (Iterator<T> curr = this->begin(); curr != end; curr++)
        if (*curr == data)
            return true;
    return false;
}

template <typename T>
bool List<T>::contains_all(std::initializer_list<T> &data) const
{
    for(auto elem: data)
        if (!this->contains(elem))
            return false;
    return true;
}

template <typename T>
bool List<T>::contains_all(List<T> &list) const
{
    for(auto elem: list)
        if (!this->contains(elem))
            return false;
    return true;
}

template <typename T>
bool List<T>::contains_all(Iterator<T> beg, Iterator<T> end) const
{
    for(Iterator<T> curr = beg; curr != end; curr++)
        if (!this->contains(curr))
            return false;
    return true;
}

template <typename T>
List<T> &List<T>::slice(Iterator<T> beg, Iterator<T> end) //меняет исходный, возвращает новый
{
    if (!this->contains(beg) || !this->contains(end))
        throw List_index_exception(__FILE__, typeid(*this).name(), get_time());

    List<T> _new;
    for(Iterator<T> curr = beg; curr != end; curr++)
        _new.push_tail(this->remove(curr));

    return _new;
}

template <typename T>
List<T> &List<T>::sub_list(Iterator<T> beg, Iterator<T> end) const // не меняет исходный, возвращает новый
{ 
    if (!this->contains(beg) || !this->contains(end))
    {
        throw List_index_exception(__FILE__, typeid(*this).name(), get_time());
    }
    List<T> _new;
    for(Iterator<T> curr = beg; curr != end; curr++)
        _new.push_tail(*curr);

    return _new;
}

template <typename T>
Iterator<T> List<T>::reverse()
{
    std::shared_ptr<List_node<T>> curr = this->head;
    std::shared_ptr<List_node<T>> prev = nullptr, next = nullptr;
    while(curr != nullptr)
    {
        next = curr->get_next();
        curr->set_next(prev);
        prev = curr;
        curr = next;
    }
    this->head = prev;
    return Iterator<T>(prev);
}

template <typename T>
List<T> &List<T>::reversed() const
{
    List<T> _new = *this;
    _new.reverse();
    return _new;
}

template <typename T>
size_t List<T>::index(const T &data) const
{
    Iterator<T> beg = this->begin();
    Iterator<T> end = this->end();
    size_t cnt = 0;
    for(; beg != end; beg++, cnt++)
        if (*beg == data)
            return cnt;
    throw List_index_exception(__FILE__, typeid(*this).name(), get_time());
}

template <typename T>
size_t List<T>::index(const Iterator<T> &iter) const
{
    Iterator<T> beg = this->begin();
    Iterator<T> end = this->end();
    size_t cnt = 0;
    for(; beg != end; beg++, cnt++)
        if (beg == iter)
            return cnt;
    throw List_index_exception(__FILE__, typeid(*this).name(), get_time());
}

template <typename T>
size_t List<T>::index_last(const T &data) const
{
    Iterator<T> beg = this->begin();
    Iterator<T> end = this->end();
    size_t cnt = 0, ans = 0;
    for(; beg != end; beg++, cnt++)
        if (*beg == data)
            ans = cnt;
    return ans;
}

template <typename T>
size_t List<T>::index_last(const Iterator<T> &iter) const
{
    Iterator<T> beg = this->begin();
    Iterator<T> end = this->end();
    size_t cnt = 0, ans = 0;
    for(; beg != end; beg++, cnt++)
        if (beg == iter)
            ans = cnt;
    return ans;
}

template <typename T>
void List<T>::replace(const T &data, const T &replacement)
{
    std::shared_ptr<List_node<T>> beg = this->head;
    std::shared_ptr<List_node<T>> end = this->tail;
    for(; beg != end; beg = beg->get_next())
        if(beg->get_data() == data)
            beg->set_data(replacement);
}

template <typename T>
Iterator<T> List<T>::min() const
{
    Iterator<T> ans = this->begin();
    Iterator<T> beg = this->begin();
    Iterator<T> end = this->end();
    for(;beg != end; beg++)
        if (*beg < *ans)
            ans = beg;
    return ans;
}

template <typename T>
Iterator<T> List<T>::max() const
{
    Iterator<T> ans = this->begin();
    Iterator<T> beg = this->begin();
    Iterator<T> end = this->end();
    for(;beg != end; beg++)
        if (*beg > *ans)
            ans = beg;
    return ans;
}

template <typename T>
Iterator<T> List<T>::operator += (const List<T> &list)
{
    this->merge(list);
    return this->end();
}

#endif
