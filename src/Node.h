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
    vector<Node *> toNodes;

    explicit Node(string str, int index) {
        context.append(str);
        id = index;
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

    int get_id() const {
        return id;
    }

    void addToNodes(Node *node) {
        toNodes.push_back(node);
    }

private:
    string context;
    char s, e;
    int id;
};


#endif //INITPROJECT_NODE_H
