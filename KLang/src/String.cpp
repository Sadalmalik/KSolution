#include "KLang/String.h"
#include "KLang/Encoding.h"

namespace KLang
{
    String String::NewLine(u8"\n", Encoding::utf8);

    String::String() : _data(nullptr) { }

    String::String(String& string) : _data(string._data) { }

    String::String(Array<ucs4>symbols) : _data(symbols) { }

    String::String(const char* str, Encoding encoding)
    {
        // Decode string by encoding
        uint32_t size = (uint32_t) strlen(str);
        Buffer buffer((byte*)str, (byte*)(str + size));
        _data = Encoder::Decode(buffer, encoding);
    }

    uint32_t String::Length()
    {
        return _data.Length();
    }

    Array<ucs4> String::Symbols()
    {
        return _data;
    }

    ucs4& String::operator[] (uint32_t index)
    {
        return _data[index];
    }

    String String::operator+ (String& other)
    {
        return _data + other._data;
    }

    bool String::IsNullOrEmpty(String& string)
    {
        return string._data == nullptr || string._data.Length() == 0;
    }

    String String::Format(String format)
    {
        // Use String builder here? How?
        throw NotImplementedException("Format not implemented!");
    }
}