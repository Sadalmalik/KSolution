#include <stdio.h>
#include <fstream>
#include <mutex>

#include "KLangTests.h"


int main()
{
    TestEncoding();
    TestArrays();

    printf("Hello World!\n");
    printf("\n");
    printf("Size of mutex: %d\n", (int) sizeof(std::mutex));

    return 0;
}
