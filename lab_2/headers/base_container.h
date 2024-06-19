#ifndef BASE_CONTAINER_H
#define BASE_CONTAINER_H

class Base_container
{

public:
    virtual size_t get_size() const noexcept
    {
        return this->size;
    }

    virtual bool is_empty() const noexcept
    {
        return size == 0;
    }

    virtual void clear();

    virtual  ~Base_container() = default;

protected:
    size_t size = 0;
};


#endif // BASE_CONTAINER_H
