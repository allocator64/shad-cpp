#include <gtest/gtest.h>

#include <vector>
#include <algorithm>

template<typename T>
void rotate(T begin, T end, int k) {
    size_t size = std::distance(begin, end);
    while (k < 0) {
        k += size;
    }

    k %= size;

    while (k--) {
        for (T i = begin + 1; i != end; ++i) {
            std::swap(*begin, *i);
        }
    }
}

struct test_t : public ::testing::Test {
};

TEST_F(test_t, rotate) {
    std::vector<int> v = {1, 2, 3, 4};
    rotate(v.begin(), v.end(), 1);
    EXPECT_EQ(std::vector<int>({4, 1, 2, 3}), v);
    int a[3] = {1, 2, 3};
    rotate(a, a + 3, -4);
    EXPECT_EQ(std::vector<int>({2, 3, 1}), std::vector<int>(a, a + 3));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

