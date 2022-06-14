#include "../include/Cube.hpp"
#include "../include/Engine.hpp"

#include <cmath>
#include <cstdlib>
#include <fstream>
#include <functional>
#include <string>

Cube::Cube() {
    this->points = {
        V3(-0.5, -0.5, -0.5),
        V3( 0.5, -0.5, -0.5),
        V3( 0.5,  0.5, -0.5),
        V3(-0.5,  0.5, -0.5),
        V3(-0.5, -0.5,  0.5),
        V3( 0.5, -0.5,  0.5),
        V3( 0.5,  0.5,  0.5),
        V3(-0.5,  0.5,  0.5),
    };

    this->orthographic_projection_matrix = {
        V3(1.0, 0.0, 0.0),
        V3(0.0, 1.0, 0.0),
    };

    this->angle = 0.0;
}

void Cube::update() {
    this->rotation_x.clear();
    this->rotation_x.push_back(V3(1.0, 0.0, 0.0));
    this->rotation_x.push_back(V3(0.0, std::cos(this->angle), -std::sin(this->angle)));
    this->rotation_x.push_back(V3(0.0, std::sin(this->angle), std::cos(this->angle)));

    this->rotation_y.clear();
    this->rotation_y.push_back(V3(std::cos(this->angle), 0.0, -std::sin(this->angle)));
    this->rotation_y.push_back(V3(0.0, 1.0, 0.0));
    this->rotation_y.push_back(V3(std::sin(this->angle), 0.0, std::cos(this->angle)));

    this->rotation_z.clear();
    this->rotation_z.push_back(V3(std::cos(this->angle), -std::sin(this->angle), 0.0));
    this->rotation_z.push_back(V3(std::sin(this->angle),  std::cos(this->angle), 0.0));
    this->rotation_z.push_back(V3(0.0, 0.0, 1.0));

    this->angle += 0.02;
}

void Cube::display(std::function<void(int x, int y, size_t max_cols, size_t max_rows, wchar_t c)> plot, size_t max_cols, size_t max_rows) {
    std::vector<V2> points_to_connect;

    for (auto& point : this->points) {
        auto rotated_point = matrix::matmul_matrix_vector3(this->rotation_x, point);
        rotated_point = matrix::matmul_matrix_vector3(this->rotation_y, rotated_point);
        rotated_point = matrix::matmul_matrix_vector3(this->rotation_z, rotated_point);

        auto projected_point = matrix::matmul_matrix_vector2(this->orthographic_projection_matrix, rotated_point);
        auto final_projected_point = V2(projected_point.x() * 20.0, projected_point.y() * 10.0);
        points_to_connect.push_back(final_projected_point);
    }

    for (auto i = 0; i < 4; i++) {
        engine::line( // front face
            points_to_connect[i].x(), points_to_connect[i].y(),
            points_to_connect[(i + 1) % 4].x(), points_to_connect[(i + 1) % 4].y(),
            plot,
            max_cols, max_rows
        );

        engine::line( // back face
            points_to_connect[i + 4].x(), points_to_connect[i + 4].y(),
            points_to_connect[((i + 1) % 4) + 4].x(), points_to_connect[((i + 1) % 4) + 4].y(),
            plot,
            max_cols, max_rows
        );

        engine::line( // connecting front and back faces
            points_to_connect[i].x(), points_to_connect[i].y(),
            points_to_connect[i + 4].x(), points_to_connect[i + 4].y(),
            plot,
            max_cols, max_rows
        );
    }
}