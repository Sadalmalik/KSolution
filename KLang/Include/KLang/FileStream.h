#pragma once
#ifndef KLANG_HEAD_FILE_STREAM
#define KLANG_HEAD_FILE_STREAM

#include <stdio.h>

#include "String.h"
#include "Stream.h"

namespace KLang
{
    class FileStream : StreamObject
    {
    private:
        FILE* _file;
        bool _canRead;
        bool _canWrite;
    public:
        FileStream(String path);

        bool IsEOF() override;
        bool CanRead() override;
        bool CanWrite() override;

        uint32_t Length() override;
        uint32_t Offset() override;
        uint32_t Remains() override;

        void Seek(uint32_t, SeekPosition position = SeekPosition::Current) override;
        uint32_t Tell() override;

        void Write(byte b) override;
        byte Read() override;
    };
}

#endif // !KLANG_HEAD_FILE_STREAM



