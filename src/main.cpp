#include "bits/stdc++.h"
#include "Node.h"

#define MAXN 10000

void parse_args(int argc, char *argv[]);
void parse_additional_args(bool &flag, char &ch, char *argv[], int &i, int size);

void parse_words(const string &context);
void store_word(string &word);

void create_nodes();
void check_circle();

int read_file(const std::string &filename);
void output_result();

void solve();
void genAllWordChain(char head, char tail, char not_head);
void genMaxWordCountChain(char head, char tail, char not_head);
void dp_longest_chain(char head, char tail, char not_head);
void dfs_longest_chain(int id, int cur_v, vector<string> cur_chain, char head, char tail, char not_head);
void dfs_all_chain(int id, vector<string> cur_chain, char head, char tail, char not_head);


// 读入时，单词储存相关
vector<string> words;
unordered_map<string, int> word_map;    //记录单词是否重复，int同时记录单词长度
vector<Node *> nodes_with_diff_head[26];    // 不同开头的单词

// 建图相关
vector<Node *> nodes;
int nodes_size = -1;
int inDegree[MAXN] = {0};

// 程序参数相关
string input_file;
bool is_all_chain = false;             // -n
bool is_count_chain = false;   // -w
bool is_word_chain = false;    // -c
bool is_head = false;      char req_head = 0;      // -h
bool is_tail = false;      char req_tail = 0;      // -t
bool is_not_head = false;  char req_not_head = 0;  // -j
bool allow_circle = false;          // -r

bool circle_exist = false;

// 程序错误处理相关
enum args_fault {
    file_not_exists,    // 文件不存在
    file_illegal,       // 文件不合法

    args_conflict,      // 参数类型冲突
    args_no_basic,      // 没有基本类型参数

    additional_lack_character,  // 附加参数缺少附带字母-h-t-j
    additional_not_match,        // 字母格式不正确
};
bool fault[10];         // 储存异常信息

// 程序算法相关
// dp算法
int dp[MAXN] = {0};
int lastWord[MAXN] = {-1};
// dfs算法
bool vis[MAXN] = {false};
// 最终结果
int longest_value = 0;
vector<string> longest_chain;
vector<vector<string>> all_chain;

int main(int argc, char *argv[]) {
    /* 读取命令行，获取参数信息，检查冲突 */
    parse_args(argc, argv);

    /* 读取文件，建图 */
    read_file(input_file);
    create_nodes();
    check_circle();
    if (circle_exist && !allow_circle) {
        cout << "has Circle !" << endl;
    }
    /* 求解 */
    solve();
    output_result();        //待写
    return 0;
}

void parse_args(int argc, char *argv[]) {
    int i = 0;
    while (i < argc) {
        if (strcmp(argv[i], "-n") == 0) {
            is_all_chain = true;
            if (is_count_chain || is_word_chain) {
                fault[args_conflict] = true;
            }
        } else if (strcmp(argv[i], "-w") == 0) {
            is_count_chain = true;
            if (is_all_chain || is_word_chain) {
                fault[args_conflict] = true;
            }
        } else if (strcmp(argv[i], "-c") == 0) {
            is_word_chain = true;
            if (is_all_chain || is_count_chain) {
                fault[args_conflict] = true;
            }
        } else if (strcmp(argv[i], "-h") == 0) {
            parse_additional_args(is_head, req_head, argv, i, argc);
        } else if (strcmp(argv[i], "-t") == 0) {
            parse_additional_args(is_tail, req_tail, argv, i, argc);
        } else if (strcmp(argv[i], "-j") == 0) {
            parse_additional_args(is_not_head, req_not_head, argv, i, argc);
        } else if (strcmp(argv[i], "-r") == 0) {
            allow_circle = true;
        } else {
            input_file = argv[i];
            // 没有.txt出现 或者.txt不是文件名结尾
            int size = (int )input_file.length();
            if ((input_file.find(".txt") == std::string::npos) || (input_file.find_last_of(".txt") != size - 4)) {
                fault[file_illegal] = true;
            }
        }
        i++;
    }
    if (!is_all_chain && !is_count_chain && !is_word_chain) {
        fault[args_no_basic] = true;
    }
}

/* 处理-h-t-j三个附加参数，主要是异常处理 */
void parse_additional_args(bool &flag, char &ch, char *argv[], int &i, int size) {
    flag = true;
    if ((i + 1 < size) && (strlen(argv[i+1]) == 1) && isalpha(argv[i+1][0])) {
        ch = argv[++i][0];
    } else if ((i + 1 == size) || (strlen(argv[i+1]) == 0)) {
        // 错误处理，附加参数后缺失字母
        fault[additional_lack_character] = true;
    } else {
        // 错误处理，附加参数后，格式不匹配
        fault[additional_not_match] = true;
    }
}


