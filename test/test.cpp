#include <gtest/gtest.h>
#include <gzCrypt.hpp>

using namespace gzCrypt::bigint_literals;

TEST(gzCrypt, UnsignedComparison)
{
    gzCrypt::biguint x;
    EXPECT_EQ(x, 0);

    gzCrypt::biguint y = 9;

    gzCrypt::biguint z = 14;

    EXPECT_LT(x, y);
    EXPECT_LT(y, z);
    EXPECT_LT(x, z);

    EXPECT_GT(y, x);
    EXPECT_GT(z, y);
    EXPECT_GT(z, x);

    EXPECT_EQ(x, x);
    EXPECT_EQ(y, y);
    EXPECT_EQ(z, z);

    EXPECT_NE(x, y);
    EXPECT_NE(y, z);
    EXPECT_NE(z, x);
}

TEST(gzCrypt, UnsignedIncrement)
{
    gzCrypt::biguint x;

    EXPECT_EQ(x++, 0);
    EXPECT_EQ(x, 1);

    EXPECT_EQ(++x, 2);

}


TEST(gzCrypt, UnsignedAddition)
{
    gzCrypt::biguint x = 5;

    gzCrypt::biguint y = 9;

    ASSERT_EQ(x + y, 14);
    ASSERT_EQ(y + x, 14);
}

TEST(gzCrypt, UnsignedDecrement)
{
    gzCrypt::biguint x = 2;

    ASSERT_EQ(x--, 2);
    ASSERT_EQ(x, 1);

    ASSERT_EQ(--x, 0);

    ASSERT_ANY_THROW(--x);

}


TEST(gzCrypt, UnsignedSubtraction)
{
    gzCrypt::biguint x = 9;

    gzCrypt::biguint y = 5;

    EXPECT_EQ(x - y, 4);
    EXPECT_ANY_THROW(y - x);

    EXPECT_EQ(x - 0, x);

    EXPECT_EQ(x - x, 0);
}

TEST(gzCrypt, UnsignedMultiplication)
{
    gzCrypt::biguint x = 9;

    gzCrypt::biguint y = 5;

    EXPECT_EQ(x * y, 45);
    EXPECT_EQ(x * 1, x);
    EXPECT_EQ(x * 0, 0);

    EXPECT_EQ(y * x, 45);
    EXPECT_EQ(1 * x, x);
    EXPECT_EQ(0 * x, 0);
}

TEST(gzCrypt, UnsignedDivision)
{
    gzCrypt::biguint x = 92312_ubig;

    gzCrypt::biguint y = 5;

    EXPECT_EQ(x / y, 18462_ubig);
    EXPECT_EQ(x / 1, x);
    EXPECT_ANY_THROW(x / 0);

    EXPECT_EQ(y / x, 0);
    EXPECT_EQ(1 / y, 0);
    EXPECT_EQ(0 / y, 0);
}
