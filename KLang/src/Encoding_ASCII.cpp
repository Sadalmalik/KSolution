#include "KLang/Encoding.h"
#include "KLang/Exceptions.h"

namespace KLang
{
    // UCS4 support
    bool UCS4toASCII(ucs4& symbol, Buffer& stream)
    {
        if (symbol < 0x80)
        {
            stream.Write((byte)symbol);
            return true;
        }
        return false;
    }

    bool ASCIItoUCS4(ucs4& symbol, Buffer& stream)
    {
        if (symbol < 0x80)
        {
            stream.Write((byte)symbol);
            return true;
        }
        return false;
    }

    // UCS2 support
    bool UCS2toASCII(ucs4& symbol, Buffer& stream)
    {
        byte c = stream.Read();
        if (c > 0x7F)
        {
            stream.Seek(-1);
            return false;
        }
        symbol = c;
        return true;
    }

    bool ASCIItoUCS2(ucs2& symbol, Buffer& stream)
    {
        byte c = stream.Read();
        if (c > 0x7F)
        {
            stream.Seek(-1);
            return false;
        }
        symbol = c;
        return true;
    }
}