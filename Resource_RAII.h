#pragma once
#include <cstdio>
using std::FILE;

class ResourceRAII {
private:
    FILE* f = nullptr;
    int* numbers = nullptr;
    int arraylength = 0;
    int linesread = 0;
    char* read = nullptr;
    char line[255];
    size_t const maxlinelength = 255;

public:
    ResourceRAII(char const * const filepath);
    bool OK();
    char* GetLine() { return line; }
    int GetLineCount() { return linesread; }
    int ProcessLines();
    int AccessNumber(int index);
    ResourceRAII(ResourceRAII const& other) = delete;
    ResourceRAII& operator=(ResourceRAII const& other) = delete;
    ~ResourceRAII();
};

