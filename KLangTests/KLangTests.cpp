#include <stdio.h>

#include "Stream.h"
#include "Encoding.h"

#include <fstream>

using namespace KLang;

int main()
{
    const int size = 4 * 1024;
    byte buffer[size];
    Stream stream(&buffer[0], &buffer[size], Stream::T_READ | Stream::T_WRITE);

    ucs4 c = 0;
    bool success = false;

    // 0400-04FF
    for (c = 0x0400; c <= 0x04FF; c++)
    {
        success = UCS4toUTF8(c, stream);
    }

    printf("Chars count: %d\n bytes writed: %d", (int)(0x04FF - 0x0400), stream.Offset());

    std::fstream fout;
    fout.open("D:/test.txt", std::ios::binary | std::ios::out);

    char* start = (char*)stream.Begin();

    fout.write(start, stream.Offset());
    fout.close();


    printf("Hello World!\n");
}