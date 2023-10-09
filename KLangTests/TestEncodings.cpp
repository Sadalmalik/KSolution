#include <stdio.h>
#include <fstream>

#include "KLangTests.h"

#include "KLang/Buffer.h"
#include "KLang/Encoding.h"

using namespace KLang;

void TestEncoding()
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

    printf("Done!\n\n");


    std::fstream fin;
    fin.open("D:/test.txt", std::ios::binary | std::ios::in);

    fin.seekg(0, std::ios::end);
    int length = (int)fin.tellg();
    fin.seekg(0, std::ios::beg);

    Buffer otherBuffer(size);
    fin.read((char*)otherBuffer.Begin(), length);       // read the whole file into the buffer
    fin.close();

    //throw std::exception("My Test Exception");

    otherBuffer.Seek(0, Buffer::SeekBgn);
    printf("Read symbols:\n");
    ucs4 r = 0;
    int count = 0x04FF - 0x0400;
    for (int i = 0; i <= count; i++)
    {
        success = UTF8toUCS4(r, otherBuffer);
        printf("  %d :  %X    %s\n", i, r, success ? "true" : "false");
    }
    printf("Done!\n\n");
}