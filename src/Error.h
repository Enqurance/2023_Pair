//
// Created by ZYL on 2023/3/14.
//

#ifndef WORDLIST_ERROR_H
#define WORDLIST_ERROR_H

#include <string>
#include "exception"

using namespace std;

// 程序错误处理相关，要换为异常处理
enum all_exception_state {
    FILE_NOT_EXIST,         // 文件不存在
    FILE_ILLEGAL,           // 文件不合法
    FILE_LACK,              // 缺少输入文件
    FILE_MORE_THAN_ONE,     // 输入文件多于一个

    ARGS_UNIDENTIFIED,      // 未定义的参数
    ARGS_DUPLICATE,         // 重复参数

    ARG_N_CONFLICT,         // -n参数冲突

    VALUE_LACK,             // -h-j-t的参数值缺失
    VALUE_MORE_THAN_ONE,    // -h-j-t的参数多于一个字符
    VALUE_ILLEGAL_ARGS,     // -h-j-t的参数值不合法(不是字母)

    BASIC_ARGS_CONFLICT,    // 基础参数冲突-c-w-n
    BASIC_ARGS_LACK,        // 缺少基础参数-c-w-n

    LOOP_ILLEGAL,           // 不要求环，但是单词成环

    RESULT_TOO_LARGE,       // 结果长度超过20000
};

class SelfException : public exception {
protected:
    int exception_state;
    string info;
    const char* message{};

private:
    void generateMessage() {
        switch (exception_state) {
            case FILE_ILLEGAL:
                message = "Error: File illegal. Probably it's not a TXT file!";
                break;
            case FILE_LACK:
                message = "Error: There is no input TXT included!";
                break;
            case FILE_MORE_THAN_ONE:
                message = "Error: There are more than one TXT included!";
                break;
            case FILE_NOT_EXIST:
                message = "Error: There is no TXT file in this path! Please make sure the path is correct!";
                break;
            case ARGS_UNIDENTIFIED:
                message = "Error: Unidentified arg, please choose arg from (-n,-c,-w,-h,-t,-j)!";
                break;
            case ARGS_DUPLICATE:
                message = "Error: Duplicate arg!";
                break;
            case ARG_N_CONFLICT:
                message = "Error: Arg -n cannot combine with other args!";
                break;
            case VALUE_LACK:
                message = "Error: Lack value for arg (-h/-j/-t)!";
                break;
            case VALUE_MORE_THAN_ONE:
                message = "Error: More than one value for arg (-h/-j/-t)!";
                break;
            case VALUE_ILLEGAL_ARGS:
                message = "Error: Illegal value for arg (-h/-j/-t), please enter character!";
                break;
            case BASIC_ARGS_CONFLICT:
                message = "Error: Arg(-n/-c/-w) conflict!";
                break;
            case BASIC_ARGS_LACK:
                message = "Error: Lack of basic arg(-n/-c/-w)!";
                break;
            case LOOP_ILLEGAL:
                message = "Error: There is a words loop included without permission!";
                break;
            case RESULT_TOO_LARGE:
                message = "Error: Too large for the results(length over 20000)!";
                break;
        }
    }

public:
    SelfException(const SelfException&) noexcept = default;

    explicit SelfException(const int error_state = -1, const string& info = "") {
        this->exception_state = error_state;
        this->info = info;
        generateMessage();
    }

    ~SelfException() override = default;

    const char* what() const noexcept override {
        return message;
    }
};

extern "C" __declspec(dllexport) void throwSelfException(const int error_state = -1, const string& info = "") {
    auto* e = new SelfException(error_state, info);
    throw *e;
}

#endif //WORDLIST_ERROR_H
