#pragma once
#ifndef KLANG_HEAD_ENCODING
#define KLANG_HEAD_ENCODING

#include <stdint.h>
#include "Buffer.h"

namespace KLang
{
    typedef uint16_t ucs2;
    typedef uint32_t ucs4;

    bool UCS4toUTF8(ucs4 & symbol, Buffer & stream);
    bool UCS2toUTF8(ucs2 & symbol, Buffer & stream);

    bool UTF8toUCS4(ucs4 & symbol, Buffer & stream);
    bool UTF8toUCS2(ucs2 & symbol, Buffer & stream);
}

#endif // !KLANG_HEAD_ENCODING
