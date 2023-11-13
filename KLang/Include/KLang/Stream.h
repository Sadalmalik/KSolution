#pragma once
#ifndef KLANG_HEAD_STREAM
#define KLANG_HEAD_STREAM

#include <atomic>

#include "Types.h"
#include "Exceptions.h"

namespace KLang
{
    enum class SeekPosition
    {
        Current = 0,
        Begin = 1,
        End = 2
    };

    class StreamObject
    {
    private:
        std::atomic<uint32_t> _counter;
    public:
        virtual ~StreamObject() = 0;

        // Return false for infinity streams
        virtual bool IsEOF() = 0;
        virtual bool CanRead() = 0;
        virtual bool CanWrite() = 0;

        // Return -1 for infinity
        virtual uint32_t Length() = 0;
        virtual uint32_t Offset() = 0;
        virtual uint32_t Remains() = 0;

        virtual void Seek(uint32_t, SeekPosition position = SeekPosition::Current) = 0;
        virtual uint32_t Tell() = 0;

        virtual void Write(byte b) = 0;
        virtual byte Read() = 0;

        friend class Stream;
    };

    class Stream
    {
    private:
        StreamObject* _stream;

        inline void CleanStreamObject()
        {
            if (_stream == nullptr)
                return;

            _stream->_counter--;

            if (_stream->_counter == 0)
                delete _stream;

            _stream = nullptr;
        }

        inline void NullCheck()
        {
            if (_stream == nullptr)
                throw NullPointerException("NullPointerException: Stream is null!\n");
        }

    public:
        Stream() : _stream(nullptr) { }

        Stream(Stream& other)
        {
            _stream = other._stream;
            _stream->_counter++;
        }

        Stream(const Stream& other)
        {
            _stream = other._stream;
            _stream->_counter++;
        }

        Stream(StreamObject* stream)
        {
            _stream = stream;
            _stream->_counter++;
        }

        inline bool IsEOF()         { NullCheck(); return _stream->IsEOF(); }
        inline bool CanRead()       { NullCheck(); return _stream->CanRead(); }
        inline bool CanWrite()      { NullCheck(); return _stream->CanWrite(); }

        inline uint32_t Length()    { NullCheck(); return _stream->Length(); }
        inline uint32_t Offset()    { NullCheck(); return _stream->Offset(); }
        inline uint32_t Remains()   { NullCheck(); return _stream->Remains(); }

        inline void Seek(uint32_t offset, SeekPosition position = SeekPosition::Current)
        {
            NullCheck();
            _stream->Seek(offset, position);
        }
        inline uint32_t Tell()
        {
            NullCheck();
            return _stream->Tell();
        }

        inline void Write(byte b)   { NullCheck(); _stream->Write(b); }
        inline byte Read()          { NullCheck(); return _stream->Read(); }

        inline void operator= (const Stream& other)
        {
            CleanStreamObject();
            _stream = other._stream;
            if (_stream != nullptr)
                _stream->_counter++;
        }

        inline void operator= (Stream& other)
        {
            CleanStreamObject();
            _stream = other._stream;
            if (_stream != nullptr)
                _stream->_counter++;
        }

        inline void operator= (Stream* other)
        {
            CleanStreamObject();
            _stream = other->_stream;
            if (_stream != nullptr)
                _stream->_counter++;
        }

        inline void operator= (StreamObject* stream)
        {
            CleanStreamObject();
            _stream = stream;
            _stream->_counter++;
        }

        inline bool operator== (const Stream& other)
        {
            return _stream == other._stream;
        }

        inline bool operator== (const Stream* other)
        {
            return _stream == other->_stream;
        }
    };
}

#endif // !KLANG_HEAD_STREAM
