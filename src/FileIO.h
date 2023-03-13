#pragma once

#include "bits/stdc++.h"

#ifdef FILEIO_EXPORTS
#define FILEIO_API __declspec(dllexport)
#else
#define FILEIO_API __declspec(dllimport)
#endif

using namespace std;

class FILEIO_API FileIO {
public:
    FileIO() = default;

    // 读文件，输出文件
    int read_file(const string &filename) {
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
        words_cnt = int(words.size());
        return 1;
    }

    int output_screen(vector<vector<string>> all_chains) {
        int all_chains_size = (int) all_chains.size();
        cout << all_chains_size << endl;
        for (int i = 0; i < all_chains_size; i++) {
            int single_size = (int) all_chains[i].size();
            for (int j = 0; j < single_size; j++) {
                cout << all_chains[i][j] << " ";
            }
            cout << endl;
        }
        return 1;
    }

    int output_file(vector<string> longest_chain) {
        ofstream file;
        file.open("solution.txt", ios::out);
        if (!file.is_open()) {
            cerr << "cannot output to solution.txt!" << endl;
            return -1;
        }
        int longest_chain_size = (int) longest_chain.size();
        for (int i = 0; i < longest_chain_size; i++) {
            file << longest_chain[i] << endl;
        }
        file.close();
        return 1;
    }

    vector<string> get_words(int &size) {
        size = words_cnt;
        return words;
    }

//    void print_words() {
//        for (int i = 0; i < words_cnt; i++) {
//            cout << words[i] << endl;
//        }
//    }

private:
    // 读入时，单词储存相关
    unordered_map<string, int> word_map;    //记录单词是否重复，int同时记录单词长度
    vector<string> words;
    int words_cnt = 0;

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
    }

    void store_word(string &word) {     /* 储存单词的函数 */
        transform(word.begin(), word.end(), word.begin(), ::tolower);
        if (word_map.find(word) == word_map.end()) {    //添加单词操作
            words.push_back(word);
            word_map[word] = (int) word.length();
        }
    }
};