#include "iostream"
#include "fstream"
#include "vector"
#include "Node.h"

using namespace std;

vector<string> parse(const string &context);

vector<Node> create_nodes(vector<string> words);

int open_file(const char *filename, string &context);

int main(int argc, char *argv[]) {
    string context;
    open_file("/Users/enqurance/Desktop/BUAA/大三下/罗杰软工/结对编程/InitProject/Testfile.txt", context);
    parse(context);
    return 0;
}

//vector<Node> create_nodes(vector<string> words) {
//
//}

int open_file(const char *filename, string &context) {   /* 读文件，目前只能读绝对路径 */
    ifstream file(filename, ios::in);
    if (!file.is_open()) {
        cerr << "文件打开失败！" << endl;
        return -1;
    }
    string temp;
    while (getline(file, temp)) {
        transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
        context += temp;
    }
    cout << context + "\n";
    return 1;
}


vector<string> parse(const string &context) {   /* 解析单词的函数 */
    vector<string> words;
    int size = int(context.length());
    for (int i = 0; i < size; i++) {
        string word;
        for (; i < size; i++) {
            if (isalpha(context[i])) {
                word.append(1, context[i]);
            } else {
                break;
            }
        }
        if (!word.empty()) {
            words.push_back(word);
        }
    }
    for (const auto& word: words) {
        cout << word << endl;
    }
    return words;
}

vector<Node> create_nodes(vector<string> words) {

}