#include "KLang/String.h"
#include "KLang/Encoding.h"

namespace KLang
{
    String::String() : _data(nullptr) { }

    String::String(String& string) : _data(string._data) { }

    String::String(Array<ucs4>symbols) : _data(symbols) { }

    String::String(const char* str, Encoding encoding = Encoding::utf8)
    {
        // Decode string by encoding
        int size = strlen(str);
        // Encoder::Decode()
    }

    uint32_t String::Length()
    {
        return _data.Length();
    }

    ucs4& String::operator[] (uint32_t index)
    {
        return _data[index];
    }

    String String::operator+ (String a, String b)
    {
        return nullptr;
    }
}