#include "FileReader.h"
/* 当前文件执行在bin目录下 */

int main() {
    FileReader f;
    f.read_file("../src/Testfile1.txt");
    f.print_words();
}

