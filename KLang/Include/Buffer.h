#pragma once
#ifndef KLANG_HEAD_STREAM
#define KLANG_HEAD_STREAM

#include <stdint.h>
#include <stdio.h>

namespace KLang
{
    typedef int8_t byte;

    class Buffer
    {
    private:
        byte* _begin;
        byte* _end;
        byte* _it;
        bool _isOwner;
        size_t _size;
    public:
        inline Buffer(size_t size);
        inline Buffer(byte* begin, byte* end);
        inline ~Buffer();

        inline bool IsEOF();

        inline byte* Begin();
        inline byte* End();

        inline size_t Offset();
        inline size_t Remains();

        inline void Seek(size_t, int point = SeekCur);
        inline void Write(byte b);
        inline byte Read();

        static const int SeekBgn = 0;
        static const int SeekCur = 1;
        static const int SeekEnd = 2;
    };

    inline Buffer::Buffer(size_t size)
    {
        this->_isOwner = true;
        this->_size = size;
        this->_begin = new byte[size];
        this->_end = &this->_begin[size];
        this->_it = this->_begin;
        printf("Allocate %d bytes at %p\n", size, this->_begin);
    }

    inline Buffer::Buffer(byte* begin, byte* end)
    {
        this->_isOwner = false;
        this->_begin = begin;
        this->_end = end;
        this->_it = begin;
        this->_size = this->_end - this->_begin;
    }

    inline Buffer::~Buffer()
    {
        if (this->_isOwner)
        {
            printf("Free %d bytes at %p\n", this->_size, this->_begin);
            delete[] this->_begin;
        }
    }

    inline byte*  Buffer::Begin()    { return this->_begin; }
    inline byte*  Buffer::End()      { return this->_end; }
    inline bool   Buffer::IsEOF()    { return this->_it == this->_end; }
    inline size_t Buffer::Offset()   { return (size_t)(this->_it - this->_begin); }
    inline size_t Buffer::Remains()  { return (size_t)(this->_end - this->_it); }

    inline void Buffer::Seek(size_t offset, int point)
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

#endif // !KLANG_HEAD_STREAM