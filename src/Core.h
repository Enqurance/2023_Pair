//
// Created by Enqurance on 2023/3/10.
//

#ifndef WORDLIST_CORETEST_H
#define WORDLIST_CORE_H

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

    void create_nodes(bool is_word_chain) {       /* 创建节点，生成图 */
        int cnt = 0;
        for (int i = 0; i < words_size; i++) {
            Node *n = new Node(words[i], cnt++, (is_word_chain) ? (int) words[i].length() : 1);
            nodes.push_back(n);
            nodes_with_diff_head[n->get_s() - 'a'].push_back(n);
        }
        nodes_size = cnt;
        for (int i = 0; i < nodes_size; i++) {
            for (int j = 0; j < nodes_size; j++) {
                if (i == j) continue;
                if (nodes[i]->get_e() == nodes[j]->get_s()) {
                    nodes[i]->addToNodes(nodes[j]);
                    inDegree[j]++;
                }
            }
        }
    }

    void check_circle() {
        queue<Node *> q;
        int count = 0;
        int tmp_inDegree[MAX];
        memcpy(tmp_inDegree, inDegree, sizeof(inDegree));
        for (int i = 0; i < nodes_size; i++) {
            if (tmp_inDegree[i] == 0) {
                count++;
                q.push(nodes[i]);
            }
        }
        while (!q.empty()) {
            Node *tmp = q.front();
            q.pop();
            int toNode_size = (int) (tmp->toNodes).size();
            for (int i = 0; i < toNode_size; i++) {
                int toNode_id = tmp->toNodes[i]->get_id();
                tmp_inDegree[toNode_id]--;
                if (tmp_inDegree[toNode_id] == 0) {
                    count++;
                    q.push(nodes[toNode_id]);
                }
            }
        }
        loop_exist = count != nodes_size;
    }

    void dfs_all_chain(int id, vector<string> cur_chain) {
        vis[id] = true;
        cur_chain.push_back(nodes[id]->get_context());
        if (cur_chain.size() >= 2) {
            all_chains.push_back(cur_chain);
            all_chains_size++;
        }
        int toNode_size = (int) (nodes[id]->toNodes).size();
        for (int i = 0; i < toNode_size; i++) {
            int toNode_id = nodes[id]->toNodes[i]->get_id();
            if (!vis[toNode_id]) {
                dfs_all_chain(toNode_id, cur_chain);
            }
        }
    }

    void dp_longest_chain() {
        // 局部变量初始化
        queue<Node *> q;
        int tmp_inDegree[MAX];
        memcpy(tmp_inDegree, inDegree, sizeof(inDegree));
        memset(lastWord, -1, sizeof(lastWord));

        // 入度为0的，且符合要求开头字母的，先入队
        for (int i = 0; i < nodes_size; i++) {
            if (tmp_inDegree[i] == 0) {
                // 有要求指定开头字母，或者没有要求
                // 有要求指定不能开头的字母，或者没有要求
                if ((head == 0 || nodes[i]->get_s() == head) &&
                    (reject == 0 || reject != nodes[i]->get_s())) {
                    q.push(nodes[i]);
                    dp[i] = nodes[i]->get_v();
                }
            }
        }

        // 根据拓扑排序迭代
        while (!q.empty()) {
            Node *tmp = q.front();
            q.pop();
            int toNode_size = (int) (tmp->toNodes).size();
            for (int i = 0; i < toNode_size; i++) {
                int toNode_id = tmp->toNodes[i]->get_id();
                if (dp[tmp->get_id()] + tmp->get_v() > dp[toNode_id]) {
                    lastWord[toNode_id] = tmp->get_id();
                    dp[toNode_id] = dp[tmp->get_id()] + tmp->get_v();
                }
                tmp_inDegree[toNode_id]--;
                if (tmp_inDegree[toNode_id] == 0) {
                    if ((head == 0 || nodes[i]->get_s() == head) &&
                        (reject == 0 || reject != nodes[i]->get_s())) {
                        q.push(nodes[toNode_id]);
                    }
                }
            }
        }

        // 最终遍历结果，找到最长的链
        int max_length = 0, max_index;
        for (int i = 0; i < nodes_size; i++) {
            if (dp[i] > max_length && (tail == 0 || tail == nodes[i]->get_e())) {
                max_index = i;
                max_length = dp[i];
            }
        }

        // 没有长度超过2的单词链
        if (max_length < 2) return;

        // 将结果保存并返回
        while (max_index != -1) {
            longest_chain.push_back(nodes[max_index]->get_context());
            max_index = lastWord[max_index];
        }
        reverse(longest_chain.begin(), longest_chain.end());
    }

    void dfs_longest_chain(int id, int cur_v, vector<string> cur_chain) {
        vis[id] = true;
        cur_chain.push_back(nodes[id]->get_context());
        cur_v += nodes[id]->get_v();
        if ((cur_v > longest_size) && (tail == 0 || nodes[id]->get_e() == tail) && cur_chain.size() >= 2) {
            longest_chain.assign(cur_chain.begin(), cur_chain.end());
            longest_size = cur_v;
        }
        int toNode_size = (int) (nodes[id]->toNodes).size();
        for (int i = 0; i < toNode_size; i++) {
            int toNode_id = nodes[id]->toNodes[i]->get_id();
            if ((head == 0 || head == nodes[toNode_id]->get_s()) &&
                (reject == 0 || reject != nodes[toNode_id]->get_s()) && !vis[toNode_id]) {
                dfs_longest_chain(toNode_id, cur_v + nodes[toNode_id]->get_v(), cur_chain);
            }
        }
    }

