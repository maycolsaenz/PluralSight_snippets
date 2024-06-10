#pragma once

#include <Windows.h>
#include <bitset>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <iomanip>
#include <functional>
#include <iostream>
using namespace std;

/*!
 * @class maskMatcher
 * \brief This class represents a comparator for two arguments: the APG address and
 *        a user-defined mask.
 *        The purpose of this class is to construct the EXPECTED boolean output resulting
 *        from comparing the aforementioned arguments. It will return TRUE if the APG
 *        address is equal to, greater than, or less than the user-defined mask. This is
 *        determined by the operator defined at the beginning of the mask. If no operator
 *        is present, the equal ("==") assessment is performed.
 */
class maskMatcher {
private:
    std::string userMask{};
    std::string token{};
    int operation{};
    std::vector<int>coefficient{};
    std::vector<std::string> extendedTokens{};
    std::bitset<32> mask_fixed;
    std::bitset<32> addr_fixed;

    /*!
     * \brief This function erases blanks in the user-defined mask.
     * \author Maycol Saenz.
     */
    void cleanBlanks();

    /*!
     * \brief This function identifies the operator at the beginning of the user-defined
     *        mask. It stores the numeric value 0 for "==", 1 for "<=", and 2 for ">=".
     *        If no operator is detected, the first option is set.
     * \author Maycol Saenz.
     * \return TRUE if an operator is present at the beginning of the mask, FALSE otherwise.
     */
    BOOL containsOperator();

    /*!
     * \brief This function erases the first two characters of the user-defined mask.
     * \author Maycol Saenz.
     */
    void eraseOperator();

    /*!
     * \brief This function identifies short-hand syntax within the user-defined mask by
     *        looking for an asterisk(*).
     * \author Maycol Saenz.
     * \return TRUE if an asterisk is found, FALSE otherwise.
     */
    BOOL containsAsterisk();

    /*!
     * \brief This function collects the token right after every asterisk in the
     *        user-defined mask.
     * \author Maycol Saenz.
     */
    void collectToken();
    /*!
     * \brief This function collects the multiplier before every asterisk in the
     *        user-defined mask.
     * \author Maycol Saenz.
     */
    void collectCoefficient();

    /*!
     * \brief This function expands the short-hand syntax notation (count*token) and
     *        stores the result of each occurrence in a vector.
     * \author Maycol Saenz.
     */
    void expandTokens();

    /*!
     * \brief This function expands the user-defined mask by replacing short-hand
     *        syntax notation with the corresponding expanded occurrance previously
     *        stored in a vector.
     * \author Maycol Saenz.
     */
    void replaceTokens();

    /*!
     * \brief This function flips the user-defined mask characters and casts them
     *        to a numeric value. This is stored in a member variable.
     * \param[in] input Address from APG.
     * \author Maycol Saenz.
     */
    void convertMaskToNumber(UINT64 input);

    /*!
     * \brief This function compares two numeric values depending on
     *        the operation indicated by the first two characters of the mask.
     * \author Maycol Saenz.
     * \return TRUE if the conditional comparison is met, FALSE otherwise.
     */
    BOOL conditionalComparison();

public:
    maskMatcher() = default;

    /*!
     * \brief This function implements the logic to compare the value of
     *        a user-defined mask against the APG address, acording to the operator
     *        at the beginning of the mask. If no operator is found, the equal(==)
     *        assessment is performed.
     * \param[in] mask User defined mask.
     * \param[in] input Address from APG.
     * \author Maycol Saenz.
     * \return TRUE if the conditional comparison is met, FALSE otherwise.
     */
    //BOOL matchesMask(LPCTSTR mask, UINT64 input);//Version in TOPO suite.
    BOOL matchesMask(std::string mask, UINT64 input);

    /*!
     * \brief This function sets all the output to true when the
     *        input value matches the configured mask.
     * \param[in] input Input address of Atopo.
     * \param[in] mask Value used to configure the mask macro.
     * \author Maycol Saenz.
     * \return Scrambled address expected.
     */
    //UINT64 AllBitsMaskResult(LPCTSTR mask, UINT64 input); // TOPO suite version
    UINT64 AllBitsMaskResult(std::string mask, UINT64 input);

    /* ******************For Testing ONLY************************
     * This method is just for testing.
     * There is no implementation in maskMastch.cpp
     */ 
    std::string getUserMask(std::string testMask) {
        matchesMask(testMask, 0);
        return userMask;
    }
};