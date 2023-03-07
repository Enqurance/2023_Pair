//
// Created by Enqurance on 2023/3/7.
//

#ifndef INITPROJECT_NODE_H
#define INITPROJECT_NODE_H

#include "vector"
#include "string"

using namespace std;


class Node {
public:
    // 将记录出边的形式改为了vector<int>，表示在nodes中的编号
    vector<int> toNodes;

    explicit Node(string str) {
        context.append(str);
        if (!str.empty()) {
            s = str[0];
            e = str[str.size() - 1];
        }
    }

    char get_s() const {
        return s;
    }

    char get_e() const {
        return e;
    }

    string get_context() {
        return context;
    }

    void addToNodes(int node_id) {
        toNodes.push_back(node_id);
    }

private:
    string context;
    char s, e;
};


#endif //INITPROJECT_NODE_H
