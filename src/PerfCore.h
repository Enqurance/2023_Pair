//
// Created by ZYL on 2023/3/10.
//

#ifndef WORDLIST_CORE_H
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

    bool over_large = false;

    // 建图相关
    vector<Node *> nodes;
    int nodes_size = -1;
    int inDegree[MAX] = {0};
    bool graph_mode = false;

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

    void reBuildGraph() {
        // 局部变量初始化
        queue<Node *> q;
        int tmp_inDegree[MAX];
        memcpy(tmp_inDegree, inDegree, sizeof(inDegree));
        for (int i = 0; i < nodes_size; i++) {
            if (tmp_inDegree[i] == 0 &&
                ((head != 0 && nodes[i]->get_s() != head) || (reject != 0 && nodes[i]->get_s() == reject))) {
                q.push(nodes[i]);
            }
        }
        while (!q.empty()) {
            Node *tmp = q.front();
            q.pop();
            tmp->is_deleted = true;
            int toNode_size = (int) (tmp->toNodes).size();
            for (int i = 0; i < toNode_size; i++) {
                int toNode_id = tmp->toNodes[i]->get_id();
                tmp_inDegree[toNode_id]--;
                if (tmp_inDegree[toNode_id] == 0 &&
                    ((head != 0 && nodes[toNode_id]->get_s() != head) ||
                     (reject != 0 && nodes[toNode_id]->get_s() == reject))) {
                    q.push(nodes[toNode_id]);
                }
            }
        }
        words.clear();
        words_size = 0;
        for (int i = 0; i < nodes_size; i++) {
            if (!nodes[i]->is_deleted) {
                words.push_back(nodes[i]->get_context());
                words_size++;
            } else {
                delete nodes[i];
            }
        }
        nodes.clear();
        nodes_with_diff_head->clear();
        memset(inDegree, 0, sizeof(inDegree));
        create_nodes(graph_mode);
    }

    void dfs_all_chain(int id, vector<string> &cur_chain, int cur_size) {
        if (over_large) return;
        vis[id] = true;
        cur_chain.push_back(nodes[id]->get_context());
        cur_size++;
        if (cur_size >= 2) {
            all_chains.push_back(cur_chain);
            all_chains_size++;
            if (all_chains_size > 20000) {
                over_large = true;
                return;
            }
        }
        int toNode_size = (int) (nodes[id]->toNodes).size();
        for (int i = 0; i < toNode_size; i++) {
            int toNode_id = nodes[id]->toNodes[i]->get_id();
            if (!vis[toNode_id]) {
                dfs_all_chain(toNode_id, cur_chain, cur_size);
            }
        }
        cur_chain.pop_back();
        vis[id] = false;
    }

    void dp_longest_chain() {
        // 如果head和reject有要求，重构图
        if (head != 0 || reject != 0) reBuildGraph();

        // 局部变量初始化
        queue<Node *> q;
        int tmp_inDegree[MAX];
        int len_rec[MAX];
        memcpy(tmp_inDegree, inDegree, sizeof(inDegree));
        memset(lastWord, -1, sizeof(lastWord));
        memset(dp, 0, sizeof(dp));
        memset(len_rec, 0, sizeof(len_rec));

        // 入度为0的，且符合要求开头字母的，先入队
        for (int i = 0; i < nodes_size; i++) {
            if (tmp_inDegree[i] == 0) {
                // 有要求指定开头字母，或者没有要求
                // 有要求指定不能开头的字母，或者没有要求
                if ((head == 0 || nodes[i]->get_s() == head) &&
                    (reject == 0 || reject != nodes[i]->get_s())) {
                    q.push(nodes[i]);
                    dp[i] = nodes[i]->get_v();
                    len_rec[i] = 1;
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
                    len_rec[toNode_id] = len_rec[tmp->get_id()] + 1;
                }
                tmp_inDegree[toNode_id]--;
                if (tmp_inDegree[toNode_id] == 0) {
                    q.push(nodes[toNode_id]);
                }
            }
        }

        // 最终遍历结果，找到最长的链
        int max_length = 0, max_index = -1;
        for (int i = 0; i < nodes_size; i++) {
            if (dp[i] > max_length && (tail == 0 || tail == nodes[i]->get_e()) && len_rec[i] >= 2) {
                max_index = i;
                max_length = dp[i];
            }
        }

        // 将结果保存并返回
        while (max_index != -1) {
            longest_chain.push_back(nodes[max_index]->get_context());
            max_index = lastWord[max_index];
        }
        reverse(longest_chain.begin(), longest_chain.end());
    }

    void dfs_longest_chain(int id, int cur_v, vector<string> &cur_chain, int cur_size) {
        if (over_large) return;
        vis[id] = true;
        cur_chain.push_back(nodes[id]->get_context());
        cur_v += nodes[id]->get_v();
        cur_size += 1;
        // 当result结果长度超过20000，输出到solution.txt的可以为空
        if (cur_size > 20000) {
            over_large = true;
            return;
        }
        if ((cur_v > longest_size) && (tail == 0 || nodes[id]->get_e() == tail) && cur_size >= 2) {
            longest_chain.assign(cur_chain.begin(), cur_chain.end());
            longest_size = cur_v;
        }
        int toNode_size = (int) (nodes[id]->toNodes).size();
        for (int i = 0; i < toNode_size; i++) {
            int toNode_id = nodes[id]->toNodes[i]->get_id();
            if (!vis[toNode_id]) {
                dfs_longest_chain(toNode_id, cur_v + nodes[toNode_id]->get_v(), cur_chain, cur_size);
            }
        }
        cur_chain.pop_back();
        vis[id] = false;
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
        this->over_large = false;
        this->graph_mode = graph_mode;
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
        this->over_large = false;
        create_nodes(false);
        check_circle();
    }

    // 不要求和其他参数联合使用
    int genAllWordChain(vector<vector<string>> &result) {
        for (auto &i: nodes_with_diff_head) {
            int size = (int) i.size();
            for (int j = 0; j < size; j++) {
                memset(vis, false, nodes_size);
                dfs_all_chain(i[j]->get_id(), *new vector<string>, 0);
                if (over_large) {
//                    dealWithOverLarge();
                    result.clear();
                    return 0;
                }
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
                    dfs_longest_chain(i, 0, *new vector<string>, 0);
                    if (over_large) {
//                        dealWithOverLarge();
                        result.clear();
                        return 0;
                    }
                }
            }
        } else {
            dp_longest_chain();
            if (over_large) {
//                dealWithOverLarge();
                result.clear();
                return 0;
            }
        }
        result = longest_chain;
        longest_size = int(longest_chain.size());
        return longest_size;
    }

    bool checkIllegalLoop() const {
        return !enable_loop && loop_exist;
    }
};

#endif