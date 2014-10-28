#include <gtest/gtest.h>

#include <vector>
#include <algorithm>
#include <tuple>

struct test_t : public ::testing::Test {
};

TEST_F(test_t, some1) {
    auto expected = [](int b, int c, int d) {
        return b + c * d << 2 & 8;
    };

    auto actual = [](int b, int c, int d) {
        return ((b + (c * d)) << 2) & 8;
    };


    int size = 10;
    std::vector<int> val(size);
    std::iota(val.begin(), val.end(), -size/2);

    for (int b : val)
        for (int c : val)
            for (int d : val) {
                // std::cout << b << " " << c << " " << d << std::endl;
                EXPECT_EQ(expected(b, c, d), actual(b, c, d));
            }
}

TEST_F(test_t, some2) {
    auto actual = [](int x) {
        bool c = x != 0;
        return c;
    };

    auto expected = [](int x) {
        bool c = (x != 0);
        return c;
    };

    int size = 10;
    std::vector<int> val(size);
    std::iota(val.begin(), val.end(), -size/2);

    for (int x : val)
        EXPECT_EQ(expected(x), actual(x));
}

TEST_F(test_t, some3) {
    auto actual = [](int i) {
        return 0 <= i < 7;
    };

    auto expected = [](int i) {
        return ((0 <= i) ? 1 : 0) < 7;
    };

    int size = 20;
    std::vector<int> val(size);
    std::iota(val.begin(), val.end(), -size/2);

    for (int x : val)
        EXPECT_EQ(expected(x), actual(x));
}

TEST_F(test_t, some4) {
    auto actual = []() {
        return 1, 2+3;
    };

    auto expected = []() {
        return 2+3;
    };

    auto actual2 = [](int *a) {
        return *a = 1, 2+3;
    };

    auto expected2 = [](int *a) {
        *a = 1;
        return 2+3;
    };

    EXPECT_EQ(expected(), actual());
    int a1 = -1, a2 = -1;
    EXPECT_EQ(expected2(&a1), actual2(&a2));
    EXPECT_EQ(a1, a2);
}

TEST_F(test_t, some5) {
    auto actual = [](int &b) {
        return - 1 + + b - - 5;
    };

    auto expected = [](int &b) {
        return (((- 1) + (+ b)) - (- 5));
    };

    int b1 = 0;
    int b2 = 0;

    EXPECT_EQ(actual(b1), expected(b2));
    EXPECT_EQ(b1, b2);
}

TEST_F(test_t, some6) {
    auto actual = [](int &a, int &b, int &c) {
        a = b == c++;
    };

    auto expected = [](int &a, int &b, int &c) {
        c++;
        a = (b == (c - 1));
    };

    int a = 0, a2 = 0;
    int b = 0, b2 = 0;
    int c = 0, c2 = 0;

    actual(a, b, c);
    expected(a2, b2, c2);

    EXPECT_EQ(std::make_tuple(a, b, c), std::make_tuple(a2, b2, c2));
}

TEST_F(test_t, some7) {

    auto actual = [](int *b, int c, int *d) {
        int a = 1;
        a *=* b ? c : *d*2;
        return a;
    };

    auto expected = [](int *b, int c, int *d) {
        int a = 1;
        a *= ((*b) ? (c) : ((*d) * 2));
        return a;
    };

    int size = 20;
    std::vector<int> val(size);
    std::iota(val.begin(), val.end(), -size/2);

    for (int b : val)
        for (int c : val)
            for (int d : val)
                EXPECT_EQ(expected(&b, c, &d), actual(&b, c, &d));
}

TEST_F(test_t, some8) {
    int x[2] = {1, 2};

    int *p1 = &x[1];
    int v1 = *--p1;

    int *p2 = &x[1];
    int v2 = *(--p2);
    EXPECT_EQ(1, v1);
    EXPECT_EQ(1, v2);
}

TEST_F(test_t, some9) {
    struct data {
        void *m;
        data()
        {
            m = malloc(sizeof(int));
            *(int *)m = 123;
        }
        ~data()
        {
            if (m)
                free(m);
        }
    };

    data d;
    data *p = &d;

    EXPECT_EQ((int *)(p->m), (int*)p->m);

}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
