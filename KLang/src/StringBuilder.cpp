#include "KLang/Encoding.h"
#include "KLang/String.h"
#include "KLang/StringBuilder.h"

namespace KLang
{
    StringBuilder::StringBuilder()
    {
    }

    StringBuilder::StringBuilder(String initial)
    {
        _strings.Add(initial);
    }

    StringBuilder::StringBuilder(String& initial)
    {
        _strings.Add(initial);
    }

    StringBuilder::~StringBuilder()
    {
        // Nothing to do here?
    }

    void StringBuilder::Append(String string)
    {
        _strings.Add(string);
    }

    void StringBuilder::AppendLine(String string)
    {
        _strings.Add(string);
        _strings.Add(String::NewLine);
    }

    void StringBuilder::AppendFormat(String string)
    {
        throw NotImplementedException("AppendFormat not implemented!");
    }

    String StringBuilder::ToString()
    {
        uint32_t length = 0;
        uint32_t count = _strings.Length();
        for (uint32_t i = 0; i < count; i++)
            length += _strings[i].Length();

        uint32_t offset = 0;
        Array<ucs4> finalString(length);
        for (uint32_t i = 0; i < count; i++)
        {
            String string = _strings[i];
            length = string.Length();
            for (uint32_t k = 0; k < length; k++)
            {
                finalString[k + offset] = string[k];
            }
            offset += length;
        }

        return finalString;
    }
}