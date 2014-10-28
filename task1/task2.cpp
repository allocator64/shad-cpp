#include <gtest/gtest.h>

#include <iostream>

int gcdex(int a, int b, int *x, int *y) {
    if (a == 0) {
        *x = 0;
        *y = 1;
        return b;
    }
    int x1, y1;
    int d = gcdex(b%a, a, &x1, &y1);
    *x = y1 - (b / a) * x1;
    *y = x1;
    return d;
}

int inverse(int a, int m) {
    int x, y;
    if (gcdex(a, m, &x, &y) == 1) {
        return (x % m + m) % m;
    }
    return -1;
}

struct test_t : public ::testing::Test {
};

TEST_F(test_t, gcdex) {
    int x, y;
    EXPECT_EQ(5, gcdex(5, 10, &x, &y));
    EXPECT_EQ(5, 5*x + 10*y);

    EXPECT_EQ(1, gcdex(5, 7, &x, &y));
    EXPECT_EQ(1, 5*x + 7*y);
}

TEST_F(test_t, inverse) {
    EXPECT_EQ(3, inverse(2, 5));
    EXPECT_EQ(4, inverse(2, 7));
    EXPECT_EQ(-1, inverse(10, 15));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

