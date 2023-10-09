#pragma once
#ifndef KLANG_HEAD_STRING
#define KLANG_HEAD_STRING

#include "Types.h"
#include "Array.h"
#include "Encoding.h"

namespace KLang
{
    class String
    {
    private:
        Array<ucs4> _data;

    public:
        String();
        String(const char* str, Encoding encoding = Encoding::utf8);
        String(Array<ucs4>symbols);
        String(String&string);

        uint32_t Length();
        Array<ucs4> Symbols();

        ucs4& operator[] (uint32_t index);

        String operator+ (String& other);

        static bool IsNullOrEmpty(String& string);
        // Need to think about that
        static String Format(String format);

        static String NewLine;
    };
}

#endif // KLANG_HEAD_STRING