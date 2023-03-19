#include "bits/stdc++.h"
#include "windows.h"

#define MAX 10005

using namespace std;

int load_dll();

void free_dll();

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

// 获取函数地址
typedef void (*THROW_SELF_EXCEPTION)(const int error_state, const string &info);

typedef int (*READ_FILE)(const string &filename);

typedef int (*OUTPUT_SCREEN)(const vector<vector<string>> &all_chains);

typedef int (*OUTPUT_FILE)(const vector<string> &longest_chain);

typedef int (*GET_WORDS)(vector<string> &words);

typedef int (*GEN_CHAINS_ALL)(const vector<string> &words, int len, vector<vector<string>> &result);

typedef int (*GEN_CHAINS_WORD)(const vector<string> &words, int len, vector<string> &result,
                               char head, char tail, char reject, bool enable_loop);

typedef int (*GEN_CHAINS_CHAR)(const vector<string> &words, int len, vector<string> &result,
                               char head, char tail, char reject, bool enable_loop);

HMODULE LibDll, CoreDll;

THROW_SELF_EXCEPTION throw_self_exception;
READ_FILE read_file;
OUTPUT_SCREEN output_screen;
OUTPUT_FILE output_file;
GET_WORDS get_words;
GEN_CHAINS_ALL gen_chains_all;
GEN_CHAINS_WORD gen_chain_word;
GEN_CHAINS_CHAR gen_chain_char;

enum all_exception_state {
    FILE_NOT_EXIST,         // 文件不存在
    FILE_ILLEGAL,           // 文件不合法
    FILE_LACK,              // 缺少输入文件
    FILE_MORE_THAN_ONE,     // 输入文件多于一个

    ARGS_UNIDENTIFIED,      // 未定义的参数
    ARGS_DUPLICATE,         // 重复参数
    ARG_N_CONFLICT,

    VALUE_LACK,             // -h-j-t的参数值缺失
    VALUE_MORE_THAN_ONE,    // -h-j-t的参数多于一个字符
    VALUE_ILLEGAL_ARGS,     // -h-j-t的参数值不合法(不是字母)

    BASIC_ARGS_CONFLICT,    // 基础参数冲突-c-w-n
    BASIC_ARGS_LACK,        // 缺少基础参数-c-w-n

    LOOP_ILLEGAL,           // 不要求环，但是单词成环
};

static const regex arg_pattern("^(\\-(n|c|w|h|t|j|r))$");
// 可以匹配C:\, D:\开头的绝对路径，路径中允许包含..和.
static const regex txt_pattern(R"(^([a-zA-Z]:\\)?(([a-zA-Z0-9]+\\)*((..|.)\\)*)*[a-zA-Z0-9]+.(txt|TXT)$)");

int main(int argc, char *argv[]) {
    // 加载dll失败，直接返回
    if (load_dll() == -1) return 0;

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

    free_dll();
    return 0;
}

int load_dll() {
    // 加载lib.dll库
    LibDll = LoadLibrary("lib.dll");
    if (!LibDll) {
        cerr << "Unable to load LIB DLL!" << endl;
        return -1;
    }
    throw_self_exception = reinterpret_cast<THROW_SELF_EXCEPTION>(GetProcAddress(LibDll, "throwSelfException"));
    if (!throw_self_exception) {
        cerr << "this !" << endl;
    }
    read_file = reinterpret_cast<READ_FILE>(GetProcAddress(LibDll, "read_file"));
    output_screen = reinterpret_cast<OUTPUT_SCREEN>(GetProcAddress(LibDll, "output_screen"));
    output_file = reinterpret_cast<OUTPUT_FILE>(GetProcAddress(LibDll, "output_file"));
    get_words = reinterpret_cast<GET_WORDS>(GetProcAddress(LibDll, "get_words"));

    if (!read_file || !output_screen || !output_file || !get_words || !throw_self_exception) {
        cerr << "Unable to get function address of lib.dll!" << endl;
        return -1;
    }

    // 加载core.dll库
    CoreDll = LoadLibrary("core.dll");
    if (!CoreDll) {
        cerr << "Unable to load CORE DLL!" << endl;
        return -1;
    }

    gen_chains_all = reinterpret_cast<GEN_CHAINS_ALL>(GetProcAddress(CoreDll, "gen_chains_all"));
    gen_chain_word = reinterpret_cast<GEN_CHAINS_WORD>(GetProcAddress(CoreDll, "gen_chain_word"));
    gen_chain_char = reinterpret_cast<GEN_CHAINS_CHAR>(GetProcAddress(CoreDll, "gen_chain_char"));
    if (!gen_chains_all || !gen_chain_word || !gen_chain_char) {
        cerr << "Unable to get function address of core.dll!" << endl;
        return -1;
    }
    return 0;
}

