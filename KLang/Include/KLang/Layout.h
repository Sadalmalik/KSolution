#pragma once
#ifndef KLANG_HEAD_LAYOUT
#define KLANG_HEAD_LAYOUT

#include <tuple>

#include "Types.h"

namespace KLang
{
    template<typename T1>
    inline auto NewLayout(uint32_t s1)
    {
        byte* layout = new byte[
            s1 * sizeof(T1)
        ];
        T1* t1 = (T1*)layout;
        uint32_t i;
        for (i = 0; i < s1; i++) new (&t1[i]) T1();
        return layout, t1;
    }

    template<typename T1, typename T2>
    inline auto NewLayout(uint32_t s1, uint32_t s2)
    {
        byte* layout = new byte[
            s1 * sizeof(T1) +
            s2 * sizeof(T2)
        ];
        T1* t1 = (T1*)layout;
        T2* t2 = (T2*)(t1[s1]);
        uint32_t i;
        for (i = 0; i < s1; i++) new (&t1[i]) T1();
        for (i = 0; i < s2; i++) new (&t2[i]) T2();
        return layout, t1, t2;
    }

    template<typename T1, typename T2, typename T3>
    inline auto NewLayout(uint32_t s1, uint32_t s2, uint32_t s3)
    {
        byte* layout = new byte[
            s1 * sizeof(T1) +
            s2 * sizeof(T2) +
            s3 * sizeof(T3)
        ];
        T1* t1 = (T1*)layout;
        T2* t2 = (T2*)(t1[s1]);
        T3* t3 = (T3*)(t2[s2]);
        uint32_t i;
        for (i = 0; i < s1; i++) new (&t1[i]) T1();
        for (i = 0; i < s2; i++) new (&t2[i]) T2();
        for (i = 0; i < s3; i++) new (&t3[i]) T3();
        return layout, t1, t2, t3;
    }

    template<typename T1, typename T2, typename T3, typename T4>
    inline auto NewLayout(uint32_t s1, uint32_t s2, uint32_t s3, uint32_t s4)
    {
        byte* layout = new byte[
            s1 * sizeof(T1) +
            s2 * sizeof(T2) +
            s3 * sizeof(T3) +
            s4 * sizeof(T4)
        ];
        T1* t1 = (T1*)layout;
        T2* t2 = (T2*)(t1[s1]);
        T3* t3 = (T3*)(t2[s2]);
        T4* t4 = (T4*)(t3[s3]);
        uint32_t i;
        for (i = 0; i < s1; i++) new (&t1[i]) T1();
        for (i = 0; i < s2; i++) new (&t2[i]) T2();
        for (i = 0; i < s3; i++) new (&t3[i]) T3();
        for (i = 0; i < s4; i++) new (&t4[i]) T4();
        return layout, t1, t2, t3, t4;
    }

    template<typename T1>
    inline auto DelLayout(byte* layout, uint32_t s1)
    {
        T1* t1 = (T1*)layout;
        uint32_t i;
        for (i = 0; i < s1; i++) t1[i].~T();
        delete[] layout;
    }

    template<typename T1, typename T2>
    inline auto DelLayout(byte* layout, uint32_t s1, uint32_t s2)
    {
        T1* t1 = (T1*)layout;
        T2* t2 = (T2*)(t1[s1]);
        uint32_t i;
        for (i = 0; i < s1; i++) t1[i].~T();
        for (i = 0; i < s2; i++) t2[i].~T();
        delete[] layout;
    }

    template<typename T1, typename T2, typename T3>
    inline auto DelLayout(byte* layout, uint32_t s1, uint32_t s2, uint32_t s3)
    {
        T1* t1 = (T1*)layout;
        T2* t2 = (T2*)(t1[s1]);
        T3* t3 = (T3*)(t2[s2]);
        uint32_t i;
        for (i = 0; i < s1; i++) t1[i].~T();
        for (i = 0; i < s2; i++) t2[i].~T();
        for (i = 0; i < s3; i++) t3[i].~T();
        delete[] layout;
    }

    template<typename T1, typename T2, typename T3, typename T4>
    inline auto DelLayout(byte* layout, uint32_t s1, uint32_t s2, uint32_t s3, uint32_t s4)
    {
        T1* t1 = (T1*)layout;
        T2* t2 = (T2*)(t1[s1]);
        T3* t3 = (T3*)(t2[s2]);
        T4* t4 = (T4*)(t3[s3]);
        uint32_t i;
        for (i = 0; i < s1; i++) t1[i].~T();
        for (i = 0; i < s2; i++) t2[i].~T();
        for (i = 0; i < s3; i++) t3[i].~T();
        for (i = 0; i < s4; i++) t4[i].~T();
        delete[] layout;
    }

}

#endif // !KLANG_HEAD_LAYOUT