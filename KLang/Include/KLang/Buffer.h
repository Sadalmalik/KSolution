#pragma once
#ifndef KLANG_HEAD_BUFFER
#define KLANG_HEAD_BUFFER

#include <stdio.h>
#include "Types.h"

namespace KLang
{
    class Buffer
    {
    private:
        byte* _it;
        byte* _begin;
        byte* _end;

        uint32_t _size;
        Array<byte> _data;
    public:
        inline Buffer(uint32_t size);
        inline Buffer(byte* begin, byte* end);
        inline ~Buffer();

        void Resize(uint32_t newLength);

        inline bool IsEOF();

        inline byte* Begin();
        inline byte* End();

        inline uint32_t Length();
        inline uint32_t Offset();
        inline uint32_t Remains();

        inline void Seek(uint32_t, int point = SeekCur);
        inline void Write(byte b);
        inline byte Read();

        static const int SeekBgn = 0;
        static const int SeekCur = 1;
        static const int SeekEnd = 2;
    };

    inline Buffer::Buffer(uint32_t size) : _data(size)
    {
        _size = size;

        this->_begin = &_data[0];
        this->_end = &_data[size-1];
        this->_it = this->_begin;

        for (int i = 0; i < size; i++)
            this->_begin[i] = 0;
    }

    inline Buffer::Buffer(byte* begin, byte* end) : _data(nullptr)
    {
        this->_begin = begin;
        this->_end = end;
        this->_it = begin;

        this->_size = this->_end - this->_begin;
    }

    inline Buffer::~Buffer()
    {
        _data = nullptr;
    }

    inline void   Buffer::Resize(uint32_t newLength)
    {
        _data.Resize(newLength);
        _size = newLength;
    }

    inline byte*  Buffer::Begin()    { return _begin; }
    inline byte*  Buffer::End()      { return _end; }
    inline bool   Buffer::IsEOF()    { return _it == _end; }

    inline uint32_t Buffer::Length()   { return _data.Length(); }
    inline uint32_t Buffer::Offset()   { return (uint32_t)(this->_it - this->_begin); }
    inline uint32_t Buffer::Remains()  { return (uint32_t)(this->_end - this->_it); }

    inline void Buffer::Seek(uint32_t offset, int point)
    {
        switch (point)
        {
        case SeekBgn:
            this->_it = this->_begin + offset;
            break;
        case SeekCur:
            this->_it += offset;
            break;
        case SeekEnd:
            this->_it = this->_end - offset;
            break;
        }
    }

    inline void Buffer::Write(byte b)
    {
        *this->_it++ = b;
    }

    inline byte Buffer::Read()
    {
        return *this->_it++;
    }
}

#endif // !KLANG_HEAD_BUFFER