#ifndef UTILS_H_
#define UTILS_H_

#include <utility>
#include "ArraySequence.h"
#include "ListSequence.h"

template <typename T>
ArraySequence<T> createRandomDigitalArrSequence(size_t sizeOfSeq) {
	ArraySequence<T> arr;
	for (size_t i = 0; i < sizeOfSeq; ++i) {
		arr.pushBack(rand() % 5000 - 2500);
	}
	return std::move(arr);
}

template <typename T>
ListSequence<T> createRandomDigitalListSequence(size_t sizeOfSeq) {
	ListSequence<T> lst;
	for (size_t i = 0; i < sizeOfSeq; ++i) {
		lst.pushBack(rand() % 5000 - 2500);
	}
	return std::move(lst);
}

template<typename Sequence, typename Comparison>
void mergeForSort(Sequence& seq, Sequence workSpace, size_t lowPtr, size_t highPtr, size_t upperBound, Comparison fcn) {
	size_t j = 0;
	size_t lowerBound = lowPtr;
	size_t mid = highPtr - 1;
	while (lowPtr <= mid && highPtr <= upperBound) {
		if (fcn(seq[lowPtr], seq[highPtr])) {
			workSpace[j++] = seq[lowPtr++];
		}
		else {
			workSpace[j++] = seq[highPtr++];
		}
	}
	while (lowPtr <= mid) {
		workSpace[j++] = seq[lowPtr++];
	}
	while (highPtr <= upperBound) {
		workSpace[j++] = seq[highPtr++];
	}
	for (j = 0; j < upperBound - lowerBound + 1; ++j) {
		seq[lowerBound + j] = workSpace[j];
	}
}

template <typename Sequence, typename Comparison>
void recMergeSort(Sequence& seq, Sequence workSpace, size_t lowerBound, size_t upperBound, Comparison fcn) {
	if (lowerBound == upperBound) {
		return;
	}
	else {
		size_t mid = (lowerBound + upperBound) / 2;
		recMergeSort(seq, workSpace, lowerBound, mid, fcn);
		recMergeSort(seq, workSpace, mid + 1, upperBound, fcn);
		mergeForSort(seq, workSpace, lowerBound, mid + 1, upperBound, fcn);
	}
}


#endif // !UTILS_H_
