#ifndef SORTINGS_H_
#define SORTINGS_H_

#include "utils.h"

template <typename Sequence, typename Comparison>
void bubbleSort(Sequence& seq, Comparison fcn) {
	if (seq.len() < 1) { return; }
	for (size_t i = seq.len() - 1; i > 0; --i) {
		for (size_t j = 0; j < i; ++j) {
			if (fcn(seq[j + 1], seq[j])) {
				auto temp = seq[j + 1];
				seq[j + 1] = seq[j];
				seq[j] = temp;
			}
		}
	}
}

template <typename Sequence, typename Comparison>
void shakerSort(Sequence& seq, Comparison fcn) {
	if (seq.len() < 1) { return; }
	int left = 0, right = seq.len() - 1;
	bool flag = true;
	while (flag) {
		flag = false;
		for (int j = left; j < right; ++j) {
			if (fcn(seq[j + 1], seq[j])) {
				auto temp = seq[j + 1];
				seq[j + 1] = seq[j];
				seq[j] = temp;
				flag = true;
			}
		}
		--right;
		for (int j = right; j > left; --j) {
			if (fcn(seq[j - 1], seq[j])) {
				auto temp = seq[j - 1];
				seq[j - 1] = seq[j];
				seq[j] = temp;
				flag = true;
			}
		}
		++left;
	}
}

template <typename Sequence, typename Comparison>
void selectionSort(Sequence& seq, Comparison fcn) {
	if (seq.len() < 1) { return; }
	for (size_t i = 0; i < seq.len() - 1; ++i) {
		size_t min = i;
		for (size_t j = i + 1; j < seq.len(); ++j) {
			if (fcn(seq[j], seq[min])) {
				min = j;
			}
		}
		auto temp = seq[i];
		seq[i] = seq[min];
		seq[min] = temp;
	}
}

template <typename Sequence, typename Comparison>
void insertionSort(Sequence& seq, Comparison fcn) {
	for (size_t i = 1; i < seq.len(); ++i) {
		auto temp = seq[i];
		size_t j = i;
		while (j > 0 && fcn(temp, seq[j - 1])) {
			seq[j] = seq[j - 1];
			--j;
		}
		seq[j] = temp;
	}
}

template <typename Sequence, typename Comparison>
void gnomeSort(Sequence& seq, Comparison fcn) {
	size_t i = 0;
	while (i < seq.len()) {
		if (i == 0 || !fcn(seq[i], seq[i - 1])) { ++i; }
		else {
			auto temp = seq[i - 1];
			seq[i - 1] = seq[i];
			seq[i] = temp;
			--i;
		}
	}
}

template <typename Sequence, typename Comparison>
void mergeSort(Sequence& seq, Comparison fcn) {
	if (seq.len() < 1) { return; }
	Sequence workSpace(seq.len());
	recMergeSort(seq, workSpace, 0, seq.len() - 1, fcn);
}


//the interval sequence formula is h = h * 3 + 1
template <typename Sequence, typename Comparison>
void ShellSort(Sequence& seq, Comparison fcn) {
	size_t h = 1;
	while (h <= seq.len() / 3) {
		h = h * 3 + 1;
	}
	while (h > 0) {
		for (size_t out = h; out < seq.len(); ++out) {
			auto temp = seq[out];
			size_t in = out;
			while (in > h - 1 && fcn(temp, seq[in - h])) {
				seq[in] = seq[in - h];
				in -= h;
			}
			seq[in] = temp;
		}
		h = (h - 1) / 3;
	}
}

template <typename Sequence, typename Comparison>
void quickSort(Sequence& seq, int first, int last, Comparison fcn) {
	if (seq.len() < 1) { return; }
	int f = first, l = last;
	auto mid = seq[(f + l) / 2]; //вычисление опорного элемента
	do {
		while (fcn(seq[f], mid)) f++;
		while (seq[l] != mid && !fcn(seq[l], mid)) l--;
		if (f <= l) { //перестановка элементов
			auto count = seq[f];
			seq[f] = seq[l];
			seq[l] = count;
			f++;
			l--;
		}
	} while (f < l);
	if (first < l) quickSort(seq, first, l, fcn);
	if (f < last) quickSort(seq, f, last, fcn);
}

#endif // !SORTINGS_H_
