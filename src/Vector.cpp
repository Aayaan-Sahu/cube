#include "../include/Vector.hpp"

V2::V2() {
    this->array[0] = 0.0;
    this->array[1] = 0.0;
}

V2::V2(float x, float y) {
    this->array[0] = x;
    this->array[1] = y;
}

const float V2::x() {
    return this->array[0];
}

const float V2::y() {
    return this->array[1];
}

float V2::operator[](size_t index) {
    return this->array[index];
}

V3::V3() {
    this->array[0] = 0.0;
    this->array[1] = 0.0;
    this->array[2] = 0.0;
}

V3::V3(float x, float y, float z) {
    this->array[0] = x;
    this->array[1] = y;
    this->array[2] = z;
}

const float V3::x() {
    return this->array[0];
}

const float V3::y() {
    return this->array[1];
}

const float V3::z() {
    return this->array[2];
}

float V3::operator[](size_t index) {
    return this->array[index];
}