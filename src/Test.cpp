<<<<<<< HEAD
#include "FileReader.h"

/* 当前文件执行在bin目录下 */

int main() {
    FileReader f;
    int len;
    f.read_file("../src/Testfile1.txt", &len);
=======
#include "FileIO.h"

int main() {
    FileIO f;
    f.read_file("../Testfile1.txt");
/* 当前文件执行在bin目录下 */
>>>>>>> refs/remotes/origin/main
    f.print_words();
}

