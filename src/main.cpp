#include "bits/stdc++.h"
#include "Node.h"
#include "Core.h"
#include "FileReader.h"

#define MAX 10000

void parse_args(int argc, char *argv[]);
void parse_additional_args(bool &flag, char &ch, char *argv[], int &i, int size);

void create_nodes();
void check_circle();

int read_file(const std::string &filename);
void output_result();

void solve();

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