#pragma once
#ifndef KLANG_HEAD_LIST
#define KLANG_HEAD_LIST

#include "KLang/Array.h"

namespace KLang
{
    template<typename T>
    class ListObject
    {
    private:
        std::atomic<uint32_t> _counter;
        uint32_t _offset;
        Array<T> _data;
    };

    template<typename T>
    class List
    {
    private:
        ListObject<T>* _object;

    public:
        List();
        List(uint32_t initialSize);
        List(std::initializer_list<T> items);
        List(List<T>& other);
        List(const List<T>& other);
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
    List<T>::List()
    {
        _object = new ListObject<T>();
        _object->_counter = 1;
        _object->_offset = 0;
        _object->_data = Array<T>(32);
    }

    template<typename T>
    List<T>::List(uint32_t initialSize)
    {
        _object = new ListObject<T>();
        _object->_counter = 1;
        _object->_offset = 0;
        _object->_data = Array<T>(initialSize);
    }

    template<typename T>
    List<T>::List(std::initializer_list<T> items)
    {
        uint32_t size = items.size();

        _object = new ListObject<T>();
        _object->_counter = 1;
        _object->_offset = 0;
        _object->_data = Array<T>(size);

        for (int i = 0; i < size; i++)
            _data[i] = items[i];
        _offset = size;
    }

    template<typename T>
    List<T>::List(List<T>& other) : _offset(0)
    {
        _object = new ListObject<T>();
        _object->_counter = 1;
        _object->_offset = 0;
        _object->_data = other._data.Clone();
    }

    template<typename T>
    List<T>::List(const List<T>& other) : _offset(0)
    {
        _object = new ListObject<T>();
        _object->_counter = 1;
        _object->_offset = 0;
        _object->_data = other._data.Clone();
    }

    template<typename T>
    List<T>::~List()
    {
        if (_object == nullptr)
            return;
        _object->_data.Clear();
    }

    template<typename T>
    uint32_t List<T>::Length()
    {
        if (_object == nullptr)
            throw NullPointerException();
        return _object->_offset;
    }

    template<typename T>
    T& List<T>::operator[] (uint32_t idx)
    {
        if (_object == nullptr)
            throw NullPointerException();
        return _object->_data[idx];
    }

    template<typename T>
    uint32_t List<T>::IndexOf(T& item)
    {
        if (_object == nullptr)
            throw NullPointerException();
        Array<T> temp = _object->_data;
        for (int i = 0; i < _offset; i++)
        {
            if (temp[i] == item)
                return i;
        }
        return -1;
    }

    template<typename T>
    void List<T>::Add(T& item)
    {
        if (_object == nullptr)
            throw NullPointerException();
        _object->_data[_offset] = item;
        uint32_t length = _object->_data.Length();
        if (_object->_offset >= length)
            _object->_data.Resize(length * 2);
    }

    template<typename T>
    bool List<T>::Remove(T& item)
    {
        if (_object == nullptr)
            throw NullPointerException();

        int i = IndexOf(item);
        if (i < 0) return false;

        Array<T> temp = _object->_data;
        for (; i < _offset - 2; i++)
            temp[i] = temp[i + 1];
        _offset--;

        // Should we do it? I thing so...
        temp[_offset].~T();

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
        if (_object == nullptr)
            throw NullPointerException();
        Array<T> temp = _object->_data;
        for (uint32_t i = 0; i < _offset; i++)
            temp[i].~T();
        _offset->_offset = 0;
    }

    template<typename T>
    T& List<T>::First()
    {
        if (_object == nullptr)
            throw NullPointerException();
        if (_object->_offset == 0)
            throw OutOfRangeException("List is empty!");
        return _object->_data[0];
    }

    template<typename T>
    T& List<T>::Last()
    {
        if (_object == nullptr)
            throw NullPointerException();
        if (_object->_offset == 0)
            throw OutOfRangeException("List is empty!");
        return _object->_data[_offset-1];
    }
}

#endif // !KLANG_HEAD_LIST
