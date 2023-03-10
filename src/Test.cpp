#include "FileIO.h"

int main() {
    FileIO f;
    f.read_file("../Testfile1.txt");
/* 当前文件执行在bin目录下 */
    f.print_words();
}

