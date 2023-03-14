#include "bits/stdc++.h"
#include "windows.h"

#define MAX 10000

using namespace std;

void parse_args(int argc, char *argv[]);
void parse_additional_args(bool &flag, char &ch, char *argv[], int &i, int size);

// 程序参数相关
string input_file;
bool is_all_chain = false;             // -n
bool is_count_chain = false;   // -w
bool is_word_chain = false;    // -c
bool is_head = false;      char head = 0;      // -h
bool is_tail = false;      char tail = 0;      // -t
bool is_not_head = false;  char reject = 0;  // -j
bool enableLoop = false;          // -r

// 程序错误处理相关，要换为异常处理
enum args_fault {
    file_not_exists,    // 文件不存在
    file_illegal,       // 文件不合法

    args_conflict,      // 参数类型冲突
    args_no_basic,      // 没有基本类型参数

    additional_lack_character,  // 附加参数缺少附带字母-h-t-j
    additional_not_match,        // 字母格式不正确
};
bool fault[10];         // 储存异常信息

// 获取函数地址
typedef int (*READ_FILE)(const string &filename);
typedef int (*OUTPUT_SCREEN)(const vector<vector<string>> &all_chains);
typedef int (*OUTPUT_FILE)(const vector<string> &longest_chain);
typedef int (*GET_WORDS)(vector<string> &words);

typedef int (*GEN_CHAINS_ALL)(const vector<string> &words, int len, vector<vector<string>> &result);
typedef int (*GEN_CHAINS_WORD)(const vector<string> &words, int len, vector<string> &result,
                               char head, char tail, char reject, bool enable_loop);
typedef int (*GEN_CHAINS_CHAR)(const vector<string> &words, int len, vector<string> &result,
                               char head, char tail, char reject, bool enable_loop);

int main(int argc, char *argv[]) {
    /* 读取命令行，获取参数信息，检查冲突 */
    parse_args(argc, argv);

    // 加载lib.dll库
    HMODULE LibDll = LoadLibrary("lib.dll");
    if (!LibDll) {
        cout << "Unable to load LIB DLL!" << endl;
        return 1;
    }

    auto read_file = (READ_FILE) GetProcAddress(LibDll, "read_file");
    auto output_screen = (OUTPUT_SCREEN) GetProcAddress(LibDll, "output_screen");
    auto output_file = (OUTPUT_FILE) GetProcAddress(LibDll, "output_file");
    auto get_words = (GET_WORDS) GetProcAddress(LibDll, "get_words");

    read_file(input_file);

//    f->read_file(input_file);

    vector<string> words;
    int words_size = get_words(words);
//    vector<string> words = f->get_words(words_size);

    // 加载core.dll库
    HINSTANCE CoreDll = LoadLibrary("core.dll");
    if (!CoreDll) {
        cout << "Unable to load CORE DLL!" << endl;
        return 1;
    }

    auto gen_chains_all = (GEN_CHAINS_ALL) GetProcAddress(CoreDll, "gen_chains_all");
    auto gen_chain_word = (GEN_CHAINS_WORD) GetProcAddress(CoreDll, "gen_chain_word");
    auto gen_chain_char = (GEN_CHAINS_CHAR) GetProcAddress(CoreDll, "gen_chain_char");
    if (!gen_chains_all || !gen_chain_word || !gen_chain_char) {
        cout << "Unable to get function address!" << endl;
        return 1;
    }

    if (is_all_chain) {
        vector<vector<string>> result;
        gen_chains_all(words, words_size, result);

        output_screen(result);
//        f->output_screen(result);
    } else if (is_word_chain || is_count_chain) {
        vector<string> result;
        if (is_word_chain) {
            gen_chain_word(words, words_size, result, head, tail, reject, enableLoop);
        } else {
            gen_chain_char(words, words_size, result, head, tail, reject, enableLoop);
        }

        output_file(result);
//        f->output_file(result);
    }
    return 0;
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
            int size = (int )input_file.length();
            if ((input_file.find(".txt") == std::string::npos) || (input_file.find_last_of(".txt") != size - 4)) {
                fault[file_illegal] = true;
            }
        }
        i++;
    }
    if ((is_count_chain && is_all_chain) || (is_count_chain && is_word_chain) || (is_all_chain && is_word_chain)) {
        fault[args_conflict] = true;
    }
    if (!is_all_chain && !is_count_chain && !is_word_chain) {
        fault[args_no_basic] = true;
    }
}

/* 处理-h-t-j三个附加参数，主要是异常处理 */
void parse_additional_args(bool &flag, char &ch, char *argv[], int &i, int size) {
    flag = true;
    if (is_all_chain) {
        fault[args_conflict] = true;
    } else if ((i + 1 < size) && (strlen(argv[i+1]) == 1) && isalpha(argv[i+1][0])) {
        ch = argv[++i][0];
    } else if ((i + 1 == size) || (strlen(argv[i+1]) == 0)) {
        // 错误处理，附加参数后缺失字母
        fault[additional_lack_character] = true;
    } else {
        // 错误处理，附加参数后，格式不匹配
        fault[additional_not_match] = true;
    }
}