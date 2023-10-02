#pragma once
#ifndef KLANG_HEAD_TYPES
#define KLANG_HEAD_TYPES

#include <stdint.h>

namespace KLang
{
    typedef uint8_t byte;

    typedef uint16_t ucs2;
    typedef uint32_t ucs4;

    enum class Encoding
    {
        None = 0,
        utf8 = 1,
        ascii = 1,
        win1251 = 2
    };
}

#endif // !KLANG_HEAD_TYPES
