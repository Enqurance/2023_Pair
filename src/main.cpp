#include "bits/stdc++.h"
#include "windows.h"
#include "Core.h"
#include "FileIO.h"

#define MAX 10005

using namespace std;

int parse_args(int argc, char *argv[]);

int parse_additional_args(bool &flag, char &ch, char *argv[], int &i, int size);

// 程序参数相关
string input_file;
bool is_all_chain = false;             // -n
bool is_count_chain = false;   // -w
bool is_word_chain = false;    // -c
bool is_head = false;
char head = 0;      // -h
bool is_tail = false;
char tail = 0;      // -t
bool is_not_head = false;
char reject = 0;  // -j
bool enableLoop = false;          // -r

static const regex arg_pattern("^(\\-(n|c|w|h|t|j|r))$");
// 可以匹配C:\, D:\开头的绝对路径，路径中允许包含..和.
static const regex txt_pattern(R"(^([a-zA-Z]:\\)?(([a-zA-Z0-9]+\\)*((..|.)\\)*)*[a-zA-Z0-9]+.(txt|TXT)$)");

int main(int argc, char *argv[]) {
    // 加载dll失败，直接返回

    /* 读取命令行，获取参数信息，检查冲突 */
    if (parse_args(argc, argv) == -1) return 0;

    if (read_file(input_file) == -1) return 0;

    vector<string> words;
    int words_size = get_words(words);

    if (is_all_chain) {
        vector<vector<string>> result;
        gen_chains_all(words, words_size, result);
        output_screen(result);
    } else if (is_word_chain || is_count_chain) {
        vector<string> result;
        if (is_word_chain) {
            if (gen_chain_word(words, words_size, result, head, tail, reject, enableLoop) == -1) return 0;
        } else {
            if (gen_chain_char(words, words_size, result, head, tail, reject, enableLoop) == -1) return 0;
        }
        output_file(result);
    }

    return 0;
}

// 需要修改：-n参数不与其他参数混合使用
int parse_args(int argc, char *argv[]) {
    // 可能有问题，第0个参数是exe文件
    int i = 1;
    try {
        while (i < argc) {
            if (argv[i][0] == '-') {
                if (!regex_match(argv[i], arg_pattern)) {
                    throwSelfException(ARGS_UNIDENTIFIED, "");
                }
                if (strcmp(argv[i], "-n") == 0) {
                    if (is_all_chain) throwSelfException(ARGS_DUPLICATE, "");
                    is_all_chain = true;
                } else if (strcmp(argv[i], "-w") == 0) {
                    if (is_word_chain) throwSelfException(ARGS_DUPLICATE, "");
                    is_word_chain = true;
                } else if (strcmp(argv[i], "-c") == 0) {
                    if (is_count_chain) throwSelfException(ARGS_DUPLICATE, "");
                    is_count_chain = true;
                } else if (strcmp(argv[i], "-h") == 0) {
                    if (parse_additional_args(is_head, head, argv, ++i, argc) == -1) return -1;
                } else if (strcmp(argv[i], "-t") == 0) {
                    if (parse_additional_args(is_tail, tail, argv, ++i, argc) == -1) return -1;
                } else if (strcmp(argv[i], "-j") == 0) {
                    if (parse_additional_args(is_not_head, reject, argv, ++i, argc) == -1) return -1;
                } else if (strcmp(argv[i], "-r") == 0) {
                    if (enableLoop) throwSelfException(ARGS_DUPLICATE, "");
                    enableLoop = true;
                }
            } else {
                // 文件不合法，不是以.txt结尾
                if (!regex_match(argv[i], txt_pattern)) {
                    throwSelfException(FILE_ILLEGAL, "");
                }
                // 文件多于一个
                if (!input_file.empty()) {
                    throwSelfException(FILE_MORE_THAN_ONE, "");
                }
                input_file = argv[i];
            }
            i++;
        }
        if (input_file.empty()) {
            throwSelfException(FILE_LACK, "");
        }
        if ((is_count_chain && is_all_chain) || (is_count_chain && is_word_chain) || (is_all_chain && is_word_chain)) {
            throwSelfException(BASIC_ARGS_CONFLICT, "");
        }
        if (!is_all_chain && !is_count_chain && !is_word_chain) {
            throwSelfException(BASIC_ARGS_LACK, "");
        }
    } catch (const exception &e) {
        cerr << e.what() << endl;
        return -1;
    }
    return 0;
}

/* 处理-h-t-j三个附加参数，主要是异常处理 */
int parse_additional_args(bool &flag, char &ch, char *argv[], int &i, int size) {
    try {
        if (flag) throwSelfException(ARGS_DUPLICATE, "");
        flag = true;
        if (is_all_chain) {
            throwSelfException(ARG_N_CONFLICT, "");
        } else if (i >= size) {                     // 参数后无其他信息，说明没有附加值
            throwSelfException(VALUE_LACK, "");
        } else if (strlen(argv[i]) > 1) {       // 后续值的长度大于1，三种:多个字符---参数过多；参数-(arg)，文件名---参数缺失
            // 参数或文件名
            if (regex_match(argv[i], arg_pattern) || regex_match(argv[i], txt_pattern)) {
                throwSelfException(VALUE_LACK, "");
            }
            // 出现了其他非字母字符
            int arg_size = (int )strlen(argv[i]);
            for (int j = 0; j < arg_size; j++) {
                if (!isalpha(argv[i][j])) {
                    throwSelfException(VALUE_ILLEGAL_ARGS, "");
                }
            }
            // 全是字母
            throwSelfException(VALUE_MORE_THAN_ONE, "");
        } else if (isalpha(argv[i][0])) {       // 后续值长度为1，且为字母，符合
            ch = (char )tolower(argv[i][0]);
        } else {                                    // 值的长度为1，但是不是字符，说明非法
            throwSelfException(VALUE_ILLEGAL_ARGS, "");
        }
    } catch (const exception &e) {
        cerr << e.what() << endl;
        i--;
        return -1;
    }
    return 0;
}