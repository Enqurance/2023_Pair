#include "FileIO.h"

int main() {
    FileIO f;
    f.read_file("../Testfile.txt");
    f.print_words();
}

