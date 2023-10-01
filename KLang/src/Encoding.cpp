#include "KLang/Encoding.h"

namespace KLang
{
    bool UCS4toUTF8(ucs4& sym, Buffer& Buffer)
    {
        if (Buffer.Remains()==0)
            return false;

		if (sym < 0x0080)
		{
			Buffer.Write(sym);
		}
		else if (sym < 0x0800)
		{
			Buffer.Write(0xC0 | (sym >> 6));
			Buffer.Write(0x80 | (sym & 0x3F));
		}
		else if (sym <= 0x0000FFFF)
		{
			Buffer.Write(0xE0 | (sym >> 12));
			Buffer.Write(0x80 | ((sym >> 6) & 0x3F));
			Buffer.Write(0x80 | (sym & 0x3F));
		}
		else if (sym <= 0x001FFFFF)
		{
			Buffer.Write(0xF0 | (sym >> 18));
			Buffer.Write(0x80 | ((sym >> 12) & 0x3F));
			Buffer.Write(0x80 | ((sym >> 6) & 0x3F));
			Buffer.Write(0x80 | (sym & 0x3F));
		}
		else
		{
			// Values above 0x0010FFFF considered as non-secure
			// https://datatracker.ietf.org/doc/html/rfc3629
			Buffer.Write('\1');
			return false;
		}

		return true;
    }

    bool UCS2toUTF8(ucs2& sym, Buffer& Buffer)
    {
		ucs4 value = sym;
		return UCS4toUTF8(value, Buffer);
    }

	bool UTF8toUCS4(ucs4& sym, Buffer& Buffer)
	{
		if (Buffer.Remains() == 0)
			return false;

		size_t offset = Buffer.Offset();
		uint32_t c = Buffer.Read();

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
			uint32_t c2 = Buffer.Read();
			if (0x80 != (0xC0 & c2)) goto fail;

			sym = ((c  & 0x1F) << 6)
				|  (c2 & 0x3F);
			return true;
		}

		if (0xE0 == (0xF0 & c)) // 3 bytes
		{
			uint32_t c2 = Buffer.Read();
			if (0x80 != (0xC0 & c2)) goto fail;
			uint32_t c3 = Buffer.Read();
			if (0x80 != (0xC0 & c3)) goto fail;

			sym = ((c  & 0x0F) << 12)
				| ((c2 & 0x3F) << 6)
				|  (c3 & 0x3F);
			return true;
		}

		if (0xF0 == (0xF8 & c)) // 4 bytes
		{
			uint32_t c2 = Buffer.Read();
			if (0x80 != (0xC0 & c2)) goto fail;
			uint32_t c3 = Buffer.Read();
			if (0x80 != (0xC0 & c3)) goto fail;
			uint32_t c4 = Buffer.Read();
			if (0x80 != (0xC0 & c4)) goto fail;

			sym = ((c  & 0x07) << 18)
				| ((c2 & 0x3F) << 12)
				| ((c3 & 0x3F) << 6)
				|  (c4 & 0x3F);
			return true;
		}
	fail:
		Buffer.Seek(offset, Buffer::SeekBgn);
		sym = 0xffff;
		return false;
    }

    bool UTF8toUCS2(ucs2& sym, Buffer& Buffer)
    {
		if (Buffer.Remains() == 0)
			return false;

		size_t offset = Buffer.Offset();

		ucs4 result;

		if (UTF8toUCS4(result, Buffer))
		{
			if (result < 0xFFFF)
			{
				sym = result;
				return true;
			}
		}

		Buffer.Seek(offset, Buffer::SeekBgn);
		sym = 0xffff;
		return false;
    }

	bool UCS4toASCII(ucs4& symbol, Buffer& stream) { return false; }
	bool UCS2toASCII(ucs4& symbol, Buffer& stream) { return false; }

	bool ASCIItoUCS4(ucs4& symbol, Buffer& stream) { return false; }
	bool ASCIItoUCS2(ucs2& symbol, Buffer& stream) { return false; }
}