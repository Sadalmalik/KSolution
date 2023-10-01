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

    OutOfRangeException::OutOfRangeException(const char* message) : Exception(message)
    {
        
    }

    const char* OutOfRangeException::ToString()
    {
        return this->_message;
    }
}