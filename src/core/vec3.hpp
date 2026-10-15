#pragma once

#include <cmath>

namespace stage {

// Three numbers: a position in the room, or an arrow (direction + distance).
struct Vec3 {
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
};

// Add: walk along arrow a, then along arrow b. Where do you end up?
constexpr Vec3 operator+(Vec3 a, Vec3 b) { return {a.x + b.x, a.y + b.y, a.z + b.z}; }

// Subtract: the arrow that goes from b to a.
constexpr Vec3 operator-(Vec3 a, Vec3 b) { return {a.x - b.x, a.y - b.y, a.z - b.z}; }

// Negate: flip the arrow around.
constexpr Vec3 operator-(Vec3 v) { return {-v.x, -v.y, -v.z}; }

// Scale: make the arrow longer (s > 1) or shorter (s < 1).
constexpr Vec3 operator*(Vec3 v, float s) { return {v.x * s, v.y * s, v.z * s}; }
constexpr Vec3 operator*(float s, Vec3 v) { return v * s; }
constexpr Vec3 operator/(Vec3 v, float s) { return {v.x / s, v.y / s, v.z / s}; }

// Dot: how much two arrows point the same way.
// Positive = same-ish direction, 0 = at right angles, negative = opposite.
constexpr float dot(Vec3 a, Vec3 b) { return a.x * b.x + a.y * b.y + a.z * b.z; }

// Cross: a new arrow sticking straight out from both a and b.
constexpr Vec3 cross(Vec3 a, Vec3 b) {
    return {a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x};
}

// Length squared: cheaper than length (no square root). Good for comparing distances.
constexpr float length_squared(Vec3 v) { return dot(v, v); }

// Length: how long the arrow is.
inline float length(Vec3 v) { return std::sqrt(length_squared(v)); }

// Normalized: same direction, but exactly 1 long. A pure "which way."
inline Vec3 normalized(Vec3 v) {
    float len = length(v);
    if (len == 0.0f) return {};
    return v / len;
}

} // namespace stage