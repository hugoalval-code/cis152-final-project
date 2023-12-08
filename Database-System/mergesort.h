#ifndef MERGESORT_H
#define MERGESORT_H

/***************************************************************
* Name : Final Project
* Author: Hugo Alvarez Valdivia
* Course: CIS 152 - Data Structures
* Version: 1.0
* OS: Mac OSX
* IDE: QT
* Copyright : This is my own original work
* based on specifications issued by our instructor
* Description : Database system to manage a business' customers,
*               products, as well as order tracking.
* Academic Honesty: I attest that this is my original work.
* I have not used unauthorized source code, either modified or
* unmodified. I have not given other fellow student(s) access
* to my program.
***************************************************************/

#include <list>
using namespace std;

/**
 * @brief This function merges two sorted lists into a single sorted list.
 *
 * This function takes two sorted lists (left and right) and merges them
 * into a single sorted list. It uses iterators to traverse the input lists
 * and compares elements to create the merged result.
 *
 * @tparam T The type of elements in the lists.
 * @param left The first sorted list.
 * @param right The second sorted list.
 * @return std::list<T> The merged sorted list.
 */
template<typename T>
list<T> merge(const list<T>& left, const list<T>& right) {
    list<T> result;
    auto leftIterator = left.begin();
    auto rightIterator = right.begin();

    while (leftIterator != left.end() && rightIterator != right.end()) {
        if (*leftIterator < *rightIterator) {
            result.push_back(*leftIterator);
            ++leftIterator;
        } else {
            result.push_back(*rightIterator);
            ++rightIterator;
        }
    }

    // Copy the remaining elements from the left and right lists (if any)
    result.insert(result.end(), leftIterator, left.end());
    result.insert(result.end(), rightIterator, right.end());

    return result;
}

/**
 * @brief This function performs merge sort on a std::list.
 *
 * This function implements the merge sort algorithm to sort a std::list
 * of elements. It recursively divides the list into halves, sorts each half,
 * and then merges the sorted halves. The base case is when the list size is 1
 * or less, as a list with 0 or 1 elements is considered already sorted.
 *
 * @tparam T The type of elements in the list.
 * @param lst The list to be sorted.
 * @return std::list<T> The sorted list.
 */
template <typename T>
list<T> mergeSort(list<T> lst) {
    if (lst.size() <= 1) {
        return lst; // Already sorted
    }

    // Split the list into two halves
    size_t middle = lst.size() / 2;
    auto middleIt = std::next(lst.begin(), middle);

    list<T> left(lst.begin(), middleIt);
    list<T> right(middleIt, lst.end());

    // Recursively sort the two halves
    left = mergeSort(left);
    right = mergeSort(right);

    // Merge the sorted halves
    return merge(left, right);
}

#endif // MERGESORT_H
