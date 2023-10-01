#pragma once
#ifndef KLANG_HEAD_EXCEPTIONS
#define KLANG_HEAD_EXCEPTIONS

namespace KLang
{
    class Exception
    {
    protected:
        const char* _message;
    public:
        // TODO: Strings at exceptions
        Exception(const char* message);

        virtual const char* ToString();
    };

    class NullPointerException : public Exception
    {
    public:
        // TODO: Strings at exceptions
        NullPointerException(const char* message);

        const char* ToString() override;
    };

    class OutOfRangeException : public Exception
    {
    public:
        // TODO: Strings at exceptions
        OutOfRangeException(const char* message);

        const char* ToString() override;
    };
}

#endif // KLANG_HEAD_EXCEPTIONS