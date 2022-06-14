#include "./Vector.hpp"

#include <vector>
#include <functional>

namespace engine {

    enum class LINE_TYPE {
        HORIZONTAL,
        VERTICAL,
        DIAGONAL_LEFT,
        DIAGONAL_RIGHT,
        NONE,
    };

    struct Line {
        std::vector<V2> points;
        LINE_TYPE line_type;
        Line(std::vector<V2> points, LINE_TYPE line_type) {
            this->points = points;
            this->line_type = line_type;
        }
    };

    void line(
        int fpp_x1, int fpp_y1,
        int fpp_x2, int fpp_y2,
        std::function<void(int x, int y, size_t max_cols, size_t max_rows, wchar_t c)> plot,
        size_t max_cols, size_t max_rows
    );

}