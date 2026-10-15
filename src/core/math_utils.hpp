#pragma once

namespace stage {

// Keeps value between min and max.
float clamp(float value, float min, float max);

// Linear interpolation: t = 0 gives a, t = 1 gives b, t = 0.5 gives halfway.
float lerp(float a, float b, float t);

// Pi: half a circle, in radians.
constexpr float pi = 3.14159265358979f;

// Degrees -> radians. 90 degrees = a quarter turn.
constexpr float to_radians(float degrees) { return degrees * (pi / 180.0f); }

} // namespace stage