#include "functions.h"
#include "Resource.h"
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

    /// Removing Elements

    // This removes all the values 3 from the vector.
    auto newend = remove(begin(source), end(source), 3);
    int s = source.size();

    //Then cleans up the collection.
    int logicalsize = newend - begin(source);
    source.erase(newend, end(source));

    source = v3;
    //This one does the same in one line.
    source.erase(remove(begin(source), end(source), 3), end(source));

    //Vector of objects
    vector<Resource> vr(2);
    vr[0].setValue(8);
    vr[1].setValue(9);

    auto newend2 = remove_if(begin(vr), end(vr),
        [](const Resource& r) {
            return r.getvalue() == 8;
        });
    vr.erase(newend2, end(vr));

    /* About creating and filling collections
     * It is necessary to specify the size of the collection.
     */

    //This one fills the whole vector with numbers 1.
    vector<int> v6(10);
    fill(begin(v6), end(v6), 1);
    //This one fills the first 6 places with numbers 2.
    fill_n(begin(v6), 6, 2);
    //iouta fills the whole vector with incrementing numbers by 1.
    iota(begin(v6), end(v6), 1);

    //This one fills the vector with decrementing numbers by 1.
    int index = 10;
    generate(begin(v6), end(v6), [&index]() {return --index; });
    source = v6;
    index = 1;
    //Fills first 7 position with the result of the lambda function.
    generate_n(begin(v6), 7, [&index]() {return (index *= 2); });

    //Replacing values

    //This one replaces all 2s with the number 7.
    replace(begin(v6), end(v6), 2, 7);

    //This one will replace any number less than 16 with the number 7.
    replace_if(begin(v6), end(v6), [](int elem) {return elem < 16; }, 7);

    return 0;
}
