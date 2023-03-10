#include "FileReader.h"

int main() {
    FileReader f;
    f.read_file("../Testfile.txt");
    f.print_words();
}

