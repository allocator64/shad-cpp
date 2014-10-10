#include <gtest/gtest.h>

#include <iostream>
#include <string>
#include <cstring>

std::string getDayName(std::string date) {
    struct tm tm;
    memset(&tm, 0, sizeof(tm));
    int day, month, year;
    if (!(sscanf(date.c_str(), "%d.%d.%d", &day, &month, &year) == 3)) {
        std::cerr << "Incorrect format" << std::endl;
        return "";
    }
    tm.tm_year = year - 1900;
    tm.tm_mon = month - 1;
    tm.tm_mday = day;
    time_t timestamp = mktime(&tm);
    if (timestamp == -1) {
        std::cerr << "Incorrect date" << std::endl;
        return "";
    }
    localtime_r(&timestamp, &tm);
    char buf[100];
    strftime(buf, sizeof(buf), "%A", &tm);
    buf[sizeof(buf) - 1] = '\0';
    return std::string(buf);
}

bool isLeapYear(int year) {
    return (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
}


struct test_t : public ::testing::Test {
};

TEST_F(test_t, dates) {
    EXPECT_EQ("Friday", getDayName("10.10.2014"));
    EXPECT_EQ("Saturday", getDayName("11.10.2014"));
    EXPECT_EQ("Sunday", getDayName("12.10.2014"));
    EXPECT_EQ("Monday", getDayName("13.10.2014"));
    EXPECT_EQ("Tuesday", getDayName("14.10.2014"));
    EXPECT_EQ("Wednesday", getDayName("15.10.2014"));
    EXPECT_EQ("Thursday", getDayName("16.10.2014"));
}

TEST_F(test_t, years) {
    EXPECT_TRUE(isLeapYear(2012));
    EXPECT_TRUE(isLeapYear(2016));
    EXPECT_TRUE(isLeapYear(2000));

    EXPECT_FALSE(isLeapYear(2100));
    EXPECT_FALSE(isLeapYear(2013));
    EXPECT_FALSE(isLeapYear(2014));
    EXPECT_FALSE(isLeapYear(2015));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

