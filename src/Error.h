//
// Created by Yoga on 2023/3/14.
//

#ifndef WORDLIST_ERROR_H
#define WORDLIST_ERROR_H

#include "bits/stdc++.h"

using namespace std;

// 程序错误处理相关，要换为异常处理
enum all_exception_state {
    file_not_exists,    // 文件不存在
    file_illegal,       // 文件不合法

    args_conflict,      // 参数类型冲突
    args_no_basic,      // 没有基本类型参数

    additional_lack_character,  // 附加参数缺少附带字母-h-t-j
    additional_not_match,        // 字母格式不正确
};

class SelfException {
protected:
    int error_state;

public:
    explicit SelfException(const int error_state = -1) {
        this->error_state = error_state;
    }

    virtual ~SelfException() = default;

    virtual string checkMessage() const {
        return "The exception hasn't been initialized!";
    }
};

// 参数相关错误
class ArgsNotMatchException: public SelfException {
public:
    ArgsNotMatchException(const int error_state) {

    }

    string checkMessage() const override {
        switch (error_state) {
            case args_no_basic: return "There are no basic args(-n -w -c)!";
        }
    }
};

// 文件读写相关错误
class FileException: public SelfException {
public:
    FileException(const int error_state) {

    }
};

#endif //WORDLIST_ERROR_H
