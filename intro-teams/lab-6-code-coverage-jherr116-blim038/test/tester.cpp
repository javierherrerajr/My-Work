#include <gtest/gtest.h>

#include "../lib/testsubject.h"

TEST(MathTest, Square) {
    ASSERT_EQ(TestSubject::square(2), 4);
    ASSERT_EQ(TestSubject::square(3), 9);
}