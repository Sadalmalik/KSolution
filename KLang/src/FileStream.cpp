#include "KLang/FileStream.h"


namespace KLang
{
    FileStream::FileStream(String path)
    {

    }

    bool FileStream::IsEOF()
    {
        return _file != nullptr;
    }

    bool FileStream::CanRead()
    {
        return _file != nullptr && _canRead;
    }

    bool FileStream::CanWrite()
    {
        return _file != nullptr && _canWrite;
    }

    uint32_t FileStream::Length()
    {
        
    }

    uint32_t FileStream::Offset()
    {
    
    }

    uint32_t FileStream::Remains()
    {
    
    }

    void FileStream::Seek(uint32_t, SeekPosition position = SeekPosition::Current)
    {
    
    }
    uint32_t FileStream::Tell()
    {
    
    }

    void FileStream::Write(byte b)
    {
    
    }
    byte FileStream::Read()
    {
    
    }
}