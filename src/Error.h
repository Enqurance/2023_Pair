//
// Created by Yoga on 2023/3/14.
//

#ifndef WORDLIST_ERROR_H
#define WORDLIST_ERROR_H

#include "bits/stdc++.h"

using namespace std;

class SelfException {
protected:
    string message;

public:
    SelfException(const string& exception_message = "Exception message not initialized!") {
        this->message = exception_message;
    }

    virtual ~SelfException() = default;

    virtual const string checkMessage() const {
        return message;
    }
};

// 参数相关错误
class ArgsNotMatchException: public SelfException {
public:
    ArgsNotMatchException(const string& exception_message) {
        this->message = "args: " + exception_message;
    }
};

// 文件读写相关错误
class FileException: public SelfException {
public:
    FileException(const string& exception_message) {
        this->message = "file: " + exception_message;
    }
};

#endif //WORDLIST_ERROR_H
