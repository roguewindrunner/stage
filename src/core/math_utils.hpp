#pragma once

namespace stage {

// Keeps value between min and max.
float clamp(float value, float min, float max);

// Linear interpolation: t = 0 gives a, t = 1 gives b, t = 0.5 gives halfway.
float lerp(float a, float b, float t);

} // namespace stage