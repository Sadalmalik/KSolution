#include <stdio.h>

#include "Buffer.h"
#include "Encoding.h"

#include <fstream>

using namespace KLang;

int main()
{
    const int size = 8 * 1024;
    Buffer buffer(size);

    ucs4 c = 0;
    bool success = true;

    // 0400-04FF
    for (c = 0x0400; c <= 0x04FF; c++)
    {
        success &= UCS4toUTF8(c, buffer);
    }

    printf("Success encoding: %s\nChars count: %d\n bytes writed: %d\n",
        success ? "true" : "false",
        (int)(0x04FF - 0x0400),
        (int)buffer.Offset());

    std::fstream fout;
    fout.open("D:/test.txt", std::ios::binary | std::ios::out);

    fout.write((char*)buffer.Begin(), buffer.Offset());
    fout.close();


    printf("Hello World!\n");
}