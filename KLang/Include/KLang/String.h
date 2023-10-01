#pragma once
#ifndef KLANG_HEAD_STRING
#define KLANG_HEAD_STRING

#include "Types.h"

namespace KLang
{
    class String
    {
    private:
        uint32_t _size;
        // Array will be here
        //ucs4 * _data;

    public:
        String(const char* str, Encoding encoding = Encoding::utf8);
    };
}

#endif // KLANG_HEAD_STRING