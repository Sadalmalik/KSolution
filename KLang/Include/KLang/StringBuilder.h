#pragma once
#ifndef KLANG_HEAD_STRING_BUILDER
#define KLANG_HEAD_STRING_BUILDER

#include "Types.h"
#include "String.h"
#include "List.h"

namespace KLang
{
    class StringBuilder
    {
    private:
        List<String> _strings;
    public:
        StringBuilder();
        StringBuilder(String initial);
        StringBuilder(String& initial);
        ~StringBuilder();

        void Append(String string);
        void AppendLine(String string);
        void AppendFormat(String string);

        String ToString();
    };
}

#endif // !KLANG_HEAD_STRING_BUILDER