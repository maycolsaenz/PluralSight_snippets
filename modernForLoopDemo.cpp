#include "functions.h"

int modernForLoop() {

    // Legacy style for loop
    std::vector<int> nums{ 1, 2, 3, 4 };
    int total = 0;
    for (auto it = nums.begin(); it != nums.end(); it++) {
        total += *it;
    }

    // Modern style for loop
    for (auto num:nums) {
        total += num;
    }

    // This for loop works on a copy of the container.
    int oldNums[10] = { 2, 3, 4, 56, 3, 2 };
    for (int i = 0; i < 10; i++) {
        oldNums[i] /= 2;
    }
    // This for loop works on the original, by reference.
    for (auto& num: oldNums) { //auto const& does not modify it.
        num /= 2;
    }

    return 0;
}