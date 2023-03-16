#ifndef WORDLIST_FILEIO_H
#define WORDLIST_FILEIO_H

#include "bits/stdc++.h"
#include <filesystem>
#include "Node.h"
#include "Error.h"

using namespace std;

class FileIO {
public:
    static FileIO& getInstance() {
        return fileIO;
    }

    void initialize() {
        word_map.clear();
        words.clear();
        words_cnt = 0;
    }

    // 读文件，输出文件
    int read_file(const string &filename) {
        ifstream file(filename, ios::in);
        if (!file.good()) {
            try {
                throw SelfException(FILE_NOT_EXIST, filename);
            } catch (const SelfException &e) {
                cerr << e.what() << endl;
            }
            return -1;
        }
        initialize();
        string temp;
        while (getline(file, temp)) {
            parse_words(temp);
        }
        file.close();
        words_cnt = int(words.size());
        return 1;
    }

    static int output_screen(const vector<vector<string>> &all_chains) {
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

    static int output_file(const vector<string> &longest_chain) {
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

    int get_words(vector<string> &req_words) {
        req_words = words;
        return words_cnt;
    }

private:
    static FileIO fileIO;

    // 读入时，单词储存相关
    unordered_map<string, int> word_map;    //记录单词是否重复，int同时记录单词长度
    vector<string> words;
    int words_cnt = 0;

    FileIO() = default;

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

FileIO FileIO::fileIO;

#ifdef __cplusplus
extern "C" {
#endif

__declspec(dllexport) int read_file(const string &filename) {
    return FileIO::getInstance().read_file(filename);
}

__declspec(dllexport) int output_screen(const vector<vector<string>> &all_chains) {
    return FileIO::output_screen(all_chains);
}

__declspec(dllexport) int output_file(const vector<string> &longest_chain) {
    return FileIO::output_file(longest_chain);
}

__declspec(dllexport) int get_words(vector<string> &words) {
    return FileIO::getInstance().get_words(words);
}

#ifdef __cplusplus
}
#endif

#endif