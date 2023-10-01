#include <stdio.h>
#include <fstream>
#include <mutex>

#include "KLang/Buffer.h"
#include "KLang/Encoding.h"
#include "KLang/Array.h"


using namespace KLang;

void TestRawEncoding();
void TestArrays();

int main()
{
    TestRawEncoding();
    TestArrays();

    printf("Hello World!\n");
    printf("\n");
    printf("Size of mutex: %d\n", (int) sizeof(std::mutex));

    return 0;
}

void TestRawEncoding()
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
    int length = (int) fin.tellg();
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

void TestArrays()
{
    Array<int> array(15);

    try
    {
        for (uint32_t i = 0; i < array.Length(); i++)
        {
            array[i] = i + 5;
        }

        for (uint32_t i = 0; i < array.Length(); i++)
        {
            printf("Element[ %d ] = %d\n", i, array[i]);
        }

        int value = array[-1];
    }
    catch (OutOfRangeException outExc)
    {
        printf(outExc.ToString());
    }

    Array<int> anotherArray;

    try
    {
        printf("Element 0 = %d\n", anotherArray[0]);
    }
    catch (NullPointerException nullExc)
    {
        printf(nullExc.ToString());
    }

    anotherArray = array;

    try
    {
        printf("Element 0 = %d\n", anotherArray[0]);
    }
    catch (NullPointerException nullExc)
    {
        printf(nullExc.ToString());
    }

    printf("Arrays equal: %s\n", array == anotherArray ? "true" : "false");

    Array<int> thirdArray;
    printf("Array is  null: %s\n", thirdArray == nullptr ? "true" : "false");
    thirdArray = array;
    printf("Array is  null: %s\n", thirdArray == nullptr ? "true" : "false");
}