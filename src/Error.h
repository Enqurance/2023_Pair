//
// Created by ZYL on 2023/3/14.
//

#ifndef WORDLIST_ERROR_H
#define WORDLIST_ERROR_H

#include "bits/stdc++.h"

using namespace std;

// 程序错误处理相关，要换为异常处理
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

class SelfException {
protected:
    int exception_state;
    string exception_message;

public:
    explicit SelfException(const int error_state = -1) {
        this->exception_state = error_state;
    }

    virtual ~SelfException() = default;

    void generateMessage() {
        switch (exception_state) {
            case FILE_ILLEGAL:
                exception_message = "文件不合法";
                break;
            case FILE_LACK:
                break;
            case FILE_MORE_THAN_ONE:
                break;
            case FILE_NOT_EXIST:
                break;
            case ARGS_UNIDENTIFIED:
                break;
            case ARGS_DUPLICATE:
                break;
            case VALUE_LACK:
                break;
            case VALUE_MORE_THAN_ONE:
                break;
            case VALUE_ILLEGAL_ARGS:
                break;
            case BASIC_ARGS_CONFLICT:
                break;
            case BASIC_ARGS_LACK:
                break;
            case LOOP_ILLEGAL:
                break;
        }
    }

    const string getMessage() const {
        return exception_message;
    }
};

// 内容错误
class ContextErrorException: public SelfException{
public:
    ContextErrorException(const int error_state){
        cerr << "文件内容只可包含ascii字符" << endl;
    }
};

#endif //WORDLIST_ERROR_H
