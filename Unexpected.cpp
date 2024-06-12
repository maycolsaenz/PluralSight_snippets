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

    // Rotate

    vector<int> tasks(6);
    iota(begin(tasks), end(tasks), 1);

    auto two = std::find(begin(tasks), end(tasks), 2);
    auto four = std::find(begin(tasks), end(tasks), 4);

    /* The firstand the third parameters are the first elementand the
     * last one(not inclusive). You should add +1 to include number four
     * to the colored are. The second parameter is the number at the beginning
     * of the range when the rotation is complete.
     * The distance between the first one and the middle is how many elements up you're
     * rotating. And the distance between last and middle is how many elements down
     * you're rotating.
     */
    rotate(two, four, four + 1);

    // Partition and rotate

    // In this example, all odd numbers are selected first and move before number 4.
    vector<int> numbers(8);
    iota(begin(numbers), end(numbers), 1);

    /* Selected is an iterator to the border of the selected numbers,
     * one position after the last one. I want number 2 to be on top after rotate.
     */
    auto selected = std::stable_partition(begin(numbers), end(numbers),
        [](int i) {
            return i % 2 != 0;
        });
    four = std::find(begin(numbers), end(numbers), 4);
    rotate(begin(numbers), selected, four);

    return 0;
}