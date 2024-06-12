#include <utility>
#include "functions.h"

using namespace std;
int unexpectedOperations() {
    //swap
    int a{ 4 }, b{ 5 };
    swap(a, b);

    vector<int> evens{ 2, 4, 6, 8, 10 };
    vector<int> odds{ 1, 3, 5, 7, 9 };

    auto v1 = evens;
    swap(v1[0], v1[1]);

    //This does the same but with iterators
    iter_swap(begin(v1), begin(v1) + 1);

    auto v2 = odds;
    //This one swaps elements between two collections
    swap(v1[0], v2[0]);
    //This one swaps particular elements between two collections.
    iter_swap(begin(v1), find(begin(v2), end(v2), 5));

    v1 = evens;
    v2 = odds;

    /* first point v1, second point v2, the fin in the middle indicates that
     * all numbers before the position of the number 6 will be swapped.
     */
    swap_ranges(begin(v1), find(begin(v1), end(v1), 6), begin(v2));

    return 0;
}