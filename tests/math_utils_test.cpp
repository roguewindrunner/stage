#include <gtest/gtest.h>
#include "core/math_utils.hpp"

TEST(Clamp, ReturnsValueWhenInRange) {
    EXPECT_FLOAT_EQ(stage::clamp(5.0f, 0.0f, 10.0f), 5.0f);
}

TEST(Clamp, ReturnsMinWhenBelow) {
    EXPECT_FLOAT_EQ(stage::clamp(-3.0f, 0.0f, 10.0f), 0.0f);
}

TEST(Clamp, ReturnsMaxWhenAbove) {
    EXPECT_FLOAT_EQ(stage::clamp(15.0f, 0.0f, 10.0f), 10.0f);
}

TEST(Lerp, ReturnsStartWhenTIsZero) {
    EXPECT_FLOAT_EQ(stage::lerp(2.0f, 8.0f, 0.0f), 2.0f);
}

TEST(Lerp, ReturnsEndWhenTIsOne) {
    EXPECT_FLOAT_EQ(stage::lerp(2.0f, 8.0f, 1.0f), 8.0f);
}

TEST(Lerp, ReturnsMidpointWhenTIsHalf) {
    EXPECT_FLOAT_EQ(stage::lerp(2.0f, 8.0f, 0.5f), 5.0f);
}