#include "../include/Engine.hpp"

#include <cmath>

namespace engine {

    namespace {

        Line calculate_points_within_line(int x1, int y1, int x2, int y2) {
            std::vector<V2> points;

            if (x1 == x2 && y1 == y2) { // check if they are the same points
                points.push_back(V2(x1, y1));
                return Line(points, LINE_TYPE::VERTICAL);
            } else if (x1 == x2 && y1 != y2) { // check if vertical line
                auto miny = std::min(y1, y2);
                auto maxy = std::max(y1, y2);
                for (int i = miny; i <= maxy; i++) {
                    points.push_back(V2(x1, i));
                }
                return Line(points, LINE_TYPE::VERTICAL);
            } else if (y1 == y2 && x1 != x2) { // check if horizontal line
                auto minx = std::min(x1, x2);
                auto maxx = std::max(x1, x2);
                for (int i = minx; i <= maxx; i++) {
                    points.push_back(V2(i, y1));
                }
                return Line(points, LINE_TYPE::HORIZONTAL);
            } else { // diagonal line
                float dx = (float)(x2 - x1);
                float dy = (float)(y2 - y1);
                float slope = (float)dy / (float)dx;

                auto minx = std::min(x1, x2);
                auto maxx = std::max(x1, x2);
                auto miny = (minx == x1) ? y1 : y2;
                auto maxy = (miny == y1) ? y2 : y1;

                if (slope > 0 && slope < 1) {
                    float x = minx, y = miny;

                    while (true) {
                        if (std::round(x) == maxx) { // quit condition
                            if (std::round(y) == maxy) {
                                break;
                            }
                        }
                        points.push_back(V2(std::round(x), std::round(y)));
                        ++x;
                        y += slope;
                    }

                    return Line(points, LINE_TYPE::DIAGONAL_RIGHT);
                } else if (slope == 1) {
                    float x = minx, y = miny;

                    while (true) {
                        if (x == maxx) { // quit condition
                            if (y == maxy) {
                                break;
                            }
                        }
                        points.push_back(V2(x, y));
                        ++x, ++y;
                    }

                    return Line(points, LINE_TYPE::DIAGONAL_RIGHT);
                } else if (slope > 1) {
                    float x = minx, y = miny;

                    while (true) {
                        if (std::round(x) >= maxx) { // quit condition
                            if (std::round(y) >= maxy) {
                                break;
                            }
                        }
                        points.push_back(V2(std::round(x), std::round(y)));
                        ++y;
                        x += 1.0 / slope;
                    }

                    return Line(points, LINE_TYPE::DIAGONAL_RIGHT);
                } else if (slope > -1 || slope < 0) {
                    float x = maxx, y = maxy;

                    while (true) {
                        if (std::round(x) == minx) { // quit condition
                            if (std::round(y) == miny) {
                                break;
                            }
                        }
                        points.push_back(V2(std::round(x), std::round(y)));
                        --x;
                        y -= slope;
                    }

                    return Line(points, LINE_TYPE::DIAGONAL_RIGHT);
                } else if (slope == -1) {
                    float x = maxx, y = miny;

                    while (true) {
                        if (x == minx) { // quit condition
                            if (y == maxy) {
                                break;
                            }
                        }
                        points.push_back(V2(x, y));
                        --x, ++y;
                    }

                    return Line(points, LINE_TYPE::DIAGONAL_LEFT);
                } else if (slope < -1) {
                    float x = maxx, y = miny;

                    while (true) {
                        if (std::round(x) <= minx) { // quit condition
                            if (std::round(y) >= maxy) {
                                break;
                            }
                        }
                        points.push_back(V2(std::round(x), std::round(y)));
                        ++y;
                        x -= 1.0 / slope;
                    }

                    return Line(points, LINE_TYPE::DIAGONAL_LEFT);
                }
            }

            return Line({}, LINE_TYPE::NONE);
        }

    }


    void line(
        int x1, int y1,
        int x2, int y2,
        std::function<void(int x, int y, size_t max_cols, size_t max_rows, wchar_t c)> plot,
        size_t max_cols, size_t max_rows
    ) {
        auto line = calculate_points_within_line(x1, y1, x2, y2);  // find out places to draw b/w two points
        if (line.line_type == LINE_TYPE::VERTICAL) {
            for (auto& point : line.points) {
                plot(point.x(), point.y(), max_cols, max_rows, '|');
            }
        } else if (line.line_type == LINE_TYPE::HORIZONTAL) {
            for (auto& point : line.points) {
                plot(point.x(), point.y(), max_cols, max_rows, '^');
            }
        } else if (line.line_type == LINE_TYPE::DIAGONAL_LEFT) {
            for (auto& point : line.points) {
                plot(point.x(), point.y(), max_cols, max_rows, '\\');
            }
        } else if (line.line_type == LINE_TYPE::DIAGONAL_RIGHT) {
            for (auto& point : line.points) {
                plot(point.x(), point.y(), max_cols, max_rows, '/');
            }
        }
    }

}