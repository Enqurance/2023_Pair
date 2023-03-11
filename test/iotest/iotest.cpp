#include <gtest/gtest.h>
#include "../../src/FileIO.h"
#include "string"

// 测试套件示例
class FileIOTest : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

FileIO f;

// 测试用例1
TEST_F(FileIOTest, Test1) {
    string filename = "../test/Testfiles/input.txt";
    int len;
    EXPECT_EQ(f.read_file(filename), 1);
    EXPECT_EQ(f.output_file(f.get_words(len)), 1);
    ASSERT_EQ(len, 20);
    string wrong_filename = "../test/Testfiles/inpvt.txt";
    EXPECT_EQ(f.read_file(wrong_filename), -1);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
