#include <gtest/gtest.h>
#include "../../src/FileIO.h"

// 测试套件示例
class MyTestSuite : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// 测试用例1
TEST_F(MyTestSuite, Test1) {
    EXPECT_EQ(1, 1);
}

// 测试用例2
TEST_F(MyTestSuite, Test2) {
    EXPECT_TRUE(false);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
