#include "iostream"
#include "fstream"
#include "vector"

using namespace std;

vector<string> parse(const string &context);

int main(int argc, char *argv[]) {
    parse("I have reached the top of the moun8tain and reached the bottom, both of which have benefited me a lot");
    return 0;
}


vector<string> parse(const string &context) {
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
        if(word.size() > 0){
            words.push_back(word);
        }
    }
    for (auto word: words) {
        cout << word << endl;
    }
    return words;
}