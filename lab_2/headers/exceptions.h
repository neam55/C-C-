#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include<exception>
#include<chrono>
#include<ctime>
#include <memory>
#include <set>
#include<string.h>


uint64_t get_time()
{
    return duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

class Base_exception : public std::exception
{

public:
    explicit Base_exception(const char *filename, const char *class_name, uint64_t time, const char * error_prompt)
    {
        strcpy_s(message, filename);
        strcat_s(message, class_name);
        strcat_s(message, error_prompt);
    }
    [[nodiscard]]const char *what() const noexcept override
    {
        return message;
    }

private:
    char message[256];
};


class Memory_exception : public Base_exception
{
    Memory_exception(
        const char *filename,
        const char *class_name,
        uint64_t time,
        const char *error_prompt = "Memory allocation error.\n"):
        Base_exception(filename, class_name, time, error_prompt){}
};

class Iterator_exception : public Base_exception
{
    Iterator_exception(
        const char *filename,
        const char *class_name,
        uint64_t time,
        const char *error_prompt = "Invalid iterator error.\n"):
        Base_exception(filename, class_name, time, error_prompt){}
};

class Pointer_exception : public Base_exception
{
    Pointer_exception(
        const char * filename,
        const char * class_name,
        uint64_t time,
        const char * error_prompt = "Invalid pointer error.\n"):
        Base_exception(filename, class_name, time, error_prompt){}
};

class Empty_list_exception : public Base_exception
{
    Empty_list_exception(
        const char *filename,
        const char *class_name,
        uint64_t time,
        const char *error_prompt = "Operation performed on an empty list.\n"):
        Base_exception(filename, class_name, time, error_prompt){}
};


class List_index_exception : public Base_exception
{
    List_index_exception(
        const char *filename,
        const char *class_name,
        uint64_t time,
        const char *error_prompt = "List index is out of range.\n"):
        Base_exception(filename, class_name, time, error_prompt){}
};



#endif
