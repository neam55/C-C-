#ifndef BASE_ITERATOR_H
#define BASE_ITERATOR_H

class Base_iterator
{
public:
    virtual ~Base_iterator() = default;

    virtual bool is_invalid() const = 0;
};

#endif // BASE_ITERATOR_H
