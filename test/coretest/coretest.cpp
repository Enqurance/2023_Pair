#include <gtest/gtest.h>
#include "string"
#include "windows.h"
#include "../../src/Core.h"
#include "../../src/FileIO.h"

using namespace std;

vector<string> input1{"woo", "oom", "moon", "noox"};
vector<string> input2{"algebra", "apple", "zoo", "elephant", "under", "fox", "dog",
                      "moon", "leaf", "trick", "pseudopseudohypoparathyroidism"};
vector<string> input3{"abc", "cde", "efg", "cddddddddddddddddde", "chh", "hyq", "qps", "szz"};
vector<string> input4{"element", "heaven", "table", "teach", "talk"};
vector<string> input5{"a", "aa", "aaa", "aaaa", "b", "c"};

int comp_words(vector<string> &source, vector<string> &target);

int comp_vectors(vector<vector<string>> &source, vector<vector<string>> &target);

// 测试套件示例
class CoreTest : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

int main(int argc, char **argv) {    // 加载lib.dll库
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

// -n
TEST_F(CoreTest, Test_N) {
    string filename = "../test/Testfiles/input1.txt";
    vector<string> words;
    int size;
    vector<vector<string>> ans = {{"moon", "noox"},
                                  {"oom",  "moon"},
                                  {"oom",  "moon", "noox"},
                                  {"woo",  "oom"},
                                  {"woo",  "oom",  "moon"},
                                  {"woo",  "oom",  "moon", "noox"}};
    ASSERT_EQ(read_file(filename), 1);
    ASSERT_EQ(size = get_words(words), 4);
    ASSERT_EQ(comp_words(input1, words), 1);

    /* 功能测试 */
    vector<vector<string>> result;
    ASSERT_EQ(gen_chains_all(words, size, result), 6);
    ASSERT_EQ(output_screen(result), 1);
    ASSERT_EQ(comp_vectors(ans, result), 1);
}

// -w
TEST_F(CoreTest, Test_W) {
    string filename = "../test/Testfiles/input2.txt";
    vector<string> words;
    int size;
    vector<string> ans = {"algebra", "apple", "elephant", "trick"};
    ASSERT_EQ(read_file(filename), 1);
    EXPECT_EQ(size = get_words(words), 11);
    ASSERT_EQ(comp_words(input2, words), 1);

    /* 功能测试 */
    char c = 0;
    vector<string> result;
    ASSERT_EQ(gen_chain_word(words, size, result, c, c, c, false), 4);
    ASSERT_EQ(output_file(result), 1);
    ASSERT_EQ(comp_words(ans, result), 1);
}

// -c
TEST_F(CoreTest, Test_C) {
    string filename = "../test/Testfiles/input2.txt";
    vector<string> words;
    int size;
    vector<string> ans = {"pseudopseudohypoparathyroidism", "moon"};
    ASSERT_EQ(read_file(filename), 1);
    EXPECT_EQ(size = get_words(words), 11);
    ASSERT_EQ(comp_words(input2, words), 1);

    /* 功能测试 */
    char c = 0;
    vector<string> result;
    ASSERT_EQ(gen_chain_char(words, size, result, c, c, c, false), 2);
    ASSERT_EQ(output_file(result), 1);
    ASSERT_EQ(comp_words(ans, result), 1);
}

// -h -t -c
TEST_F(CoreTest, Test_H_T_C) {
    string filename = "../test/Testfiles/input3.txt";
    vector<string> words;
    int size;
    vector<string> ans = {};
    ASSERT_EQ(read_file(filename), 1);
    EXPECT_EQ(size = get_words(words), 8);
    ASSERT_EQ(comp_words(input3, words), 1);

    /* 功能测试 */
    char c = 0;
    vector<string> result;
    ASSERT_EQ(gen_chain_char(words, size, result, 'a', 'z', c, false), 0);
    ASSERT_EQ(output_file(result), 1);
    ASSERT_EQ(comp_words(ans, result), 1);
}

// -h -t -w
TEST_F(CoreTest, Test_H_T_W) {
    string filename = "../test/Testfiles/input4.txt";
    vector<string> words;
    int size;
    vector<string> ans = {"abd", "dez"};
    ASSERT_EQ(read_file(filename), 1);
    EXPECT_EQ(size = get_words(words), 7);
    ASSERT_EQ(comp_words(input2, words), 1);

    /* 功能测试 */
    char c = 0;
    vector<string> result;
    ASSERT_EQ(gen_chain_word(words, size, result, 'a', 'z', c, false), 2);
    ASSERT_EQ(output_file(result), 1);
    ASSERT_EQ(comp_words(ans, result), 1);
}

int comp_words(vector<string> &source, vector<string> &target) {
    set<string> s(source.begin(), source.end()), t(target.begin(), target.end());
    if (s == t) return 1;
    return -1;
}

int comp_vectors(vector<vector<string>> &source, vector<vector<string>> &target) {
    int size = int(source.size());
    for (int i = 0; i < size; i++) {
        if (source != target) {
            return -1;
        }
    }
    return 1;
}
