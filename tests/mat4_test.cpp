#include "core/mat4.hpp"
#include "core/math_utils.hpp"
#include <gtest/gtest.h>

using stage::Mat4;
using stage::Vec3;

// Computers can't store pi perfectly, so rotations leave tiny crumbs
// like 0.00000004 instead of 0. EXPECT_NEAR allows a small tolerance.
static void expect_vec3_near(Vec3 actual, Vec3 expected) {
    constexpr float tolerance = 1e-5f;
    EXPECT_NEAR(actual.x, expected.x, tolerance);
    EXPECT_NEAR(actual.y, expected.y, tolerance);
    EXPECT_NEAR(actual.z, expected.z, tolerance);
}

// Compile-time checks.
static_assert(Mat4::identity().at(3, 3) == 1.0f);
static_assert(stage::transform_point(stage::translation({1, 2, 3}), Vec3{}).z == 3.0f);

TEST(Mat4, IdentityLeavesPointAlone) {
    expect_vec3_near(stage::transform_point(Mat4::identity(), {1, 2, 3}), {1, 2, 3});
}

TEST(Mat4, TranslationMovesPoint) {
    expect_vec3_near(stage::transform_point(stage::translation({2, 0, 3}), {1, 1, 1}), {3, 1, 4});
}

TEST(Mat4, TranslationDoesNotMoveDirection) {
    expect_vec3_near(stage::transform_direction(stage::translation({2, 0, 3}), {0, 0, 1}),
                     {0, 0, 1});
}

TEST(Mat4, ScalingResizes) {
    expect_vec3_near(stage::transform_point(stage::scaling({2, 2, 2}), {1, 2, 3}), {2, 4, 6});
}

TEST(Mat4, RotateY90TurnsRightIntoAway) {
    Mat4 turn = stage::rotation_y(stage::to_radians(90.0f));
    expect_vec3_near(stage::transform_direction(turn, {1, 0, 0}), {0, 0, -1});
}

// Order matters: "turn, then move" vs "move, then turn".
TEST(Mat4, TurnThenMove) {
    Mat4 recipe = stage::translation({1, 0, 0}) * stage::rotation_y(stage::to_radians(90.0f));
    expect_vec3_near(stage::transform_point(recipe, {0, 0, 0}), {1, 0, 0});
}

TEST(Mat4, MoveThenTurn) {
    Mat4 recipe = stage::rotation_y(stage::to_radians(90.0f)) * stage::translation({1, 0, 0});
    expect_vec3_near(stage::transform_point(recipe, {0, 0, 0}), {0, 0, -1});
}