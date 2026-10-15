#pragma once

#include <cmath>

#include "core/vec3.hpp"

namespace stage {

// A 4x4 grid of numbers: a recipe for resizing, turning, and moving things.
// Stored column by column, the same layout OpenGL and raylib use.
struct Mat4 {
    float m[16] = {};

    // Read or write the number at (row, col).
    constexpr float& at(int row, int col) { return m[col * 4 + row]; }
    constexpr float at(int row, int col) const { return m[col * 4 + row]; }

    // The "do nothing" recipe: 1s down the diagonal, 0s everywhere else.
    static constexpr Mat4 identity() {
        Mat4 r;
        r.at(0, 0) = 1.0f;
        r.at(1, 1) = 1.0f;
        r.at(2, 2) = 1.0f;
        r.at(3, 3) = 1.0f;
        return r;
    }
};

// Glue two recipes into one. a * b means: do b FIRST, then a.
constexpr Mat4 operator*(const Mat4& a, const Mat4& b) {
    Mat4 r;
    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < 4; ++col) {
            float sum = 0.0f;
            for (int k = 0; k < 4; ++k) {
                sum += a.at(row, k) * b.at(k, col);
            }
            r.at(row, col) = sum;
        }
    }
    return r;
}

// Recipe: slide everything by t.
constexpr Mat4 translation(Vec3 t) {
    Mat4 r = Mat4::identity();
    r.at(0, 3) = t.x;
    r.at(1, 3) = t.y;
    r.at(2, 3) = t.z;
    return r;
}

// Recipe: resize. {2, 2, 2} = twice as big in every direction.
constexpr Mat4 scaling(Vec3 s) {
    Mat4 r = Mat4::identity();
    r.at(0, 0) = s.x;
    r.at(1, 1) = s.y;
    r.at(2, 2) = s.z;
    return r;
}

// Recipe: spin around the up (y) axis, like turning a chair in place.
inline Mat4 rotation_y(float radians) {
    float c = std::cos(radians);
    float s = std::sin(radians);
    Mat4 r = Mat4::identity();
    r.at(0, 0) = c;
    r.at(0, 2) = s;
    r.at(2, 0) = -s;
    r.at(2, 2) = c;
    return r;
}

// Apply a recipe to a POINT (a place). Points get moved by translation.
constexpr Vec3 transform_point(const Mat4& m, Vec3 p) {
    return {m.at(0, 0) * p.x + m.at(0, 1) * p.y + m.at(0, 2) * p.z + m.at(0, 3),
            m.at(1, 0) * p.x + m.at(1, 1) * p.y + m.at(1, 2) * p.z + m.at(1, 3),
            m.at(2, 0) * p.x + m.at(2, 1) * p.y + m.at(2, 2) * p.z + m.at(2, 3)};
}

// Apply a recipe to a DIRECTION (an arrow). Directions ignore translation.
constexpr Vec3 transform_direction(const Mat4& m, Vec3 d) {
    return {m.at(0, 0) * d.x + m.at(0, 1) * d.y + m.at(0, 2) * d.z,
            m.at(1, 0) * d.x + m.at(1, 1) * d.y + m.at(1, 2) * d.z,
            m.at(2, 0) * d.x + m.at(2, 1) * d.y + m.at(2, 2) * d.z};
}

} // namespace stage