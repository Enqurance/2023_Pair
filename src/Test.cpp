#include "FileReader.h"

/* 当前文件执行在bin目录下 */

int main() {
    FileReader f;
    int len;
    f.read_file("../src/Testfile1.txt", &len);
    f.print_words();
}

