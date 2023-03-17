#include <gtest/gtest.h>
#include "string"
#include "windows.h"
#include "../../src/PerfCore.h"
#include "../../src/PerfFileIO.h"
#include "../../src/Node.h"

using namespace std;

vector<string> input1{"woo", "oom", "moon", "noox", "blue", "nijun"};
vector<string> input2{"algebra", "apple", "zoo", "elephant", "under", "fox", "dog",
                      "moon", "leaf", "trick", "pseudopseudohypoparathyroidism",
                      "bluez", "todzzzzz", "ted"};
vector<string> input3{"bbcc", "cdef", "fack", "kill", "cde", "eb"};
vector<string> input4{"abc", "abd", "beg", "ccf", "cccccf", "grs", "dez"};
vector<string> input5{"element", "heaven", "table", "teach", "talk"};

int comp_words(vector<string> &source, vector<string> &target);

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
    FileIO f = FileIO::getInstance();
    string filename = "../test/Testfiles/input1.txt";
    vector<string> words;
    int size;
    ASSERT_EQ(f.read_file(filename), 1);
    ASSERT_EQ(size = f.get_words(words), 6);
    ASSERT_EQ(comp_words(input1, words), 1);


    /* 功能测试 */
    Core core = *new Core(words, size);
    vector<vector<string>> result;
    ASSERT_EQ(core.genAllWordChain(result), 10);
    ASSERT_EQ(f.output_screen(result), 1);
}

// -w -h -t
TEST_F(CoreTest, Test_W_H_T) {
    FileIO f = FileIO::getInstance();
    string filename = "../test/Testfiles/input2.txt";
    vector<string> words;
    int size;
    ASSERT_EQ(f.read_file(filename), 1);
    ASSERT_EQ(size = f.get_words(words), 14);
    ASSERT_EQ(comp_words(input2, words), 1);


    /* 功能测试 */
    Core core = *new Core(words, size, false, 'a', 'z', 0, false);
    vector<string> result;
    ASSERT_EQ(core.genMaxWordCountChain(result), 4);
    ASSERT_EQ(f.output_file(result), 1);
}

// -w -h -t -r
TEST_F(CoreTest, Test_W_H_T_R) {
    FileIO f = FileIO::getInstance();
    string filename = "../test/Testfiles/input3.txt";
    vector<string> words;
    int size;
    ASSERT_EQ(f.read_file(filename), 1);
    ASSERT_EQ(size = f.get_words(words), 6);
    ASSERT_EQ(comp_words(input3, words), 1);


    /* 功能测试 */
    Core core = *new Core(words, size, true, 'b', 0, 0, false);
    vector<string> result;
    ASSERT_EQ(core.checkIllegalLoop(), false);
    ASSERT_EQ(core.genMaxWordCountChain(result), 6);
    ASSERT_EQ(f.output_file(result), 1);
}

int comp_words(vector<string> &source, vector<string> &target) {
    set<string> s(source.begin(), source.end()), t(target.begin(), target.end());
    if (s == t) return 1;
    return -1;
}

