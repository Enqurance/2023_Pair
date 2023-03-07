#include "bits/stdc++.h"
#include "Node.h"

#define MAXN 10000

void parse_args(int argc, char *argv[]);
void parse_additional_args(bool &flag, char &ch, char *argv[], int &i, int size);

void parse_words(const string &context);
void store_word(string &word);

void create_nodes();
bool has_circle();

int read_file(const std::string &filename);
void output_screen();

void solve();

// 读入时，单词储存相关
vector<string> words;
unordered_map<string, int> word_map;    //记录单词是否重复，int同时记录单词长度

// 建图相关
vector<Node *> nodes;
int nodes_size = -1;
int indegree[MAXN] = {0};

// 程序参数相关
string input_file;
bool all_chain = false;             // -n
bool longest_count_chain = false;   // -w
bool longest_word_chain = false;    // -c
bool set_head = false;      char req_head;      // -h
bool set_tail = false;      char req_tail;      // -t
bool set_not_head = false;  char req_not_head;  // -j
bool allow_circle = false;          // -r

// 程序错误处理相关
enum args_fault {
    file_not_exists,    // 文件不存在
    file_illegal,       // 文件不合法

    args_conflict,      // 参数类型冲突
    args_no_basic,      // 没有基本类型参数

    additional_lack_character,  // 附加参数缺少附带字母-h-t-j
    additional_not_match        // 字母格式不正确
};
bool fault[10];         // 储存异常信息

int main(int argc, char *argv[]) {
    /* 读取命令行，获取参数信息，检查冲突 */
    parse_args(argc, argv);

    /* 读取文件，建图 */
    read_file(input_file);
    create_nodes();
    if (has_circle() && !allow_circle) {
        cout << "has Circle !" << endl;
    }
    /* 求解 */
    solve();
    output_screen();        //待写
    return 0;
}

void parse_args(int argc, char *argv[]) {
    int i = 0;
    while (i < argc) {
        if (strcmp(argv[i], "-n") == 0) {
            all_chain = true;
            if (longest_count_chain || longest_word_chain) {
                fault[args_conflict] = true;
            }
        } else if (strcmp(argv[i], "-w") == 0) {
            longest_count_chain = true;
            if (all_chain || longest_word_chain) {
                fault[args_conflict] = true;
            }
        } else if (strcmp(argv[i], "-c") == 0) {
            longest_word_chain = true;
            if (all_chain || longest_count_chain) {
                fault[args_conflict] = true;
            }
        } else if (strcmp(argv[i], "-h") == 0) {
            parse_additional_args(set_head, req_head, argv, i, argc);
        } else if (strcmp(argv[i], "-t") == 0) {
            parse_additional_args(set_tail, req_tail, argv, i, argc);
        } else if (strcmp(argv[i], "-j") == 0) {
            parse_additional_args(set_not_head, req_not_head, argv, i, argc);
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
    if (!all_chain && !longest_count_chain && !longest_word_chain) {
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

int read_file(const std::string &filename) {   /* 读文件，目前只能读绝对路径 */
    ifstream file(filename, ios::in);
    if (!file.is_open()) {
        fault[file_not_exists] = true;
        cerr << "cannot open file!" << endl;
        return -1;
    }
    string temp;
    while (getline(file, temp)) {
        parse_words(temp);
    }
    return 1;
}

// 测试，检查输出的
void output_screen() {
    cout << nodes_size << endl;
    for (int i = 0; i < nodes_size; i++) {
        cout << nodes[i]->get_context() << endl;
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
        Node *n = new Node(word, cnt++);
        nodes.push_back(n);
    }
    nodes_size = int(nodes.size());
    for (int i = 0; i < nodes_size; i++) {
        for (int j = 0; (j < nodes_size) & (i != j); j++) {
            if (nodes[i]->get_e() == nodes[j]->get_s()) {
                nodes[i]->addToNodes(nodes[j]);
                indegree[j]++;
            }
        }
    }
}

bool has_circle() {
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
            int toNode_id = tmp->toNodes[i]->get_id();
            indegree[toNode_id]--;
            if (indegree[toNode_id] == 0) {
                count++;
                q.push(nodes[toNode_id]);
            }
        }
    }
    return count != nodes_size;
}

void solve() {

}