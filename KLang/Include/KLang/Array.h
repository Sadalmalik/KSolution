#pragma once
#ifndef KLANG_HEAD_ARRAY
#define KLANG_HEAD_ARRAY

#include "Types.h"
#include "Exceptions.h"

namespace KLang
{
    template<typename T>
    class Array
    {
    private:
        uint32_t _len;
        T* _array;

        inline Array() : _len(0), _array(nullptr) {};
    public:
        int Length();

        T& operator[] (uint32_t idx);
        T& At(uint32_t idx);

        static Array* New(uint32_t length);
        static void Del(Array*arr);
    };

    template<typename T>
    int Array<T>::Length()
    {
        return this->_len;
    }

    template<typename T>
    T& Array<T>::operator[] (uint32_t idx)
    {
        if (idx < 0 || idx > _len)
            // TODO: String formatting
            throw OutOfRangeException("OutOfRangeException: Array index must be in range 0 {_len} but it is {idx}");
        return this->_array[idx];
    }

    template<typename T>
    T& Array<T>::At (uint32_t idx)
    {
        if (idx < 0 || idx > _len)
            // TODO: String formatting
            throw OutOfRangeException("OutOfRangeException: Array index must be in range 0 {_len} but it is {idx}");
        return this->_array[idx];
    }

    template<typename T>
    Array<T>* Array<T>::New(uint32_t length)
    {
        Array* array = (Array*) new byte[sizeof(Array) + length * sizeof(T)];
        array->_len = length;
        array->_array = (T*)(array + 1);

        for (uint32_t i = 0; i < length; i++)
        {
            new (&array->_array[i]) T();
        }

        return array;
    }

    template<typename T>
    void Array<T>::Del(Array<T>* array)
    {
        for (uint32_t i = 0; i < array->_len; i++)
        {
            array->_array[i].~T();
        }

        delete[](byte*)array;
    }
}

#endif // KLANG_HEAD_ARRAY