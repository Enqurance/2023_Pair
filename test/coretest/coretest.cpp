#include <gtest/gtest.h>
#include "string"
#include "windows.h"

using namespace std;

typedef int (*READ_FILE)(const string &filename);

typedef int (*OUTPUT_SCREEN)(const vector<vector<string>> &all_chains);

typedef int (*OUTPUT_FILE)(const vector<string> &longest_chain);

typedef int (*GET_WORDS)(vector<string> &words);

typedef int (*GEN_CHAINS_ALL)(const vector<string> &words, int len, vector<vector<string>> &result);

typedef int (*GEN_CHAINS_WORD)(const vector<string> &words, int len, vector<string> &result,
                               char head, char tail, char reject, bool enable_loop);

typedef int (*GEN_CHAINS_CHAR)(const vector<string> &words, int len, vector<string> &result,
                               char head, char tail, char reject, bool enable_loop);

vector<string> input1{"woo", "oom", "moon", "noox"};
vector<string> input2{"algebra", "apple", "zoo", "elephant", "under", "fox", "dog",
                      "moon", "leaf", "trick", "pseudopseudohypoparathyroidism"};
vector<string> input3{"algebra", "apple", "zoo", "elephant", "under", "fox", "dog",
                      "moon", "leaf", "trick", "pseudopseudohypoparathyroidism", "pz", "mm"};
vector<string> input4{"element", "heaven", "table", "teach", "talk"};
vector<string> input5{"a", "aa", "aaa", "aaaa", "b", "c"};

READ_FILE read_file;
OUTPUT_SCREEN output_screen;
OUTPUT_FILE output_file;
GET_WORDS get_words;
GEN_CHAINS_ALL gen_chains_all;
GEN_CHAINS_WORD gen_chain_word;
GEN_CHAINS_CHAR gen_chain_char;

int comp_words(vector<string> &source, vector<string> &target);

// 测试套件示例
class CoreTest : public ::testing::Test {
protected:
    void SetUp() override {
        HMODULE LibDll = LoadLibrary("../bin/lib.dll");
        if (!LibDll) {
            cout << "Unable to load LIB DLL!" << endl;
            return;
        }

        read_file = (READ_FILE) GetProcAddress(LibDll, "read_file");
        output_screen = (OUTPUT_SCREEN) GetProcAddress(LibDll, "output_screen");
        output_file = (OUTPUT_FILE) GetProcAddress(LibDll, "output_file");
        get_words = (GET_WORDS) GetProcAddress(LibDll, "get_words");

        if (!read_file || !output_screen || !output_file || !get_words) {
            cout << "Unable to get function address!" << endl;
            return;
        }

        // 加载core.dll库
        HINSTANCE CoreDll = LoadLibrary("../bin/core.dll");
        if (!CoreDll) {
            cout << "Unable to load CORE DLL!" << endl;
            return;
        }

        gen_chains_all = (GEN_CHAINS_ALL) GetProcAddress(CoreDll, "gen_chains_all");
        gen_chain_word = (GEN_CHAINS_WORD) GetProcAddress(CoreDll, "gen_chain_word");
        gen_chain_char = (GEN_CHAINS_CHAR) GetProcAddress(CoreDll, "gen_chain_char");
        if (!gen_chains_all || !gen_chain_word || !gen_chain_char) {
            cout << "Unable to get function address!" << endl;
            return;
        }
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
    ASSERT_EQ(read_file(filename), 1);
    ASSERT_EQ(size = get_words(words), 4);
    ASSERT_EQ(comp_words(input1, words), 1);

    /* 功能测试 */

}

int comp_words(vector<string> &source, vector<string> &target) {
    set<string> s(source.begin(), source.end()), t(target.begin(), target.end());
    if (s == t) return 1;
    return -1;
}
