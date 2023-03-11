//
// Created by Enqurance on 2023/3/10.
//

#ifndef WORDLIST_CORE_H
#define WORDLIST_CORE_H

#ifdef WORDLIST_CORE_EXPORTS
#define WORDLIST_CORE_API __declspec(dllexport)
#else
#define WORDLIST_CORE_API __declspec(dllimport)
#endif

#include "bits/stdc++.h"
#include "Node.h"

using namespace std;

#define MAX 10000

class Core {
private:
    // dp算法
    int dp[MAX] = {0};
    int lastWord[MAX] = {-1};
    // dfs算法
    bool vis[MAX] = {false};
    // 最终结果
    vector<string> longest_chain;
    int longest_size = 0;
    vector<vector<string>> all_chains;
    int all_chains_size = 0;

    // 建图相关
    vector<Node *> nodes;
    int nodes_size = -1;
    int inDegree[MAX] = {0};

    vector<string> words;
    int words_size;

    bool enable_loop = false;
    bool loop_exist = false;
    char head = 0;
    char tail = 0;
    char reject = 0;

    vector<Node *> nodes_with_diff_head[26];    // 不同开头的单词

    void create_nodes(bool is_word_chain);

    void check_circle();

    void dfs_all_chain(int id, vector<string> cur_chain);

    void dp_longest_chain();

    void dfs_longest_chain(int id, int cur_v, vector<string> cur_chain);

public:
    Core(const vector<string> &words, int words_size, bool enableLoop,
         char head, char tail, char reject, bool graph_mode);

    Core(const vector<string> &words, int words_size);

    // 不要求和其他参数联合使用
    int genAllWordChain(vector<vector<string>> &result);

    int genMaxWordCountChain(vector<string> &result);
};

//指针数组result的长度上限为20000，超出上限时报错并保证返回值正确，此时输出到solution.txt中的单词链可以为空
//如果采用推荐的API接口，由于各组之间需要互换前后端，且推荐的API接口中返回值已经具有实际意义
//因此不宜采用直接返回报错码的方式处理，因此各位不要在返回值上承载异常信息，保证返回值正确

// 函数返回值为单词链的总数
int gen_chains_all(const vector<string> &words, int len, vector<vector<string>> &result);

// 函数返回值为单词链的长度
int gen_chain_word(const vector<string> &words, int len, vector<string> &result,
                   char head, char tail, char reject, bool enable_loop);

// 函数返回值为单词链的长度
int gen_chain_char(const vector<string> &words, int len, vector<string> &result,
                   char head, char tail, char reject, bool enable_loop);


#endif //WORDLIST_CORE_H
