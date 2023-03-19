//
// Created by Yoga on 2023/3/18.
//
#include "bits/stdc++.h"
#include <gtest/gtest.h>
#include "string"
#include "windows.h"
#include "../PerfFileIO.h"
#include "../../src/Core.h"

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

    gen_chains_all(words, size, result);

//    ASSERT_EQ(core.checkIllegalLoop(), false);
//    ASSERT_EQ(core.genAllWordChain(result), 3);
//    ASSERT_EQ(core.genAllWordChain(result), 0);
    ASSERT_EQ(f.output_screen(result), 1);
}