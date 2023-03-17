//
// Created by Enqurance on 2023/3/7.
//

#ifndef WORDLIST_NODE_H
#define WORDLIST_NODE_H

#include "vector"
#include "string"

using namespace std;

class Node {
public:
    vector<Node *> toNodes;
    bool is_deleted = false;

    explicit Node(string str, int index, int v) {
        context.append(str);
        id = index;
        value = v;
        s = str[0];
        e = str[str.length() - 1];
    }

    char get_s() const {
        return s;
    }

    char get_e() const {
        return e;
    }

    string get_context() const {
        return context;
    }

    int get_id() const {
        return id;
    }

    int get_v() const {
        return value;
    }

    void addToNodes(Node *node) {
        toNodes.push_back(node);
    }

public:
    string context;
    char s, e;
    int id, value = 1;
};

#endif
