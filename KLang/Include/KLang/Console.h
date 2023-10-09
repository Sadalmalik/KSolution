#pragma once
#ifndef KLANG_HEAD_CONSOLE
#define KLANG_HEAD_CONSOLE

#include "Types.h"
#include "String.h"
#include "Encoding.h"
#include "StringBuilder.h"

namespace KLang
{
    class Console
    {
    private:
        Console() = delete;
        static Encoding _encoding;
        static Buffer _buffer;
    public:
        static void SetEncoding(Encoding encoding);

        static int Write(String& line);
        static int WriteLine(String& line);

        static String Read(uint32_t symbols);
        static String ReadLine(uint32_t symbols);

        // Raw bytes... Not recomended?
        //static void Write(const char& text);
        static void WriteBytes(Array<byte>& line);
        static Array<byte> ReadBytes(uint32_t bytes);
        static byte ReadByte();
    };
}

#endif // !KLANG_HEAD_CONSOLE