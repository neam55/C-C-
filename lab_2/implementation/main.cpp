#include <iostream>
#include <chrono>
#include <ctime>
#include"list.h"
#include"list_node.h"
#include"iterator.h"
#include"const_iterator.h"
#include"exceptions.h"

template <typename T>
void increment(T& num)
{
    num++;
}

template <typename T>
void print(T& num)
{
    std::cout << num << " ";
}

using namespace std;
int main(void)
{
    try
    {
        //Конструкторы
        List<int> list1;
        std::initializer_list<int> asf = {1, 2, 3};
        int arr[10] = {1, 2, 3, 4, 5};
        std::forward_list<int> fl = {1, 2, 3, 4, 5};
        List<int> list2(asf), list3(arr,3);
        std::cout << "list1 " << list1 << std::endl;
        std::cout << "list2 " << list2 << std::endl;
        std::cout << "list3 " << list3 << std::endl;
        List<int> list_ist(list2), list_ist2(fl);
        std::cout << list_ist << std::endl;
        size_t size = 3;
        int *arr2 = list3.to_array(size);
        for (size_t i = 0; i < size; i++)
            std::cout << arr2[i] << " ";
        std::cout << std::endl;
        delete[] arr2;
        std::forward_list<int> out = list_ist2.to_forward_list();
        std::cout << out << std::endl;
        delete out;

        //остальное
        List<int> list4;
        std::cout << "list4 " << list4 << std::endl;
        list4.push_tail(1);
        list4.push_head(2);
        list4.push_tail(3);
        list4.push_head(4);
        list4.push_tail(5);
        list4.push_head(6);
        std::cout << "list4 " << list4 << std::endl;
        list4.remove(list4.begin());
        std::cout << "list4 " << list4 << std::endl;
        list4.replace(2, 12);
        std::cout << "list4 " << list4 << std::endl;
        list4.insert_after(list4.begin(), 10);
        list4.insert_before(list4.begin(), 11);
        std::cout << "list4 " << list4 << std::endl;
        list4.pop_head();
        list4.pop_tail();
        std::cout << list4.contains(3) << std::endl;
        std::cout << list4.contains_all(asf) << std::endl;
        std::cout << "reverse: "<<list4.reverse() << std::endl;
        List<int> bin(asf), bin_01, bin_02;
        bin.list_cout();
        bin.push_tail(4);
        bin.push_tail(4);
        bin.push_tail(4);
        bin.push_tail(4);
        Iterator<int> beg = bin.begin();
        Iterator<int> end = bin.begin();
        end = end + 3;
        std::cout << "source: " << bin << std::endl;
        bin_01 = bin.sub_list(beg, end);
        std::cout << "source: " << bin << std::endl;
        std::cout << "result: " << bin_01 << std::endl;
        bin_02 = bin.slice(beg, end);
        std::cout << "source: " << bin << std::endl;
        std::cout << "result: " << bin_02 << std::endl;

        list_f.apply(increment);
        list_f.apply(print);

        //поиск и типа того
        std::initializer_list<int> asf1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1};
        List<int> list_f(asf1);
        Iterator<int> _F = list_f.find(list_f.begin(), list_f.end(), 1);
        Iterator<int> _L = list_f.find_last(list_f.begin(), list_f.end(), 1);
        std::cout << _F == _L << std::endl;
        std::cout << "first occurence: " << *_F << std::endl;
        std::cout << "last_occurenece: " << *_L << std::endl;
        std::cout << list_f.index(1) << std::endl;
        std::cout << list_f.index_last(1) << std::endl;



        //операторы и связаные с ними функции
        std::cout << "list4 " << list4 << std::endl;
        list4 += 1;
        list4 += list1;
        std::cout << "list4 " << list4 << std::endl;
        list4.merge(list3);
        std::cout << "list4 " << list4 << std::endl;
        List<int> list5, list6 = asf;
        list5 = list2 + list3;
        std::cout << "list5 " << list5 << std::endl;
        std::cout << "list6[1]" << list6[1]<< std::endl;
    }
    catch (Base_exception &error)
    {
        std::cout << error.what() << std::endl;
    }
}
