#pragma once
#ifndef KLANG_HEAD_LIST
#define KLANG_HEAD_LIST

#include "KLang/Array.h"

namespace KLang
{
    template<typename T>
    class List
    {
    private:
        uint32_t _offset;
        Array<T> _data;
    public:
        List();
        List(uint32_t initialSize);
        List(std::initializer_list<T> items);
        List(List<T>& other);
        ~List();

        uint32_t Length();
        T& operator[] (uint32_t idx);
        uint32_t IndexOf(T& item);

        void Add(T& item);
        bool Remove(T& item);
        bool Contains(T& item);

        void Clear();

        T& First();
        T& Last();
    };

    template<typename T>
    List<T>::List() : _offset(0), _data(32) { }

    template<typename T>
    List<T>::List(uint32_t initialSize) : _offset(0),  _data(initialSize) { }

    template<typename T>
    List<T>::List(std::initializer_list<T> items) : _offset(0),  _data(items.size())
    {
        int length = _data.Length();
        for (int i = 0; i < length; i++)
            _data[i] = items[i];
        _offset = length;
    }

    template<typename T>
    List<T>::List(List<T>& other) : _offset(0)
    {
        _data = other._data.Clone();
    }

    template<typename T>
    List<T>::~List()
    {
        Clear();
    }

    template<typename T>
    uint32_t List<T>::Length()
    {
        return _offset;
    }

    template<typename T>
    T& List<T>::operator[] (uint32_t idx)
    {
        return _data[idx];
    }

    template<typename T>
    uint32_t List<T>::IndexOf(T& item)
    {
        for (int i = 0; i < _offset; i++)
        {
            if (_data[i] == item)
                return i;
        }
        return -1;
    }

    template<typename T>
    void List<T>::Add(T& item)
    {
        _data[_offset] = item;
        if (_offset >= _data.Length())
            _data.Resize(_data.Length() * 2);
    }

    template<typename T>
    bool List<T>::Remove(T& item)
    {
        int i = IndexOf(item);
        if (i < 0) return false;

        for (; i < _offset - 2; i++)
            _data[i] = _data[i + 1];
        _offset--;

        // Should we do it? I thing so...
        _data[_offset].~T();

        return true;
    }

    template<typename T>
    bool List<T>::Contains(T& item)
    {
        return 0 <= IndexOf(item);
    }

    template<typename T>
    void List<T>::Clear()
    {
        for (uint32_t i = 0; i < _offset; i++)
            _data[i].~T();
        _offset = 0;
    }

    template<typename T>
    T& List<T>::First()
    {
        if (_offset == 0)
        {
            // No data here!
            throw OutOfRangeException("List is empty!");
        }
        return _data[0];
    }

    template<typename T>
    T& List<T>::Last()
    {
        if (_offset == 0)
        {
            // No data here!
            throw OutOfRangeException("List is empty!");
        }
        return _data[_offset-1];
    }
}

#endif // !KLANG_HEAD_LIST
