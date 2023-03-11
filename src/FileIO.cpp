//
// Created by Yoga on 2023/3/10.
//

#include "FileIO.h"

using namespace std;

// 读文件，输出文件
int FileIO::read_file(const string &filename) {
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

int FileIO::output_screen(vector<vector<string>> all_chains) {
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

int FileIO::output_file(vector<string> longest_chain) {
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

vector<string> FileIO::get_words(int &size) {
    size = words_cnt;
    return words;
}

void FileIO::parse_words(const string &context) {   /* 解析单词的函数 */
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

void FileIO::store_word(string &word) {     /* 储存单词的函数 */
    transform(word.begin(), word.end(), word.begin(), ::tolower);
    if (word_map.find(word) == word_map.end()) {    //添加单词操作
        words.push_back(word);
        word_map[word] = (int) word.length();
    }
}

