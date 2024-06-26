#define _CRT_SECURE_NO_WARNINGS
#include "Resource_RAII.h"
#include <cstdlib>
using std::strtol;

ResourceRAII::ResourceRAII(char const* const filepath) {
    f = fopen(filepath, "r");
    if (f) {
        read = fgets(line, maxlinelength, f);
        char* end;
        arraylength = strtol(line, &end, 10);
        numbers = new int[arraylength];
    }
    /* Successfuly constructing the object means that you've acquired your
     * resource for the destructor to clean up (Open the file and numbers).
     */
}

bool ResourceRAII::OK() {
    return ((f != nullptr) && (read != nullptr));
}

int ResourceRAII::ProcessLines() {
    bool keepgoing = true;
    char* end;
    // read all the lines
    while (keepgoing) {
        read = fgets(line, maxlinelength, f);
        if (read) {
            numbers[linesread] = strtol(line, &end, 10);
            linesread++;
        }
        else {
            keepgoing = false;
        }
    }
    return linesread;
}

int ResourceRAII::AccessNumber(int index) {
    if (numbers && index < arraylength) {
        return numbers[index];
    }
    return 0;
}

ResourceRAII::~ResourceRAII() {
    if (numbers) {
        delete[] numbers;
    }
    if (f) {
        fclose(f);
    }
}