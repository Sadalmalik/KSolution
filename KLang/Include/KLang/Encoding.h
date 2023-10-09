#pragma once
#ifndef KLANG_HEAD_ENCODING
#define KLANG_HEAD_ENCODING

#include <stdint.h>

#include "Types.h"
#include "Buffer.h"
#include "Array.h"

namespace KLang
{
    enum class Encoding
    {
        None = 0,
        utf8 = 1,
        ascii = 2,
        win1251 = 3
    };

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
        // #1 - preallocated buffers and strings:
        // symbols -> buffer
        int Encode(const Buffer& buffer, const Array<ucs4>& symbols, Encoding encoding = Encoding::utf8);
        // buffer -> symbols
        int Decode(const Buffer& buffer, const Array<ucs4>& symbols, Encoding encoding = Encoding::utf8);

        // Auto allocated buffer and strings:
        // symbols -> buffer
        Buffer Encode(const Array<ucs4>&symbols, Encoding encoding = Encoding::utf8);
        // buffer -> symbols
        Array<ucs4> Decode(const Buffer& buffer, Encoding encoding = Encoding::utf8);
    }
}

#endif // !KLANG_HEAD_ENCODING
