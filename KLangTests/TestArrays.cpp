#include <stdio.h>

#include "KLangTests.h"
#include "KLang/Array.h"

using namespace KLang;

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
    printf("Array is null: %s\n", thirdArray == nullptr ? "true" : "false");
    thirdArray = array;
    printf("Array is null: %s\n", thirdArray == nullptr ? "true" : "false");

    Array<int> nullArray(nullptr);

    printf("Array is null: %s\n", nullArray == nullptr ? "true" : "false");
}