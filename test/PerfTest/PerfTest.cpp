#include <gtest/gtest.h>
#include "string"
#include "../../src/PerfFileIO.h"
#include "../../src/PerfCore.h"

using namespace std;

void PerfTestOne();

void PerfTestTwo();

void PerfTestThree();

int main() {
//    PerfTestOne();
//    PerfTestTwo();
    PerfTestThree();
}

// most words
void PerfTestOne() {
    string filename = "../test/Testfiles/PTest1.txt";
    vector<string> words;
    vector<vector<string>> result;
    FileIO f = FileIO::getInstance();
    f.read_file(filename);
    int len = f.get_words(words);
    Core core = *new Core(words, len);
    core.genAllWordChain(result);
    FileIO::output_screen(result);
}

void PerfTestTwo() {
    string filename = "../test/Testfiles/PTest3.txt";
    vector<string> words;
    char c = 0;
    vector<string> result;
    FileIO f = FileIO::getInstance();
    f.read_file(filename);
    int len = f.get_words(words);
    Core core = *new Core(words, len, true, c, c, c, false);
    core.genMaxWordCountChain(result);
    FileIO::output_file(result);
}

// most chars
void PerfTestThree() {
    string filename = "../test/Testfiles/PTest3.txt";
    vector<string> words;
    char c = 0;
    vector<string> result;
    FileIO f = FileIO::getInstance();
    f.read_file(filename);
    int len = f.get_words(words);
    Core core = *new Core(words, len, true, c, c, c, true);
    core.genMaxWordCountChain(result);
    FileIO::output_file(result);
}


