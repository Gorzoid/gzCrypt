#include <gtest/gtest.h>
#include <gzCrypt.hpp>

TEST(gzCrypt, Comparison)
{
    gzCrypt::bigint x;

    gzCrypt::bigint y = 9;

    gzCrypt::bigint z = 14;

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


TEST(gzCrypt, Addition)
{
    gzCrypt::bigint x = 5;

    gzCrypt::bigint y = 9;

    gzCrypt::bigint z = 14;

    EXPECT_EQ(x + y, z);

    z = 0x7FFFFFFFFFFFFFFF;

    EXPECT_GT(z + z, z);

    EXPECT_GT(z + z + z, z + z);

    EXPECT_GT(z + z + z + z, z + z + z);

}

TEST(gzCrypt, NegativeAddition)
{
    gzCrypt::bigint x = -5;

    gzCrypt::bigint y = 9;

    gzCrypt::bigint z = 14;

    EXPECT_EQ(x + y, z);
    EXPECT_EQ(y + x, z);
}

