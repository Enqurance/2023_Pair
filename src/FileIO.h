#ifndef WORDLIST_FILEIO_H
#define WORDLIST_FILEIO_H

#include "bits/stdc++.h"
#include "Node.h"

using namespace std;

class FileIO {
public:
    // 读文件，输出文件
    int read_file(const string &filename);

    int output_screen(vector<vector<string>> all_chains);

    int output_file(vector<string> longest_chain);

    vector<string> get_words(int &size);

private:
    // 读入时，单词储存相关
    unordered_map<string, int> word_map;    //记录单词是否重复，int同时记录单词长度
    vector<string> words;
    int words_cnt = 0;

    void parse_words(const string &context);

    void store_word(string &word);
};


#endif //WORDLIST_FILEIO_H
