#pragma once
#ifndef KLANG_HEAD_ENCODING
#define KLANG_HEAD_ENCODING

#include <stdint.h>
#include "Stream.h"

namespace KLang
{
    typedef uint16_t ucs2;
    typedef uint32_t ucs4;

    bool UCS4toUTF8(ucs4 &symbol, Stream &stream);
    bool UCS2toUTF8(ucs2 &symbol, Stream &stream);

    bool UTF8toUCS4(ucs4& symbol, Stream& stream);
    bool UTF8toUCS2(ucs2& symbol, Stream& stream);
}

#endif // !KLANG_HEAD_ENCODING
