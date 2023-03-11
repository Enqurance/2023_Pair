#include "Core.h"

// 函数返回值为单词链的总数
int gen_chains_all(const vector<string> &words, int len, vector<vector<string>> &result) {
    Core core = *new Core(words, len);
    core.genAllWordChain()
}

// 函数返回值为单词链的长度
int gen_chain_word(const vector<string> &words, int len, vector<string> &result,
                   char head, char tail, char reject, bool enable_loop) {
    Core core = *new Core(words, len, enable_loop, head, tail, reject, false);
}

// 函数返回值为单词链的长度
int gen_chain_char(const vector<string> &words, int len, vector<string> &result,
                   char head, char tail, char reject, bool enable_loop) {
    Core core = *new Core(words, len, enable_loop, head, tail, reject, true);
}