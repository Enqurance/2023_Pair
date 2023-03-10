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
    int read_file(const std::string &filename) {   /* 读文件，目前只能读绝对路径 */
        ifstream file;
        file.open(filename, ios::in);
        if (!file.is_open()) {
//            fault[file_not_exists] = true;
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
    }

    void store_word(string &word) {     /* 储存单词的函数 */
        transform(word.begin(), word.end(), word.begin(), ::tolower);
        if (word_map.find(word) == word_map.end()) {    //添加单词操作
            words.push_back(word);
            word_map[word] = (int) word.length();
        }
    }

    void output_result(int op, vector<vector<string>> all_chain, vector<string> longest_chain) {
        if (op == is_all_chain) {
            int all_chain_size = (int )all_chain.size();
            cout << all_chain_size << endl;
            for (int i = 0; i < all_chain_size; i++) {
                int single_size = (int )all_chain[i].size();
                for (int j = 0; j < single_size; j++) {
                    cout << all_chain[i][j] << " ";
                }
                cout << endl;
            }
        } else if (op == is_word_chain || op == is_count_chain) {
            ofstream file;
            file.open("solution.txt", ios::out);
            int longest_chain_size = (int )longest_chain.size();
            for (int i = 0; i < longest_chain_size; i++) {
                file << longest_chain[i] << endl;
            }
            file.close();
        }
    }

    vector<string> get_words() {
        return words;
    }

private:
    bool fault[10];         // 储存异常信息
    // 读入时，单词储存相关
    unordered_map<string, int> word_map;    //记录单词是否重复，int同时记录单词长度
    vector<string> words;

    enum file_op {
        is_all_chain,
        is_count_chain,
        is_word_chain
    };
};


#endif //WORDLIST_FILEREADER_H
