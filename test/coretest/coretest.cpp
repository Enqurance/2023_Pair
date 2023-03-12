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

// -n
TEST_F(CoreTest, Test_N) {
    int words_size;
    FileIO f;
    string filename = "../test/Testfiles/input1.txt";
    EXPECT_EQ(f.read_file(filename), 1);
    vector<string> words = f.get_words(words_size);
    ASSERT_EQ(words_size, 4);

    /* 准备工作完成，开始测试 */
    Core core = *new Core(words, words_size);
    vector<vector<string>> result;
    gen_chains_all(words, words_size, result);
    EXPECT_EQ(f.output_screen(result), 1);
}

// -w
TEST_F(CoreTest, Test_W) {
    int words_size;
    FileIO f;
    string filename = "../test/Testfiles/input2.txt";
    EXPECT_EQ(f.read_file(filename), 1);
    vector<string> words = f.get_words(words_size);
    ASSERT_EQ(words_size, 11);

    /* 准备工作完成，开始测试 */
    Core core = *new Core(words, words_size);
    vector<string> result;
    char c = 0;
    gen_chain_word(words, words_size, result, c, c, c, false);
    EXPECT_EQ(f.output_file(result), 1);    // 测试时，solution.txt在bin下
}

// -h -w
TEST_F(CoreTest, Test_H_W) {
    int words_size;
    FileIO f;
    string filename = "../test/Testfiles/input2.txt";
    EXPECT_EQ(f.read_file(filename), 1);
    vector<string> words = f.get_words(words_size);
    ASSERT_EQ(words_size, 11);

    /* 准备工作完成，开始测试 */
    Core core = *new Core(words, words_size);
    vector<string> result;
    char c = 0;
    gen_chain_word(words, words_size, result, 'e', c, c, false);
    EXPECT_EQ(f.output_file(result), 1);    // 测试时，solution.txt在bin下
}

// -t -w
TEST_F(CoreTest, Test_T_W) {
    int words_size;
    FileIO f;
    string filename = "../test/Testfiles/input2.txt";
    EXPECT_EQ(f.read_file(filename), 1);
    vector<string> words = f.get_words(words_size);
    ASSERT_EQ(words_size, 11);

    /* 准备工作完成，开始测试 */
    Core core = *new Core(words, words_size);
    vector<string> result;
    char c = 0;
    gen_chain_word(words, words_size, result, c, 't', c, false);
    EXPECT_EQ(f.output_file(result), 1);    // 测试时，solution.txt在bin下
}

// -j -w
TEST_F(CoreTest, Test_J_W) {
    int words_size;
    FileIO f;
    string filename = "../test/Testfiles/input2.txt";
    EXPECT_EQ(f.read_file(filename), 1);
    vector<string> words = f.get_words(words_size);
    ASSERT_EQ(words_size, 11);

    /* 准备工作完成，开始测试 */
    Core core = *new Core(words, words_size);
    vector<string> result;
    char c = 0;
    gen_chain_word(words, words_size, result, c, c, 'a', false);
    EXPECT_EQ(f.output_file(result), 1);    // 测试时，solution.txt在bin下
}


// -h -t -w
TEST_F(CoreTest, Test_H_T_W) {
    int words_size;
    FileIO f;
    string filename = "../test/Testfiles/input2.txt";
    EXPECT_EQ(f.read_file(filename), 1);
    vector<string> words = f.get_words(words_size);
    ASSERT_EQ(words_size, 11);

    /* 准备工作完成，开始测试 */
    Core core = *new Core(words, words_size);
    vector<string> result;
    char c = 0;
    gen_chain_word(words, words_size, result, 'a', 't', c, false);
    EXPECT_EQ(f.output_file(result), 1);    // 测试时，solution.txt在bin下
}

// -h -t -j -w
TEST_F(CoreTest, Test_H_T_J_W) {
    int words_size;
    FileIO f;
    string filename = "../test/Testfiles/input2.txt";
    EXPECT_EQ(f.read_file(filename), 1);
    vector<string> words = f.get_words(words_size);
    ASSERT_EQ(words_size, 11);

    /* 准备工作完成，开始测试 */
    Core core = *new Core(words, words_size);
    vector<string> result;
    char c = 0;
    gen_chain_word(words, words_size, result, 'a', 't', 'a', false);
    EXPECT_EQ(f.output_file(result), 1);    // 测试时，solution.txt在bin下
}

// -c
TEST_F(CoreTest, Test_C) {
    int words_size;
    FileIO f;
    string filename = "../test/Testfiles/input2.txt";
    EXPECT_EQ(f.read_file(filename), 1);
    vector<string> words = f.get_words(words_size);
    ASSERT_EQ(words_size, 11);

    /* 准备工作完成，开始测试 */
    Core core = *new Core(words, words_size);
    vector<string> result;
    char c = 0;
    gen_chain_char(words, words_size, result, c, c, c, false);
    EXPECT_EQ(f.output_file(result), 1);    // 测试时，solution.txt在bin下
}

// -h -c
TEST_F(CoreTest, Test_H_C) {
    int words_size;
    FileIO f;
    string filename = "../test/Testfiles/input2.txt";
    EXPECT_EQ(f.read_file(filename), 1);
    vector<string> words = f.get_words(words_size);
    ASSERT_EQ(words_size, 11);

    /* 准备工作完成，开始测试 */
    Core core = *new Core(words, words_size);
    vector<string> result;
    char c = 0;
    gen_chain_char(words, words_size, result, 'a', c, c, false);
    EXPECT_EQ(f.output_file(result), 1);    // 测试时，solution.txt在bin下
}

// -t -c
TEST_F(CoreTest, Test_T_C) {
    int words_size;
    FileIO f;
    string filename = "../test/Testfiles/input2.txt";
    EXPECT_EQ(f.read_file(filename), 1);
    vector<string> words = f.get_words(words_size);
    ASSERT_EQ(words_size, 11);

    /* 准备工作完成，开始测试 */
    Core core = *new Core(words, words_size);
    vector<string> result;
    char c = 0;
    gen_chain_char(words, words_size, result, c, 't', c, false);
    EXPECT_EQ(f.output_file(result), 1);    // 测试时，solution.txt在bin下
}

// -h -t -c
TEST_F(CoreTest, Test_H_T_C) {
    int words_size;
    FileIO f;
    string filename = "../test/Testfiles/input2.txt";
    EXPECT_EQ(f.read_file(filename), 1);
    vector<string> words = f.get_words(words_size);
    ASSERT_EQ(words_size, 11);

    /* 准备工作完成，开始测试 */
    Core core = *new Core(words, words_size);
    vector<string> result;
    char c = 0;
    gen_chain_char(words, words_size, result, 'a', 'e', c, false);
    EXPECT_EQ(f.output_file(result), 1);    // 测试时，solution.txt在bin下
}

// -h -t -j -c
TEST_F(CoreTest, Test_H_T_R_C) {
    int words_size;
    FileIO f;
    string filename = "../test/Testfiles/input2.txt";
    EXPECT_EQ(f.read_file(filename), 1);
    vector<string> words = f.get_words(words_size);
    ASSERT_EQ(words_size, 11);

    /* 准备工作完成，开始测试 */
    Core core = *new Core(words, words_size);
    vector<string> result;
    gen_chain_char(words, words_size, result, 'a', 'e', 'a', false);
    EXPECT_EQ(f.output_file(result), 1);    // 测试时，solution.txt在bin下
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
