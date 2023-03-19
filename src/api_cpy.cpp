//
// Created by leera on 2023/3/17.
//

// 另外松耦合对接小组的接口

#include "vector"
#include "string"
#include "cstring"
#include "Core.h"

using namespace std;

struct cpyRetOneDim {
    char *dataList[2000];
    int dataNum;
    int result;
};

struct cpyRetTwoDim {
    char *dataList[2000][1000];
    int dataNumOne[2000];
    int dataNumTwo;
};

vector<string> charArrayToVector(char** charArray, int size) {
    vector<string> result;
    for (int i = 0; i < size; i++) {
        result.emplace_back(charArray[i]);
    }
    return result;
}

extern "C" __declspec(dllexport)
cpyRetTwoDim *gen_chains_all_cpy(char **words, int len) {
    vector<vector<string>> result;
    auto *retResult = (cpyRetTwoDim *) malloc(sizeof(cpyRetTwoDim));
    vector<string> new_words = charArrayToVector(words, len);
    int size = gen_chains_all(new_words, len, result);
    retResult->dataNumTwo = size;
    for (int i = 0; i < size; i++) {
        retResult->dataNumOne[i] = result[i].size();
        for (int j = 0; j < result[i].size(); j++) {
//            retResult->dataList[i][j] = result[i][j].c_str();
            strcpy(retResult->dataList[i][j], result[i][j].c_str());
        }
    }
    return retResult;
}


extern "C" __declspec(dllexport)
cpyRetOneDim *
gen_chain_word_cpy(char **words, int len, char head, char tail, char reject, bool en_loop) {
    vector<string> result;
    auto *retResult = (cpyRetOneDim *) malloc(sizeof(cpyRetOneDim));
    vector<string> new_words = charArrayToVector(words, len);
    int size = gen_chain_word(new_words, len, result, head, tail, reject, en_loop);
    retResult->dataNum = result.size();
    retResult->result = size;
    for (int i = 0; i < size; i++) {
        retResult->dataList[i] = (char *) result[i].c_str();
    }

//    auto *retResult = (cpyRetOneDim *) malloc(sizeof(cpyRetOneDim));
//    for (int i = 0; i < len; i++) {
//        retResult->dataList[i] = *(words + i);
//    }
//    retResult->dataNum = len;
//    retResult->result = len;
    return retResult;
}

extern "C" __declspec(dllexport)
cpyRetOneDim *gen_chain_char_cpy(char **words, int len, char head, char tail, char reject, bool en_loop) {
    vector<string> result;
    auto *retResult = (cpyRetOneDim *) malloc(sizeof(cpyRetOneDim));
    vector<string> new_words = charArrayToVector(words, len);
    int size = gen_chain_char(new_words, len, result, head, tail, reject, en_loop);
    retResult->dataNum = result.size();
    retResult->result = size;
    for (int i = 0; i < size; i++) {
        retResult->dataList[i] = (char *) result[i].c_str();
    }

    return retResult;
}