void free_dll() {
    FreeLibrary(LibDll);
    FreeLibrary(CoreDll);
}

// 需要修改：-n参数不与其他参数混合使用
int parse_args(int argc, char *argv[]) {
    // 可能有问题，第0个参数是exe文件
    int i = 1;
    try {
        while (i < argc) {
            if (argv[i][0] == '-') {
                if (!regex_match(argv[i], arg_pattern)) {
                    throw_self_exception(ARGS_UNIDENTIFIED, "");
                }
                if (strcmp(argv[i], "-n") == 0) {
                    is_all_chain = true;
                } else if (strcmp(argv[i], "-w") == 0) {
                    is_word_chain = true;
                } else if (strcmp(argv[i], "-c") == 0) {
                    is_count_chain = true;
                } else if (strcmp(argv[i], "-h") == 0) {
                    if (parse_additional_args(is_head, head, argv, ++i, argc) == -1) return -1;
                } else if (strcmp(argv[i], "-t") == 0) {
                    if (parse_additional_args(is_tail, tail, argv, ++i, argc) == -1) return -1;
                } else if (strcmp(argv[i], "-j") == 0) {
                    if (parse_additional_args(is_not_head, reject, argv, ++i, argc) == -1) return -1;
                } else if (strcmp(argv[i], "-r") == 0) {
                    enableLoop = true;
                }
            } else {
                // 文件不合法，不是以.txt结尾
                if (!regex_match(argv[i], txt_pattern)) {
                    throw_self_exception(FILE_ILLEGAL, "");
                }
                // 文件多于一个
                if (!input_file.empty()) {
                    throw_self_exception(FILE_MORE_THAN_ONE, "");
                }
                input_file = argv[i];
            }
            i++;
        }
        if (input_file.empty()) {
            throw_self_exception(FILE_LACK, "");
        }
        if ((is_count_chain && is_all_chain) || (is_count_chain && is_word_chain) || (is_all_chain && is_word_chain)) {
            throw_self_exception(BASIC_ARGS_CONFLICT, "");
        }
        if (!is_all_chain && !is_count_chain && !is_word_chain) {
            throw_self_exception(BASIC_ARGS_LACK, "");
        }
    } catch (const exception &e) {
        cerr << e.what() << endl;
        return -1;
    }
    return 0;
}

/* 处理-h-t-j三个附加参数，主要是异常处理 */
int parse_additional_args(bool &flag, char &ch, char *argv[], int &i, int size) {
    flag = true;
    try {
        if (is_all_chain) {
            throw_self_exception(ARG_N_CONFLICT, "");
        } else if (i >= size) {                     // 参数后无其他信息，说明没有附加值
            throw_self_exception(VALUE_LACK, "");
        } else if (strlen(argv[i]) > 1) {       // 后续值的长度大于1，三种:多个字符---参数过多；参数-(arg)，文件名---参数缺失
            // 参数或文件名
            if (regex_match(argv[i], arg_pattern) || regex_match(argv[i], txt_pattern)) {
                throw_self_exception(VALUE_LACK, "");
            }
            // 出现了其他非字母字符
            int arg_size = (int )strlen(argv[i]);
            for (int j = 0; j < arg_size; j++) {
                if (!isalpha(argv[i][j])) {
                    throw_self_exception(VALUE_ILLEGAL_ARGS, "");
                }
            }
            // 全是字母
            throw_self_exception(VALUE_MORE_THAN_ONE, "");
        } else if (isalpha(argv[i][0])) {       // 后续值长度为1，且为字母，符合
            ch = (char )tolower(argv[i][0]);
        } else {                                    // 值的长度为1，但是不是字符，说明非法
            throw_self_exception(VALUE_ILLEGAL_ARGS, "");
        }
    } catch (const exception &e) {
        cerr << e.what() << endl;
        i--;
        return -1;
    }
    return 0;
}