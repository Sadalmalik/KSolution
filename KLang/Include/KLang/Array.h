#pragma once
#ifndef KLANG_HEAD_data
#define KLANG_HEAD_data

#include <atomic>

#include "Types.h"
#include "Exceptions.h"

namespace KLang
{
    template<typename T>
    class Array;

    template<typename T>
    class ArrayObject
    {
    private:
        std::atomic<uint32_t> _counter;
        uint32_t _length;
        T* _data;

        ArrayObject(uint32_t length);

        friend class Array<T>;
    };

    template<typename T>
    ArrayObject<T>::ArrayObject(uint32_t length) : _counter(0), _length(length), _data((T*) (this+1))
    {
    }

    // Actually this is Facade
    template<typename T>
    class Array
    {
    private:
        ArrayObject<T> * _object;

    public:
        Array();
        Array(uint32_t length);
        Array(Array& other);
        Array(const Array& other);
        ~Array();

        uint32_t Length();

        T& operator[] (uint32_t idx);

        bool operator== (Array& other);
        bool operator== (Array<T>* other);
    };

    template<typename T>
    Array<T>::Array()
    {
        _object = nullptr;
    }

    template<typename T>
    Array<T>::Array(uint32_t length)
    {
        _object = (ArrayObject<T>*) new byte[sizeof(ArrayObject<T>) + length * sizeof(T)];

        new (_object) ArrayObject<T>(length);
        _object->_counter = 1;

        for (uint32_t i = 0; i < length; i++)
        {
            new (&_object->_data[i]) T();
        }
    }

    template<typename T>
    Array<T>::Array(Array& other)
    {
        _object = other._object;
        if (_object != nullptr)
            _object->counter++;
    }

    template<typename T>
    Array<T>::Array(const Array& other)
    {
        _object = other._object;
        if (_object != nullptr)
            _object->counter++;
    }

    template<typename T>
    Array<T>::~Array()
    {
        if (_object == nullptr)
            return;

        _object->_counter--;

        if (_object->_counter == 0)
        {
            for (uint32_t i = 0; i < _object->_length; i++)
            {
                _object->_data[i].~T();
            }

            delete[](byte*)_object;
        }
    }

    template<typename T>
    uint32_t Array<T>::Length()
    {
        if (_object == nullptr)
            throw NullPointerException("NullPointerException: Array is null!\n");
        return _object->_length;
    }

    template<typename T>
    T& Array<T>::operator[] (uint32_t idx)
    {
        if (_object == nullptr)
            throw NullPointerException("NullPointerException: Array is null!\n");
        if (idx < 0 || idx > _object->_length)
            // TODO: String formatting
            throw OutOfRangeException("OutOfRangeException: Array index must be in range 0 {_length} but it is {idx}\n");
        return _object->_data[idx];
    }

    template<typename T>
    bool Array<T>::operator== (Array& other)
    {
        return _object == other._object;
    }

    template<typename T>
    bool Array<T>::operator== (Array<T> *other)
    {
        if (this == other)
            return true;
        if (other == nullptr) // Feel suspect, but at same time feel like it should be like this... It allow us to compare with nullptr
            return _object == nullptr;
        return _object == other->_object;
    }
}

#endif // KLANG_HEAD_data