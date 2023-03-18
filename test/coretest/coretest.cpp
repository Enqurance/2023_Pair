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
vector<string> input4{"ab", "bc", "cd", "de", "awdsdas"};
vector<string> input5{"element", "heaven", "tablt", "teach", "talk", "heavez"};

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
    core.genAllWordChain(result);
//    ASSERT_EQ(core.genAllWordChain(result), 13);
    ASSERT_EQ(f.output_screen(result), 1);
}

// -w
TEST_F(CoreTest, Test_W) {
    FileIO f = FileIO::getInstance();
    string filename = "../test/Testfiles/input2.txt";
    vector<string> words;
    int size;
    ASSERT_EQ(f.read_file(filename), 1);
    ASSERT_EQ(size = f.get_words(words), 14);
    ASSERT_EQ(comp_words(input2, words), 1);


    /* 功能测试 */
    Core core = *new Core(words, size, false, 0, 0, 0, false);
    vector<string> result;
    ASSERT_EQ(core.genMaxWordCountChain(result), 5);
    ASSERT_EQ(f.output_file(result), 1);
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
TEST_F(CoreTest, Test_W_H_R) {
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
    ASSERT_EQ(core.genMaxWordCountChain(result), 4);
    ASSERT_EQ(f.output_file(result), 1);
}

// -w -j
TEST_F(CoreTest, Test_W_J_R) {
    FileIO f = FileIO::getInstance();
    string filename = "../test/Testfiles/input4.txt";
    vector<string> words;
    int size;
    ASSERT_EQ(f.read_file(filename), 1);
    ASSERT_EQ(size = f.get_words(words), 5);
    ASSERT_EQ(comp_words(input4, words), 1);


    /* 功能测试 */
    Core core = *new Core(words, size, false, 0, 0, 'a', false);
    vector<string> result;
    ASSERT_EQ(core.checkIllegalLoop(), false);
    ASSERT_EQ(core.genMaxWordCountChain(result), 3);
    ASSERT_EQ(f.output_file(result), 1);
}

// -c -h -t
TEST_F(CoreTest, Test_C_H_T) {
    FileIO f = FileIO::getInstance();
    string filename = "../test/Testfiles/input5.txt";
    vector<string> words;
    int size;
    ASSERT_EQ(f.read_file(filename), 1);
    ASSERT_EQ(size = f.get_words(words), 6);
    ASSERT_EQ(comp_words(input5, words), 1);


    /* 功能测试 */
    Core core = *new Core(words, size, false, 't', 'z', 0, true);
    vector<string> result;
    ASSERT_EQ(core.checkIllegalLoop(), false);
    ASSERT_EQ(core.genMaxWordCountChain(result), 3);
    ASSERT_EQ(f.output_file(result), 1);
}


TEST_F(CoreTest, Test_TOO_MANY_CHAIN) {
    FileIO f = FileIO::getInstance();
    string filename = "../test/Testfiles/input6.txt";
    vector<string> words;
    int size;
    ASSERT_EQ(f.read_file(filename), 1);
    ASSERT_EQ(size = f.get_words(words), 250);


    /* 功能测试 */
    Core core = *new Core(words, size);
    vector<vector<string>> result;
    ASSERT_EQ(core.checkIllegalLoop(), false);
//    ASSERT_EQ(core.genAllWordChain(result), 3);
    ASSERT_EQ(core.genAllWordChain(result), 0);
    ASSERT_EQ(f.output_screen(result), 1);
}

TEST_F(CoreTest, Test_C_R) {
    FileIO f = FileIO::getInstance();
    string filename = "../test/Testfiles/input7.txt";
    vector<string> words;
    int size;
    ASSERT_EQ(f.read_file(filename), 1);
    ASSERT_EQ(size = f.get_words(words), 7);


    /* 功能测试 */
    Core core = *new Core(words, size, true, 0, 0, 0, true);
    vector<string> result;
    ASSERT_EQ(core.checkIllegalLoop(), false);
    ASSERT_EQ(core.genMaxWordCountChain(result), 7);
    ASSERT_EQ(f.output_file(result), 1);
}

TEST_F(CoreTest, Test_C_R_COMP) {
    FileIO f = FileIO::getInstance();
    string filename = "../test/Testfiles/input8.txt";
    vector<string> words;
    int size;
    ASSERT_EQ(f.read_file(filename), 1);
    ASSERT_EQ(size = f.get_words(words), 20);


    /* 功能测试 */
    Core core = *new Core(words, size, true, 0, 0, 0, true);
    vector<string> result;
    ASSERT_EQ(core.checkIllegalLoop(), false);
    ASSERT_EQ(core.genMaxWordCountChain(result), 13);
    ASSERT_EQ(f.output_file(result), 1);
}

// fail open
TEST_F(CoreTest, Test_FAIL_OPEN) {
    FileIO f = FileIO::getInstance();
    string filename = "../test/Testfiles/input99.txt";
    vector<string> words;
    ASSERT_EQ(f.read_file(filename), -1);
}

int comp_words(vector<string> &source, vector<string> &target) {
    set<string> s(source.begin(), source.end()), t(target.begin(), target.end());
    if (s == t) return 1;
    return -1;
}

