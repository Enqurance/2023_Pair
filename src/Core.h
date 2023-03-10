//
// Created by Enqurance on 2023/3/10.
//

#ifndef WORDLIST_CORE_H
#define WORDLIST_CORE_H

#include <utility>

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
    int longest_value = 0;
    vector<string> longest_chain;
    vector<vector<string>> all_chain;
    // 建图相关
    vector<Node *> nodes;
    int nodes_size = -1;
    int inDegree[MAX] = {0};

    vector<string> words;

    bool enableLoop = false;
    bool loop_exist = false;
    char req_head = 0;
    char req_tail = 0;

    vector<Node *> nodes_with_diff_head[26];    // 不同开头的单词

    void create_nodes(bool is_word_chain) {       /* 创建节点，生成图 */
        int cnt = 0;
        for (const auto &word: words) {
            Node *n = new Node(word, cnt++, (is_word_chain) ? (int )word.length() : 1);
            nodes.push_back(n);
            nodes_with_diff_head[n->get_s() - 'a'].push_back(n);
        }
        nodes_size = int(nodes.size());
        for (int i = 0; i < nodes_size; i++) {
            for (int j = 0; (j < nodes_size) & (i != j); j++) {
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
        memcpy(tmp_inDegree, inDegree, sizeof (inDegree));
        for (int i = 0; i < nodes_size; i++) {
            if (tmp_inDegree[i] == 0) {
                count++;
                q.push(nodes[i]);
            }
        }
        while (!q.empty()) {
            Node *tmp = q.front();
            q.pop();
            int toNode_size = (int )(tmp->toNodes).size();
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

    void genAllWordChain(char head, char tail, char not_head) {
        for (int i = 0; i < 26; i++) {
            if (head != 0 && (head - 'a' != i)) continue;
            if (not_head != 0 && (head - 'a' == i)) continue;
            int size = (int )nodes_with_diff_head[i].size();
            for (int j = 0; j < size; j++) {
                memset(vis, false, nodes_size);
                dfs_all_chain(nodes_with_diff_head[i][j]->get_id(), *new vector<string>, head, tail, not_head);
            }
        }
    }

    void dfs_all_chain(int id, vector<string> cur_chain, char head, char tail, char not_head) {
        vis[id] = true;
        cur_chain.push_back(nodes[id]->get_context());
        if ((tail == 0 || tail == nodes[id]->get_e()) && (cur_chain.size() >= 2)) {
            all_chain.push_back(cur_chain);
        }
        int toNode_size = (int )(nodes[id]->toNodes).size();
        for (int i = 0; i < toNode_size; i++) {
            int toNode_id = nodes[id]->toNodes[i]->get_id();
            if ((head == 0 || head == nodes[toNode_id]->get_s()) &&
                (not_head == 0 || not_head != nodes[toNode_id]->get_s()) && !vis[toNode_id]) {
                dfs_all_chain(toNode_id, cur_chain, head, tail, not_head);
            }
        }
    }

    void genMaxWordCountChain(bool circle_exist, char head, char tail, char not_head) {
        if (circle_exist) {
            for (int i = 0; i < nodes_size; i++) {
                if ((head == 0 || head == nodes[i]->get_s()) &&
                    (not_head == 0 || not_head != nodes[i]->get_s())) {
                    dfs_longest_chain(i, 0, *new vector<string>, head, tail, not_head);
                }
            }
        } else {
            dp_longest_chain(head, tail, not_head);
        }
    }

    void dp_longest_chain(char head, char tail, char not_head) {
        // 局部变量初始化
        queue<Node *> q;
        int tmp_inDegree[MAX];
        memcpy(tmp_inDegree, inDegree, sizeof (inDegree));
        memset(lastWord, -1, sizeof (lastWord));

        // 入度为0的，且符合要求开头字母的，先入队
        for (int i = 0; i < nodes_size; i++) {
            if (tmp_inDegree[i] == 0) {
                // 有要求指定开头字母，或者没有要求
                // 有要求指定不能开头的字母，或者没有要求
                if ((head == 0 || nodes[i]->get_s() == head) &&
                    (not_head == 0 || not_head != nodes[i]->get_s())) {
                    q.push(nodes[i]);
                    dp[i] = nodes[i]->get_v();
                }
            }
        }

        // 根据拓扑排序迭代
        while (!q.empty()) {
            Node *tmp = q.front();
            q.pop();
            int toNode_size = (int )(tmp->toNodes).size();
            for (int i = 0; i < toNode_size; i++) {
                int toNode_id = tmp->toNodes[i]->get_id();
                if (dp[tmp->get_id()] + tmp->get_v() > dp[toNode_id]) {
                    lastWord[toNode_id] = tmp->get_id();
                    dp[toNode_id] = dp[tmp->get_id()] + tmp->get_v();
                }
                tmp_inDegree[toNode_id]--;
                if (tmp_inDegree[toNode_id] == 0) {
                    if ((head == 0 || nodes[i]->get_s() == head) &&
                        (not_head == 0 || not_head != nodes[i]->get_s())) {
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

        // 将结果保存并返回
        while (max_index != -1) {
            longest_chain.push_back(nodes[max_index]->get_context());
            max_index = lastWord[max_index];
        }
        reverse(longest_chain.begin(), longest_chain.end());
    }

    void dfs_longest_chain(int id, int cur_v, vector<string> cur_chain, char head, char tail, char not_head) {
        cur_chain.push_back(nodes[id]->get_context());
        cur_v += nodes[id]->get_v();
        if ((cur_v > longest_value) && (tail == 0 || nodes[id]->get_e() == tail) && cur_chain.size() >= 2) {
            longest_chain.assign(cur_chain.begin(), cur_chain.end());
            longest_value = cur_v;
        }
        int toNode_size = (int )(nodes[id]->toNodes).size();
        for (int i = 0; i < toNode_size; i++) {
            int toNode_id = nodes[id]->toNodes[i]->get_id();
            if ((head == 0 || head == nodes[toNode_id]->get_s()) &&
                (not_head == 0 || not_head != nodes[toNode_id]->get_s())) {
                dfs_longest_chain(toNode_id, cur_v + nodes[toNode_id]->get_v(), cur_chain, head, tail, not_head);
            }
        }
    }

public:
    Core(const vector<string> &words, bool enableLoop, char req_head, char req_tail, bool graph_mode) {
        this->words = words;
        this->enableLoop = enableLoop;
        this->req_head = req_head;
        this->req_tail = req_tail;
        create_nodes(graph_mode);
        check_circle();
    }
};


#endif //WORDLIST_CORE_H
