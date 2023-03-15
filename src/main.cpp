#include "bits/stdc++.h"
#include "windows.h"

#define MAX 10000

using namespace std;

int load_dll();
void free_dll();

void parse_args(int argc, char *argv[]);

void parse_additional_args(bool &flag, char &ch, char *argv[], int &i, int size);

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

    VALUE_LACK,             // -h-j-t的参数值缺失
    VALUE_MORE_THAN_ONE,    // -h-j-t的参数多于一个字符
    VALUE_ILLEGAL_ARGS,     // -h-j-t的参数值不合法(不是字母)

    BASIC_ARGS_CONFLICT,    // 基础参数冲突-c-w-n
    BASIC_ARGS_LACK,        // 缺少基础参数-c-w-n

    LOOP_ILLEGAL,           // 不要求环，但是单词成环
};

int main(int argc, char *argv[]) {
    // 加载dll失败，直接返回
    if (load_dll() == -1) return 0;

    /* 读取命令行，获取参数信息，检查冲突 */
    parse_args(argc, argv);

    read_file(input_file);

    vector<string> words;
    int words_size = get_words(words);

    if (is_all_chain) {
        vector<vector<string>> result;
        gen_chains_all(words, words_size, result);
        output_screen(result);
    } else if (is_word_chain || is_count_chain) {
        vector<string> result;
        if (is_word_chain) {
            gen_chain_word(words, words_size, result, head, tail, reject, enableLoop);
        } else {
            gen_chain_char(words, words_size, result, head, tail, reject, enableLoop);
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
    throw_self_exception = (THROW_SELF_EXCEPTION) GetProcAddress(LibDll, "ThrowSelfException");
    if (!throw_self_exception) {
        cerr << "this !" << endl;
    }
    read_file = (READ_FILE) GetProcAddress(LibDll, "read_file");
    output_screen = (OUTPUT_SCREEN) GetProcAddress(LibDll, "output_screen");
    output_file = (OUTPUT_FILE) GetProcAddress(LibDll, "output_file");
    get_words = (GET_WORDS) GetProcAddress(LibDll, "get_words");

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

    gen_chains_all = (GEN_CHAINS_ALL) GetProcAddress(CoreDll, "gen_chains_all");
    gen_chain_word = (GEN_CHAINS_WORD) GetProcAddress(CoreDll, "gen_chain_word");
    gen_chain_char = (GEN_CHAINS_CHAR) GetProcAddress(CoreDll, "gen_chain_char");
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
void parse_args(int argc, char *argv[]) {
    int i = 0;
    while (i < argc) {
        if (strcmp(argv[i], "-n") == 0) {
            is_all_chain = true;
        } else if (strcmp(argv[i], "-w") == 0) {
            is_word_chain = true;
        } else if (strcmp(argv[i], "-c") == 0) {
            is_count_chain = true;
        } else if (strcmp(argv[i], "-h") == 0) {
            parse_additional_args(is_head, head, argv, i, argc);
        } else if (strcmp(argv[i], "-t") == 0) {
            parse_additional_args(is_tail, tail, argv, i, argc);
        } else if (strcmp(argv[i], "-j") == 0) {
            parse_additional_args(is_not_head, reject, argv, i, argc);
        } else if (strcmp(argv[i], "-r") == 0) {
            enableLoop = true;
        } else {
            input_file = argv[i];
            // 没有.txt出现 或者.txt不是文件名结尾
            int size = (int) input_file.length();
            if ((input_file.find(".txt") == std::string::npos) || (input_file.find_last_of(".txt") != size - 4)) {
//                fault[file_illegal] = true;
            }
        }
        i++;
    }
    if ((is_count_chain && is_all_chain) || (is_count_chain && is_word_chain) || (is_all_chain && is_word_chain)) {
//        fault[args_conflict] = true;
    }
    if (!is_all_chain && !is_count_chain && !is_word_chain) {
//        fault[args_no_basic] = true;
    }
}

/* 处理-h-t-j三个附加参数，主要是异常处理 */
void parse_additional_args(bool &flag, char &ch, char *argv[], int &i, int size) {
    flag = true;
    if (is_all_chain) {
//        fault[args_conflict] = true;
    } else if ((i + 1 < size) && (strlen(argv[i + 1]) == 1) && isalpha(argv[i + 1][0])) {
        ch = argv[++i][0];
    } else if ((i + 1 == size) || (strlen(argv[i + 1]) == 0)) {
        // 错误处理，附加参数后缺失字母
//        fault[additional_lack_character] = true;
    } else {
        // 错误处理，附加参数后，格式不匹配
//        fault[additional_not_match] = true;
    }
}