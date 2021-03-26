#include "gtest/gtest.h"

TEST(MyTest, Passing)
{
    ASSERT_TRUE(true);
}

TEST(MyTest, Failing)
{
    ASSERT_TRUE(false);
}