#ifndef MERGESORT_H
#define MERGESORT_H

#include <list>
using namespace std;

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

    result.insert(result.end(), leftIterator, left.end());
    result.insert(result.end(), rightIterator, right.end());

    return result;
}

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
