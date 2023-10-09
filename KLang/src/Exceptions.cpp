#include "KLang/Exceptions.h"

namespace KLang
{

    Exception::Exception(const char* message)
    {
        this->_message = message;
    }

    const char* Exception::ToString()
    {
        return this->_message;
    }



    NotImplementedException::NotImplementedException(const char* message)
    {
        this->_message = message;
    }

    const char* NotImplementedException::ToString()
    {
        return this->_message;
    }



    NullPointerException::NullPointerException(const char* message) : Exception(message) { }

    const char* NullPointerException::ToString()
    {
        return this->_message;
    }



    OutOfRangeException::OutOfRangeException(const char* message) : Exception(message) { }

    const char* OutOfRangeException::ToString()
    {
        return this->_message;
    }



    EncodingException::EncodingException(const char* message) : Exception(message) { }

    const char* EncodingException::ToString()
    {
        return this->_message;
    }
}