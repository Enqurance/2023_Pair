#include "cstdio"
#include "cstring"
#include "iostream"
#include "fstream"
#include "vector"
#include "cstdlib"

using namespace std;

vector<string> parse(const string &context);

int open_file(const char *filename, string &context);

int main(int argc, char *argv[]) {
    string context;
    open_file("/Users/enqurance/Desktop/BUAA/大三下/罗杰软工/结对编程/InitProject/Testfile.txt", context);
    parse(context);
    return 0;
}

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
    int size = context.length();
    for (int i = 0; i < size; i++) {
        string word("");
        for (; i < size; i++) {
            if (isalpha(context[i])) {
                word.append(1, context[i]);
            } else {
                break;
            }
        }
        if (word.size() > 0) {
            words.push_back(word);
        }
    }
    for (auto word: words) {
        cout << word << endl;
    }
    return words;
}