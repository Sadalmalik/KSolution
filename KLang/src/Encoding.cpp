#include "KLang/Array.h"
#include "KLang/Encoding.h"
#include "KLang/Exceptions.h"

namespace KLang
{
	typedef bool (*ENCtoUCS) (ucs4& symbol, Buffer& stream);
	typedef bool (*UCStoENC) (ucs4& symbol, Buffer& stream);

	struct EncoderPair
	{
		ENCtoUCS encoding_to_ucs;
		UCStoENC ucs_to_encoding;
	};

	Array<EncoderPair> encoders({
		{nullptr, nullptr},
		{UTF8toUCS4, UCS4toUTF8},
		{ASCIItoUCS4, UCS4toASCII},
		{nullptr, nullptr}
	}); /// Hmmm 

	// symbols -> buffer
	int Encode(Buffer& buffer, Array<ucs4>& symbols, Encoding encoding)
	{
		UCStoENC encode = encoders[(int)encoding].ucs_to_encoding;

		// Stream API?
		ucs4 symbol;
		uint32_t idx = 0;
		uint32_t size = symbols.Length();
		for (idx = 0; idx < size; idx++)
		{
			symbol = symbols[idx];
			if (!encode(symbol, buffer))
				throw EncodingException("Unexpected symbol {0}");
		}

		return idx;
	}

	// buffer -> symbols
	int Decode(Buffer& buffer, Array<ucs4>& symbols, Encoding encoding)
	{
		ENCtoUCS decode = encoders[(int)encoding].encoding_to_ucs;

		ucs4 symbol;
		uint32_t idx = 0;
		while (buffer.Remains() > 0)
		{
			if (!decode(symbol, buffer))
				throw EncodingException("Unexpected symbol {0}");
			symbols[idx++] = symbol;
		}

		return idx;
	}

	// symbols -> buffer
	Buffer Encode(Array<ucs4>& symbols, Encoding encoding)
	{
		Buffer buffer(4 * symbols.Length());

		Encode(buffer, symbols, encoding);

		// Well, i thing i need rewrite buffer based on Arrays
		size_t length = buffer.Offset();
		Buffer resized(length);
		buffer.Seek(0, Buffer::SeekBgn);
		while (buffer.Offset() < length)
		{
			resized.Write(buffer.Read());
		}

		return resized;
	}

	// buffer -> symbols
	Array<ucs4> Decode(Buffer& buffer, Encoding encoding)
	{
		Array<ucs4> symbols(buffer.Remains());

		int readed = Decode(buffer, symbols, encoding);

		symbols.Resize(readed);
		return readed;
	}
}