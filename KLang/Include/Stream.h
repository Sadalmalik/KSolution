#pragma once
#ifndef KLANG_HEAD_STREAM
#define KLANG_HEAD_STREAM

#include <stdint.h>

namespace KLang
{
    typedef int8_t byte;

    class Stream
    {
    private:
        int _flags;
        byte* _begin;
        byte* _end;
        byte* _it;
    public:
        inline Stream();
        inline Stream(byte* begin, byte* end, int flags);

        inline byte* Begin();
        inline byte* End();

        inline size_t Offset();
        inline size_t Remains();

        inline bool IsEOF();
        inline bool CanRead();
        inline bool CanWrite();

        inline void Seek(size_t, int point = T_SEEK_CUR);

        inline void Write(byte b);
        inline byte Read();

        static const int T_SEEK_BGN = 0;
        static const int T_SEEK_CUR = 1;
        static const int T_SEEK_END = 2;

        static const int T_READ = 0x1;
        static const int T_WRITE = 0x2;
    };

    inline Stream::Stream(byte* begin, byte* end, int flags)
    {
        this->_flags = flags;
        this->_begin = begin;
        this->_end = end;
        this->_it = begin;
    }

    inline byte*  Stream::Begin()    { return this->_begin; }
    inline byte*  Stream::End()      { return this->_end; }
    inline bool   Stream::IsEOF()    { return this->_it == this->_end; }
    inline size_t Stream::Offset()   { return (size_t)(this->_it - this->_begin); }
    inline size_t Stream::Remains()  { return (size_t)(this->_end - this->_it); }
    inline bool   Stream::CanRead()  { return 0 != (this->_flags & T_READ); }
    inline bool   Stream::CanWrite() { return 0 != (this->_flags & T_WRITE); }

    inline void Stream::Seek(size_t offset, int point)
    {
        switch (point)
        {
        case T_SEEK_BGN:
            this->_it = this->_begin + offset;
            break;
        case T_SEEK_CUR:
            this->_it += offset;
            break;
        case T_SEEK_END:
            this->_it = this->_end - offset;
            break;
        }
    }

    inline void Stream::Write(byte b)
    {
        *this->_it++ = b;
    }

    inline byte Stream::Read()
    {
        return *this->_it++;
    }
}

#endif // !KLANG_HEAD_STREAM