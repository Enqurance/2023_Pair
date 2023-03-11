#include <gtest/gtest.h>
#include "../../src/Core.h"
#include "../../src/FileIO.h"
#include "string"

// 测试套件示例
class CoreTest : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// 测试用例1
TEST_F(CoreTest, Test1) {
    int words_size;
    FileIO f;
    string filename = "../tests/Testfiles/input1.txt";
    vector<string> words = f.get_words(words_size);
    EXPECT_EQ(f.output_file(f.get_words(words_size)), 1);
    ASSERT_EQ(words_size, 20);

    /* 准备工作完成，开始测试 */
    Core core = *new Core(words, words_size);
    vector<vector<string>> result;
    gen_chains_all(words, words_size, result);
}

//测试用例2
TEST_F(CoreTest, Test2) {
    int words_size;
    FileIO f;
    string filename = "../tests/Testfiles/input2.txt";
    vector<string> words = f.get_words(words_size);
    EXPECT_EQ(f.output_file(f.get_words(words_size)), 1);
    ASSERT_EQ(words_size, 20);
    /* 准备工作完成，开始测试 */
    Core core = *new Core(words, words_size);
    vector<vector<string>> result;
    gen_chains_all(words, words_size, result);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
