#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <vector>
#include "./Vector.hpp"

namespace matrix {
    float dot(V3& v1, V3& v2);

    V3 matmul_matrix_vector3(std::vector<V3>& matrix, V3& vector);
    V2 matmul_matrix_vector2(std::vector<V3>& matrix, V3& vector);
}

#endif