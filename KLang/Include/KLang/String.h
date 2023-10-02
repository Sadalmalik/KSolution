#pragma once
#ifndef KLANG_HEAD_STRING
#define KLANG_HEAD_STRING

#include "Types.h"
#include "Array.h"

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

        ucs4& operator[] (uint32_t index);

        static String operator+ (String a, String b);
    };
}

#endif // KLANG_HEAD_STRING