#include <stdio.h>
#include "KLang/Console.h"
#include "KLang/Encoding.h"

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#endif

namespace KLang
{
    void Console::SetEncoding(Encoding encoding)
    {
        _encoding = encoding;
#if defined(_WIN32) || defined(_WIN64)
        SetConsoleOutputCP(CP_UTF8);
#endif
    }

    int Console::Write(String& string)
    {
        uint32_t length = 4 * string.Length();
        if (_buffer.Length() < length)
            _buffer.Resize(length);

        Encoder::Encode(_buffer, string.Symbols(), _encoding);
        _buffer.Write('\0');

        return fputs((char*)_buffer.Begin(), stdout);
    }

    int Console::WriteLine(String& line)
    {
        uint32_t length = 4 * line.Length();
        if (_buffer.Length() < length)
            _buffer.Resize(length);

        Encoder::Encode(_buffer, line.Symbols(), _encoding);
        _buffer.Write('\n');
        _buffer.Write('\0');

        return fputs((char*)_buffer.Begin(), stdout);
    }

    String Console::Read(uint32_t symbols)
    {

    }

    String Console::ReadLine(uint32_t symbols)
    {

    }


    //void Console::Write(const char& text, Encoding encoding) { }
    void Console::Write(Array<byte>& line) { }
    Array<byte> Console::ReadBytes(uint32_t bytes) { }
    static byte ReadByte() { }
}