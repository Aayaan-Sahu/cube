#ifndef CUBE_HPP
#define CUBE_HPP

#include "./Vector.hpp"
#include "./Matrix.hpp"

#include <vector>
#include <functional>

class Cube {
    private:
        std::vector<V3> points;
        std::vector<V3> orthographic_projection_matrix;
        std::vector<V3> rotation_x;
        std::vector<V3> rotation_y;
        std::vector<V3> rotation_z;
        float angle;

    public:
        Cube();

        void update();
        void display(
            std::function<void(int x, int y, size_t max_cols, size_t max_rows, wchar_t c)> plot,
            size_t max_cols, size_t max_rows
        );
};

#endif