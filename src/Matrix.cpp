#include "../include/Matrix.hpp"

float matrix::dot(V3& v1, V3& v2) {
    return v1.x() * v2.x() + v1.y() * v2.y() + v1.z() * v2.z();
}

V3 matrix::matmul_matrix_vector3(std::vector<V3>& matrix, V3& vector) {
    return V3(
        matrix::dot(matrix[0], vector),
        matrix::dot(matrix[1], vector),
        matrix::dot(matrix[2], vector)
    );
}

V2 matrix::matmul_matrix_vector2(std::vector<V3>& matrix, V3& vector) {
    return V2(
        matrix::dot(matrix[0], vector),
        matrix::dot(matrix[1], vector)
    );
}