#include "gtest/gtest.h"
#include "../include/Hailstone.h"

using sequence::satisfiesHailstone;

TEST(HailstoneTests, SatisfiesHailstone) {
    // Test various inputs to cover different branches in the function
    EXPECT_FALSE(sequence::satisfiesHailstone(0));  // Should return false
    EXPECT_TRUE(sequence::satisfiesHailstone(1));   // Should return true
    EXPECT_TRUE(sequence::satisfiesHailstone(4));   // Should return true
    EXPECT_TRUE(sequence::satisfiesHailstone(5));   // Should return true
}