public:
    Core(const vector<string> &words, int words_size, bool enableLoop,
         char head, char tail, char reject, bool graph_mode) {
        this->words = words;
        this->words_size = words_size;
        this->enable_loop = enableLoop;
        this->head = head;
        this->tail = tail;
        this->reject = reject;
        create_nodes(graph_mode);
        check_circle();
    }

    Core(const vector<string> &words, int words_size) {
        this->words = words;
        this->words_size = words_size;
        this->enable_loop = false;
        this->head = 0;
        this->tail = 0;
        this->reject = 0;
        create_nodes(false);
        check_circle();
    }

    // 不要求和其他参数联合使用
    int genAllWordChain(vector<vector<string>> &result) {
        for (int i = 0; i < 26; i++) {
            int size = (int) nodes_with_diff_head[i].size();
            for (int j = 0; j < size; j++) {
                memset(vis, false, nodes_size);
                dfs_all_chain(nodes_with_diff_head[i][j]->get_id(), *new vector<string>);
            }
        }
        result = all_chains;
        return all_chains_size;
    }

    int genMaxWordCountChain(vector<string> &result) {
        if (loop_exist) {
            for (int i = 0; i < nodes_size; i++) {
                if ((head == 0 || head == nodes[i]->get_s()) &&
                    (reject == 0 || reject != nodes[i]->get_s())) {
                    memset(vis, false, nodes_size);
                    dfs_longest_chain(i, 0, *new vector<string>);
                }
            }
        } else {
            dp_longest_chain();
        }
        result = longest_chain;
        longest_size = int(longest_chain.size());
        return longest_size;
    }
};

//指针数组result的长度上限为20000，超出上限时报错并保证返回值正确，此时输出到solution.txt中的单词链可以为空
//如果采用推荐的API接口，由于各组之间需要互换前后端，且推荐的API接口中返回值已经具有实际意义
//因此不宜采用直接返回报错码的方式处理，因此各位不要在返回值上承载异常信息，保证返回值正确

#ifdef __cplusplus
extern "C" {
#endif

__declspec(dllexport) int gen_chains_all(const vector<string> &words, int len, vector<vector<string>> &result) {
    Core core = *new Core(words, len);
    return core.genAllWordChain(result);
}

__declspec(dllexport) int gen_chain_word(const vector<string> &words, int len, vector<string> &result,
                                         char head, char tail, char reject, bool enable_loop) {
    Core core = *new Core(words, len, enable_loop, head, tail, reject, false);
    return core.genMaxWordCountChain(result);
}

__declspec(dllexport) int gen_chain_char(const vector<string> &words, int len, vector<string> &result,
                                         char head, char tail, char reject, bool enable_loop) {
    Core core = *new Core(words, len, enable_loop, head, tail, reject, true);
    return core.genMaxWordCountChain(result);
}

#ifdef __cplusplus
}
#endif

#endif