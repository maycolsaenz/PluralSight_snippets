#include "functions.h"
#include <algorithm>
#include <numeric>
#include <vector>
#include <string>

using namespace std;

int generatingManipulating() {
    vector<int> source {3, 6, 1, 0, -2, 5};

    // Allocate the same space into another vector
    vector<int> v2(source.size());

    // Long version
    copy(begin(source), end(source), begin(v2));

    //Short version to copy the whole collection
    auto v3 = source;

    /*! Copying part of a collection
     */

    // Find number 1 position in the collection
    auto position = find(begin(source), end(source), 1);
    vector<int> v4(source.size());
    copy(begin(source), position, begin(v4));

    // If you want to copy the number at the position too
    copy(begin(source), position + 1, begin(v4));

    // Copying only even numbers
    vector<int> v5(source.size());
    copy_if(begin(source), end(source), begin(v5),
        [](int elem) {return elem % 2 == 0; });

    /* Copying the first 3 elements.
     * Note that the other elements are still there.
     */
    copy_n(begin(v5), 3, begin(v2));

    /* Copying within the same collection with no overlap.
     * If the third parameter is between the first two, you should use
     * copy_backward().
     */
    copy(begin(source), position + 1, position + 1);

    // Copying v3 backwards into source from the end.
    copy_backward(begin(v3), end(v3), end(source));

    /* The third parameter is between the first two.
     * It's not guaranteed to succeed.
     * copy(begin(source), end(source)-1, begin(source) + 1);
     * Instead use copy_backward.
     */
    copy_backward(begin(source), end(source) - 1, end(source));


    return 0;
}
