#include "bits/stdc++.h"
#include "Node.h"

#define MAXN 10000

void parse_words(const string &context);
void parse_args(int argc, char *argv[]);

void create_nodes();
bool check_circle();

int read_file(const char *filename);

int output_screen();

// 读入时，单词储存相关
vector<string> words;
unordered_map<string, int> word_map;    //记录单词是否重复，int同时记录单词长度

// 建图相关
vector<Node *> nodes;
int nodes_size = -1;
int indegree[MAXN] = {0};

// 程序参数相关
char* input_file;
bool all_chain = false;             // -n
bool longest_count_chain = false;   // -w
bool longest_word_chain = false;    // -c
bool set_head = false;      char req_head;      // -h
bool set_tail = false;      char req_tail;      // -t
bool set_not_head = false;  char req_not_head;  // -j
bool allow_circle = false;          // -r

int main(int argc, char *argv[]) {
    parse_args(argc, argv);
    string context;
    read_file(input_file);
    create_nodes();
    if (!check_circle()) {
        // 判断参数
    }
    output_screen();        //待写
    return 0;
}

void parse_args(int argc, char *argv[]) {
    int i = 0;
    while (i < argc) {
        if (strcmp(argv[i], "-n") == 0) {
            all_chain = true;
        } else if (strcmp(argv[i], "-w") == 0) {
            longest_count_chain = true;
        } else if (strcmp(argv[i], "-c") == 0) {
            longest_word_chain = true;
        } else if (strcmp(argv[i], "-h") == 0) {
            set_head = true;
            if ((i + 1 < argc) && (strlen(argv[i+1])) && isalpha(argv[i+1][0])) {
                set_head = argv[++i][0];
            } else {
                // 错误处理，-h后参数不匹配
            }
        } else if (strcmp(argv[i], "-t") == 0) {
            set_tail = true;
            if ((i + 1 < argc) && (strlen(argv[i+1])) && isalpha(argv[i+1][0])) {
                set_tail = argv[++i][0];
            } else {
                // 错误处理，-t后参数不匹配
            }
        } else if (strcmp(argv[i], "-j") == 0) {
            set_not_head = true;
            if ((i + 1 < argc) && (strlen(argv[i+1])) && isalpha(argv[i+1][0])) {
                set_not_head = argv[++i][0];
            } else {
                // 错误处理，-j后参数不匹配
            }
        } else if (strcmp(argv[i], "-r") == 0) {
            allow_circle = true;
        } else {
            input_file = argv[i];
        }
        i++;
    }
}

int read_file(const char *filename) {   /* 读文件，目前只能读绝对路径 */
    ifstream file(filename, ios::in);
    if (!file.is_open()) {
        cerr << "文件打开失败！" << endl;
        return -1;
    }
    string temp;
    while (getline(file, temp)) {
        parse_words(temp);
    }
    return 1;
}

int output_file(const char *filename) {
    ofstream file(filename, ios::out);
    if (!file.is_open()) {
        cerr << "文件打开失败！" << endl;
        return -1;
    }

}


void parse_words(const string &context) {   /* 解析单词的函数 */
    int size = int(context.length());
    int i = 0;
    string word;
    while (i < size) {
        if (isalpha(context[i])) {
            word.append(1, context[i]);
        } else if (!word.empty()) {
            transform(word.begin(), word.end(), word.begin(), ::tolower);
            if (word_map.find(word) == word_map.end()) {    //添加单词操作
                words.push_back(word);
                word_map[word] = (int )word.length();
            }
            word.clear();
        }
        i++;
    }
}

void create_nodes() {
    for (const auto &word: words) {
        Node *n = new Node(word);
        nodes.push_back(n);
    }
    nodes_size = int(nodes.size());
    for (int i = 0; i < nodes_size; i++) {
        for (int j = 0; (j < nodes_size) & (i != j); j++) {
            if (nodes[i]->get_e() == nodes[j]->get_s()) {
                nodes[i]->addToNodes(j);
                indegree[j]++;
            }
        }
    }
}

bool check_circle() {
    queue<Node *> q;
    int count = 0;
    for (int i = 0; i < nodes_size; i++) {
        if (indegree[i] == 0) {
            count++;
            q.push(nodes[i]);
        }
    }
    while (!q.empty()) {
        Node *tmp = q.front();
        q.pop();
        int toNode_size = (int )(tmp->toNodes).size();
        for (int i = 0; i < toNode_size; i++) {
            indegree[tmp->toNodes[i]]--;
            if (indegree[tmp->toNodes[i]] == 0) {
                count++;
                q.push(nodes[tmp->toNodes[i]]);
            }
        }
    }
    return count == nodes_size;
}