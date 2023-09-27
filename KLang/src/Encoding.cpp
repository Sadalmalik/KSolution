#include "Encoding.h"

namespace KLang
{
    bool UCS4toUTF8(ucs4& sym, Stream& stream)
    {
        if (!stream.CanWrite())
            return false;

		if (sym < 0x0080)
		{
			stream.Write(sym);
		}
		else if (sym < 0x0800)
		{
			stream.Write(0xC0 | (sym >> 6));
			stream.Write(0x80 | (sym & 0x3F));
		}
		else if (sym <= 0x0000FFFF)
		{
			stream.Write(0xE0 | (sym >> 12));
			stream.Write(0x80 | ((sym >> 6) & 0x3F));
			stream.Write(0x80 | (sym & 0x3F));
		}
		else if (sym <= 0x001FFFFF)
		{
			stream.Write(0xF0 | (sym >> 18));
			stream.Write(0x80 | ((sym >> 12) & 0x3F));
			stream.Write(0x80 | ((sym >> 6) & 0x3F));
			stream.Write(0x80 | (sym & 0x3F));
		}
		else
		{
			// Values above 0x0010FFFF considered as non-secure
			// https://datatracker.ietf.org/doc/html/rfc3629
			stream.Write('\1');
			return false;
		}

		return true;
    }

    bool UCS2toUTF8(ucs2& sym, Stream& stream)
    {
		ucs4 value = sym;
		return UCS4toUTF8(value, stream);
    }

	bool UTF8toUCS4(ucs4& sym, Stream& stream)
	{
		if (!stream.CanRead())
			return false;

		size_t offset = stream.Offset();
		byte c = stream.Read();

		// Full packed?
		if (c == 0xFF)
			goto fail;

		// Not start of symbol
		if (0x80 == (0xC0 & c))
			goto fail;

		if (c < 0x80) // 1 byte
		{
			sym = c;
			return true;
		}

		if (0xC0 == (0xE0 & c)) // 2 bytes
		{
			byte c2 = stream.Read();
			if (0x80 != (0xC0 & c2)) goto fail;

			sym = ((c & 0x07) << 6)
				| (c2 & 0x3F);
			return true;
		}

		if (0xE0 == (0xF0 & c)) // 3 bytes
		{
			byte c2 = stream.Read();
			if (0x80 != (0xC0 & c2)) goto fail;
			byte c3 = stream.Read();
			if (0x80 != (0xC0 & c3)) goto fail;

			sym = ((c & 0x07) << 12)
				| ((c2 & 0x3F) << 6)
				| (c3 & 0x3F);
			return true;
		}

		if (0xF0 == (0xF8 & c)) // 4 bytes
		{
			byte c2 = stream.Read();
			if (0x80 != (0xC0 & c2)) goto fail;
			byte c3 = stream.Read();
			if (0x80 != (0xC0 & c3)) goto fail;
			byte c4 = stream.Read();
			if (0x80 != (0xC0 & c4)) goto fail;

			sym = ((c  & 0x07) << 18)
				| ((c2 & 0x3F) << 12)
				| ((c3 & 0x3F) << 6)
				|  (c4 & 0x3F);
			return true;
		}
	fail:
		stream.Seek(offset, Stream::T_SEEK_BGN);
		sym = 0xffff;
		return false;
    }

    bool UTF8toUCS2(ucs2& sym, Stream& stream)
    {
		if (!stream.CanRead())
			return false;

		size_t offset = stream.Offset();

		ucs4 result;

		if (UTF8toUCS4(result, stream))
		{
			if (result < 0xFFFF)
			{
				sym = result;
				return true;
			}
		}

		stream.Seek(offset, Stream::T_SEEK_BGN);
		sym = 0xffff;
		return false;
    }
}