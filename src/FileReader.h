//
// Created by Enqurance on 2023/3/10.
//
#include "bits/stdc++.h"
#include "Node.h"

using namespace std;

#ifndef WORDLIST_FILEREADER_H
#define WORDLIST_FILEREADER_H


class FileReader {
public:
    // 读文件，输出文件
    int read_file(const std::string &filename) {
        ifstream file;
        file.open(filename, ios::in);
        if (!file.is_open()) {
            cerr << "cannot open file!" << endl;
            return -1;
        }
        string temp;
        while (getline(file, temp)) {
            parse_words(temp);
        }
        file.close();
        return 1;
    }

    void parse_words(const string &context) {   /* 解析单词的函数 */
        int size = int(context.length());
        int i = 0;
        string word;
        while (i < size) {
            if (isalpha(context[i])) {
                word.append(1, context[i]);
            } else if (!word.empty()) {
                store_word(word);
                word.clear();
            }
            i++;
        }
        if (!word.empty()) {
            store_word(word);
        }
        copy();
    }

    void store_word(string &word) {     /* 储存单词的函数 */
        transform(word.begin(), word.end(), word.begin(), ::tolower);
        if (word_map.find(word) == word_map.end()) {    //添加单词操作
            words_vec.push_back(word);
            word_map[word] = (int) word.length();
        }
    }

    void copy() {
        int size = int(words_vec.size());
        words_cnt = size;
        for (int i = 0; i < size; i++) {
            words[i] = const_cast<char *>(words_vec[i].c_str());
        }
    }

    void print_words() {
        for (int i = 0; i < words_cnt; i++) {
            cout << words[i] << endl;
        }
    }

    char **get_words() {
        return words;
    }

private:
    bool fault[10];         // 储存异常信息
    // 读入时，单词储存相关

    enum file_op {
        is_all_chain,
        is_count_chain,
        is_word_chain
    };

    unordered_map<string, int> word_map;    //记录单词是否重复，int同时记录单词长度
    vector<string> words_vec;
    int words_cnt = 0;
    char *words[20005];
};


#endif //WORDLIST_FILEREADER_H
