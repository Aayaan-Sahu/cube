#ifndef VEC_HPP
#define VEC_HPP

#include <cstdio>

struct V2 {
    float array[2];

    V2();
    V2(float x, float y);

    const float x();
    const float y();

    float operator[](size_t index);
};

struct V3 {
    float array[3];

    V3();
    V3(float x, float y, float z);

    const float x();
    const float y();
    const float z();

    float operator[](size_t index);
};

#endif