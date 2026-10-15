#include <gtest/gtest.h>
#include "core/vec3.hpp"

using stage::Vec3;

// Helper: check all three numbers match.
static void expect_vec3_eq(Vec3 actual, Vec3 expected) {
    EXPECT_FLOAT_EQ(actual.x, expected.x);
    EXPECT_FLOAT_EQ(actual.y, expected.y);
    EXPECT_FLOAT_EQ(actual.z, expected.z);
}

// static_assert = a test that runs while COMPILING.
// If it's wrong, the code won't even build. This proves constexpr works.
static_assert(stage::dot(Vec3{1, 0, 0}, Vec3{0, 1, 0}) == 0.0f);
static_assert((Vec3{1, 2, 3} + Vec3{1, 1, 1}).x == 2.0f);

TEST(Vec3, Add) { expect_vec3_eq(Vec3{1, 2, 3} + Vec3{4, 5, 6}, Vec3{5, 7, 9}); }

TEST(Vec3, Subtract) { expect_vec3_eq(Vec3{5, 7, 9} - Vec3{4, 5, 6}, Vec3{1, 2, 3}); }

TEST(Vec3, Negate) { expect_vec3_eq(-Vec3{1, -2, 3}, Vec3{-1, 2, -3}); }

TEST(Vec3, ScaleVectorTimesNumber) { expect_vec3_eq(Vec3{1, 2, 3} * 2.0f, Vec3{2, 4, 6}); }

TEST(Vec3, ScaleNumberTimesVector) { expect_vec3_eq(2.0f * Vec3{1, 2, 3}, Vec3{2, 4, 6}); }

TEST(Vec3, Divide) { expect_vec3_eq(Vec3{2, 4, 6} / 2.0f, Vec3{1, 2, 3}); }

TEST(Vec3, DotOfRightAnglesIsZero) {
    EXPECT_FLOAT_EQ(stage::dot(Vec3{1, 0, 0}, Vec3{0, 0, 1}), 0.0f);
}

TEST(Vec3, DotOfSameDirectionIsPositive) {
    EXPECT_FLOAT_EQ(stage::dot(Vec3{2, 0, 0}, Vec3{3, 0, 0}), 6.0f);
}

TEST(Vec3, CrossOfRightAndUpIsTowardCamera) {
    expect_vec3_eq(stage::cross(Vec3{1, 0, 0}, Vec3{0, 1, 0}), Vec3{0, 0, 1});
}

TEST(Vec3, LengthOfThreeFourIsFive) { EXPECT_FLOAT_EQ(stage::length(Vec3{3, 4, 0}), 5.0f); }

TEST(Vec3, NormalizedHasLengthOne) {
    EXPECT_FLOAT_EQ(stage::length(stage::normalized(Vec3{3, 4, 0})), 1.0f);
}

TEST(Vec3, NormalizedZeroStaysZero) { expect_vec3_eq(stage::normalized(Vec3{}), Vec3{}); }