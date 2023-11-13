#pragma once
#ifndef KLANG_HEAD_ARRAY
#define KLANG_HEAD_ARRAY

#include <atomic>
#include <initializer_list>

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

        inline void ClearArrayObject();
        inline void NullCheck();
    public:
        Array();
        Array(uint32_t length);
        Array(std::initializer_list<T> items);
        Array(const Array& other);
        Array(const Array* other);
        ~Array();

        Array Clone();
        void Clear();

        uint32_t Length();
        const T* RawArray();
        Array<T> Resized(uint32_t newLength);
        void Resize(uint32_t newLength);

        T& operator[] (uint32_t idx);

        void operator= (Array& other);
        void operator= (const Array& other);
        void operator= (const Array* other);

        bool operator== (const Array& other);
        bool operator== (const Array* other);

        Array<T> operator+ (Array<T>&other);
    };

    template<typename T>
    inline void Array<T>::NullCheck()
    {
        if (_object == nullptr)
            throw NullPointerException("NullPointerException: Array is null!\n");
    }

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
    Array<T>::Array(std::initializer_list<T> items)
    {
        uint32_t length = (uint32_t) items.size();
        _object = (ArrayObject<T>*) new byte[sizeof(ArrayObject<T>) + length * sizeof(T)];

        new (_object) ArrayObject<T>(length);
        _object->_counter = 1;

        uint32_t i = 0;
        auto end = items.end();
        for (auto iter = items.begin(); iter != end; iter++, i++)
        {
            new (&_object->_data[i]) T();
            _object->_data[i] = *iter;
        }
    }

    template<typename T>
    Array<T>::Array(const Array& other)
    {
        _object = other._object;
        if (_object != nullptr)
            _object->_counter++;
    }

    template<typename T>
    Array<T>::Array(const Array* other)
    {
        if (other == nullptr)
        {
            _object = nullptr;
            return;
        }
        _object = other->_object;
        if (_object != nullptr)
            _object->_counter++;
    }

    template<typename T>
    Array<T>::~Array()
    {
        ClearArrayObject();
    }

    template<typename T>
    Array<T> Array<T>::Clone()
    {
        uint32_t length = Length();
        Array<T> newArray(length);
        for (uint32_t i = 0; i < length; i++)
            newArray[i] = this[i];
        return newArray;
    }

    template<typename T>
    void Array<T>::Clear()
    {
        for (uint32_t i = 0; i < _object->_length; i++)
        {
            _object->_data[i].~T();
        }
    }

    template<typename T>
    void Array<T>::ClearArrayObject()
    {
        if (_object == nullptr)
            return;

        _object->_counter--;

        if (_object->_counter == 0)
        {
            Clear();
            delete[](byte*)_object;
        }

        _object = nullptr;
    }

    template<typename T>
    uint32_t Array<T>::Length()
    {
        NullCheck();
        return _object->_length;
    }

    template<typename T>
    const T* Array<T>::RawArray()
    {
        NullCheck();
        return _object->_data;
    }

    template<typename T>
    Array<T> Array<T>::Resized(uint32_t newLength)
    {
        NullCheck();
        Array<T> newArray(newLength);
        uint32_t minLength = Length();
        if (minLength > newLength)
            minLength = newLength;
        for (uint32_t i = 0; i < minLength; i++)
            newArray[i] = (*this)[i];
        return newArray;
    }

    template<typename T>
    void Array<T>::Resize(uint32_t newLength)
    {
        NullCheck();
        *this = Resized(newLength);
    }

    template<typename T>
    T& Array<T>::operator[] (uint32_t idx)
    {
        NullCheck();
        if (idx < 0 || idx > _object->_length)
            // TODO: String formatting
            throw OutOfRangeException("OutOfRangeException: Array index must be in range 0 {_length} but it is {idx}\n");
        return _object->_data[idx];
    }

    template<typename T>
    void Array<T>::operator= (const Array<T>& other)
    {
        ClearArrayObject();
        _object = other._object;
        if (_object != nullptr)
            _object->_counter++;
    }

    template<typename T>
    void Array<T>::operator= (Array<T>& other)
    {
        ClearArrayObject();
        _object = other._object;
        if (_object != nullptr)
            _object->_counter++;
    }

    template<typename T>
    void Array<T>::operator= (const Array<T>* other)
    {
        ClearArrayObject();
        _object = other==nullptr ? nullptr : other._object;
        if (_object != nullptr)
            _object->_counter++;
    }

    template<typename T>
    bool Array<T>::operator== (const Array<T>& other)
    {
        return _object == other._object;
    }

    template<typename T>
    bool Array<T>::operator== (const Array<T> *other)
    {
        if (this == other)
            return true;
        if (other == nullptr) // Feel suspect, but at same time feel like it should be like this... It allow us to compare with nullptr
            return _object == nullptr;
        return _object == other->_object;
    }

    template<typename T>
    Array<T> operator+ (Array<T>& other)
    {
        Array<T>&a = *this;
        Array<T>&b = other;
        uint32_t aLen = a.Length();
        uint32_t bLen = b.Length();
        uint32_t size = aLen + bLen;
        Array<T> sum(size);

        uint32_t i = 0;
        for (; i < aLen; i++) sum[i] = a[i];
        for (; i < size; i++) sum[i] = b[i - aLen];
        return sum;
    }
}

#endif // KLANG_HEAD_ARRAY