#include "gtest/gtest.h"

int my_function(int a, int b) {
    return a + b;
}

TEST(MyTest, TestMyFunction) {
    // 调用 my_function 并断言其返回值是否等于 3
    EXPECT_EQ(my_function(1, 2), 3);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
