#include <iostream>
#include <fmt/format.h>
#include <stdio.h>

using fmt::format;
using std::cout;

void copy(char* from, char* to) {
    std::cout << from << '\n';
    system(format("cp {} {}", from, to).c_str());
}

int main(int argc, char * * argv) {
    if (argc != 3) {
        cout << format("Usage: {} binary output_directory\n", argv[0]);
        return 1;
    }

    FILE * ldd_file = popen(format("ldd {}", argv[1]).c_str(), "r");
    if(!ldd_file) {
        cout << format("Unable to run {}\n", argv[1]);
        return 1;
    }

    char line[256];

    while(fgets(line, 256, ldd_file)) {
        int paren_loc = -1;
        int split_loc = -1;
        int start_loc = -1;

        for(char *c = line; *c; c++) {
            if(start_loc < 0 && *c != ' ' && *c != '\t')
                start_loc = c - line;
            if(*c == '=')
                split_loc = c - line;
            if(*c == '(')
                paren_loc = c - line;
        }

        if(start_loc < 0 || split_loc < 0 && line[start_loc] != '/')
            continue;

        if(paren_loc >= 0)
            line[paren_loc-1] = 0;

        if(split_loc < 0)
            copy(line + start_loc, argv[2]);
        else
            copy(line + split_loc + 3, argv[2]);
    }

    if(pclose(ldd_file)) {
        cout << format("Non-zero exit running ldd\n");
        return 1;
    }
}
