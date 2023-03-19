#include "bits/stdc++.h"
#include <gtest/gtest.h>
#include "string"
#include "windows.h"
#include "../../src/FileIO.h"
#include "../../src/Core.h"
#include "filesystem"

using namespace std;

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

// too many chains
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

    ASSERT_EQ(gen_chains_all(words, size, result), 0);
    ASSERT_EQ(f.output_screen(result), 1);
}


// no file
TEST_F(CoreTest, Test_NO_FILE) {
    FileIO f = FileIO::getInstance();
    string filename = "../test/Testfiles/input66.txt";
    ASSERT_EQ(f.read_file(filename), -1);
}

// illegal file
TEST_F(CoreTest, Test_ILLEGAL_FILE) {
    int ret1 = system("..\\bin\\Wordlist.exe -n ..\\test\\Testfiles\\MDFile.md");
    ASSERT_EQ(ret1, 0);
}

TEST_F(CoreTest, Test_LACK) {
    int ret1 = std::system("..\\bin\\Wordlist.exe -n input.txt input1.txt");
    ASSERT_EQ(ret1, 0);
}

// illegal loop
TEST_F(CoreTest, Test_ILLEGAL_LOOP) {
    FileIO f = FileIO::getInstance();
    string filename = "../test/Testfiles/input3.txt";
    vector<string> words;
    int size;
    ASSERT_EQ(f.read_file(filename), 1);
    ASSERT_EQ(size = f.get_words(words), 6);

    /* 开始测试 */
    vector<vector<string>> result;
    ASSERT_EQ(gen_chains_all(words, size, result), -1);
}

// parameter error
TEST_F(CoreTest, Test_PARAMETER_ERROR) {
    // 基本参数冲突 BASIC_ARGS_CONFLICT
    int ret1 = std::system("..\\bin\\Wordlist.exe -c -w ..\\Testfiles\\input1.txt");
    ASSERT_EQ(ret1, 0);
    // 基本参数缺失 BASIC_ARGS_LACK
    int ret2 = std::system("..\\bin\\Wordlist.exe ..\\Testfiles\\input1.txt");
    ASSERT_EQ(ret2, 0);
    // 参数缺少值 VALUE_LACK
    int ret3 = std::system("..\\bin\\Wordlist.exe -w -h ..\\Testfiles\\input1.txt");
    ASSERT_EQ(ret3, 0);
    // 参数值多于一个 VALUE_MORE_THAN_ONE
    int ret4 = std::system("..\\bin\\Wordlist.exe -w -t bb ..\\Testfiles\\input1.txt");
    ASSERT_EQ(ret4, 0);
    // 参数值非法(不是字母) VALUE_ILLEGAL_ARGS
    int ret5 = std::system("..\\bin\\Wordlist.exe -w -j 8 ..\\Testfiles\\input1.txt");
    ASSERT_EQ(ret5, 0);
    // 参数N冲突 ARG_N_CONFLICT
    int ret6 = std::system("..\\bin\\Wordlist.exe -n -h a ..\\Testfiles\\input1.txt");
    ASSERT_EQ(ret6, 0);
    // 参数未定义 ARGS_UNIDENTIFIED
    int ret7 = std::system("..\\bin\\Wordlist.exe -n -o ..\\Testfiles\\input1.txt");
    ASSERT_EQ(ret7, 0);
    // 参数重复 ARGS_DUPLICATE
    int ret8 = std::system("..\\bin\\Wordlist.exe -h a -h a ..\\Testfiles\\input1.txt");
    ASSERT_EQ(ret8, 0);
}