// 读文件，输出文件
int read_file(const std::string &filename) {   /* 读文件，目前只能读绝对路径 */
    ifstream file;
    file.open(filename, ios::in);
    if (!file.is_open()) {
        fault[file_not_exists] = true;
        cerr << "cannot open file!" << endl;
        return -1;
    }
    string temp;
    while (getline(file, temp)) {
        parse_words(temp);
    }
    file.close();
    return 1;
}

void output_result() {
    if (is_all_chain) {
        int all_chain_size = (int )all_chain.size();
        cout << all_chain_size << endl;
        for (int i = 0; i < all_chain_size; i++) {
            int single_size = (int )all_chain[i].size();
            for (int j = 0; j < single_size; j++) {
                cout << all_chain[i][j] << " ";
            }
            cout << endl;
        }
    } else if (is_count_chain || is_word_chain) {
        ofstream file;
        file.open("solution.txt", ios::out);
        int longest_chain_size = (int )longest_chain.size();
        for (int i = 0; i < longest_chain_size; i++) {
            file << longest_chain[i] << endl;
        }
        file.close();
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
            store_word(word);
            word.clear();
        }
        i++;
    }
    if (!word.empty()) {
        store_word(word);
    }
}

void store_word(string &word) {     /* 储存单词的函数 */
    transform(word.begin(), word.end(), word.begin(), ::tolower);
    if (word_map.find(word) == word_map.end()) {    //添加单词操作
        words.push_back(word);
        word_map[word] = (int )word.length();
    }
}

void create_nodes() {       /* 创建节点，生成图 */
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
    int tmp_inDegree[MAXN];
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
    circle_exist = count != nodes_size;
}

void solve() {
    if (is_all_chain) {
        genAllWordChain(req_head, req_tail, req_not_head);
    } else if (is_word_chain || is_count_chain) {
        genMaxWordCountChain(req_head, req_tail, req_not_head);
    }
}

void genAllWordChain(char head, char tail, char not_head) {
    for (int i = 0; i <nodes_size; i++) {
        if ((!is_head || (nodes[i]->get_s() == head)) &&
            (!is_not_head || (not_head != nodes[i]->get_s()))) {
            memset(vis, false, nodes_size);
            dfs_all_chain(i, *new vector<string>, head, tail, not_head);
        }
    }
}

void dfs_all_chain(int id, vector<string> cur_chain, char head, char tail, char not_head) {
    vis[id] = true;
    cur_chain.push_back(nodes[id]->get_context());
    if ((!is_tail || (tail == nodes[id]->get_e())) && (cur_chain.size() >= 2)) {
        all_chain.push_back(cur_chain);
    }
    int toNode_size = (int )(nodes[id]->toNodes).size();
    for (int i = 0; i < toNode_size; i++) {
        int toNode_id = nodes[id]->toNodes[i]->get_id();
        if ((!is_head || (head == nodes[toNode_id]->get_s())) &&
            (!is_not_head || (not_head != nodes[toNode_id]->get_s())) && !vis[toNode_id]) {
            dfs_all_chain(toNode_id, cur_chain, head, tail, not_head);
        }
    }
}

void genMaxWordCountChain(char head, char tail, char not_head) {
    if (circle_exist) {
        for (int i = 0; i <nodes_size; i++) {
            if ((!is_head || (nodes[i]->get_s() == head)) &&
                (!is_not_head || (not_head != nodes[i]->get_s()))) {
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
    int tmp_inDegree[MAXN];
    memcpy(tmp_inDegree, inDegree, sizeof (inDegree));
    memset(lastWord, -1, sizeof (lastWord));

    // 入度为0的，且符合要求开头字母的，先入队
    for (int i = 0; i < nodes_size; i++) {
        if (tmp_inDegree[i] == 0) {
            // 有要求指定开头字母，或者没有要求
            // 有要求指定不能开头的字母，或者没有要求
            if ((!is_head || (nodes[i]->get_s() == head)) &&
                (!is_not_head || (not_head != nodes[i]->get_s()))) {
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
                if ((!is_head || (nodes[i]->get_s() == head)) &&
                    (!is_not_head || (not_head != nodes[i]->get_s()))) {
                    q.push(nodes[toNode_id]);
                }
            }
        }
    }
    // 最终遍历结果，找到最长的链
    int max_length = 0, max_index;
    for (int i = 0; i < nodes_size; i++) {
        if (dp[i] > max_length && (!is_tail || (tail == nodes[i]->get_e()))) {
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
    if ((cur_v > longest_value) && (!is_tail || (nodes[id]->get_e() == tail))) {
        longest_chain.assign(cur_chain.begin(), cur_chain.end());
        longest_value = cur_v;
    }
    int toNode_size = (int )(nodes[id]->toNodes).size();
    for (int i = 0; i < toNode_size; i++) {
        int toNode_id = nodes[id]->toNodes[i]->get_id();
        if ((!is_head || (head == nodes[toNode_id]->get_s())) &&
            (!is_not_head || (not_head != nodes[toNode_id]->get_s()))) {
            dfs_longest_chain(toNode_id, cur_v + nodes[toNode_id]->get_v(), cur_chain, head, tail, not_head);
        }
    }
}