#pragma once
#ifndef KLANG_HEAD_ENCODING
#define KLANG_HEAD_ENCODING

#include <stdint.h>
#include "Types.h"
#include "Buffer.h"
#include "String.h"

namespace KLang
{
    typedef uint16_t ucs2;
    typedef uint32_t ucs4;

    bool UCS4toUTF8(ucs4 & symbol, Buffer & stream);
    bool UCS2toUTF8(ucs2 & symbol, Buffer & stream);

    bool UTF8toUCS4(ucs4 & symbol, Buffer & stream);
    bool UTF8toUCS2(ucs2 & symbol, Buffer & stream);

    bool UCS4toASCII(ucs4& symbol, Buffer& stream);
    bool UCS2toASCII(ucs4& symbol, Buffer& stream);

    bool ASCIItoUCS4(ucs4& symbol, Buffer& stream);
    bool ASCIItoUCS2(ucs2& symbol, Buffer& stream);

    namespace Encoder
    {
        // symbols -> buffer
        bool Encode(Buffer& buffer, Array<ucs4>& symbols, Encoding encoding);
        // buffer -> symbols
        bool Decode(Buffer& buffer, Array<ucs4>& symbols, Encoding encoding);

        Buffer Encode(Array<ucs4>&symbols, Encoding encoding);
        Array<ucs4> Decode(Buffer& buffer, Encoding encoding);
    }
}

#endif // !KLANG_HEAD_ENCODING
