#ifndef ARRAY_H_
#define ARRAY_H_

#include <stdexcept>
#include <iostream>
#include <initializer_list>

template <typename T>
class MyArray {
private:
	size_t size;
	size_t capasity;
	T* arr;

public:
	MyArray() : size{ 0 }, capasity{ 0 }, arr{ nullptr } {};

	explicit MyArray(size_t sz) : size{ sz }, capasity{ sz }, arr{ new T[sz] } {
		for (size_t i = 0; i < sz; ++i) {
			arr[i] = T();
		}
	};

	explicit MyArray(size_t sz, T itemToFill) : size{ sz }, capasity{ sz }, arr{ new T[sz] } {
		for (size_t i = 0; i < size; ++i) {
			arr[i] = itemToFill;
		}
	}

	MyArray(const MyArray<T>& arrToCopy) : size{ arrToCopy.size }, capasity{ arrToCopy.capasity }, arr{ new T[capasity] }{
		if (size % 2) {
			for (size_t i = 0; i < size / 2; ++i) {
				arr[i] = arrToCopy.arr[i];
				arr[size - i - 1] = arrToCopy.arr[size - i - 1];
			}
			arr[size / 2] = arrToCopy.arr[size / 2];
		}
		else {
			for (size_t i = 0; i < size / 2; ++i) {
				arr[i] = arrToCopy.arr[i];
				arr[size - i - 1] = arrToCopy.arr[size - i - 1];
			}
		}
	}

	MyArray(MyArray&& arrToMove) : size{ arrToMove.size }, capasity{ arrToMove.capasity }, arr{ arrToMove.arr }{
		arrToMove.arr = nullptr;
		arrToMove.size = 0;
	}

	~MyArray() { delete[] arr; }

	size_t len() const { return size; }

	bool isEmpty() const { return !size; }

	T& getFront() {
		if (size < 1) {
			throw std::runtime_error("The array is already empty!");
		}
		return arr[0];
	}

	const T& getFront() const {
		if (size < 1) {
			throw std::runtime_error("The array is already empty!");
		}
		return arr[0];
	}

	T& getBack() {
		if (size < 1) {
			throw std::runtime_error("The array is already empty!");
		}
		return arr[size - 1];
	}

	const T& getBack() const {
		if (size < 1) {
			throw std::runtime_error("The array is already empty!");
		}
		return arr[size - 1];
	}

	void pushBack(T itemToInsert);
	void pushFront(T itemToInsert);

	T popBack();
	T popFront();

	//returns the first index of itemToFind (if there is no such element, returns -1)
	//different searches: lenear or binary
	int find(T itemToFind) const;

	T getMax() const;

	T* getSubsequenceByIndexes(size_t begin, size_t end);

	const T& operator[](size_t index) const;
	T& operator[](size_t index);

	MyArray<T>& operator=(const MyArray<T>& arrToCopy);
	MyArray<T>& operator=(MyArray<T>&& arrToMove);

	void insert(size_t index, T itemToInsert);

	void remove(size_t indexForRemoving);

	//delete the first itemToDel
	void del(T itemToDel);

	//delete all itemsToDel
	void delAll(T itemsToDel);

	void terminate();

	//delete all dubs of all elements
	void noDubs();

	//delete all dubs of certain element
	void noDubs(T itemNoDubs);

	//merge
	void merge(const MyArray<T>& lhs, const MyArray<T>& rhs);

	template <typename T>
	friend std::ostream& operator<<(std::ostream& os, const MyArray<T>& arrToOutput);
	template <typename T>
	friend bool operator<(const MyArray<T>& lhs, const MyArray<T>& rhs);
	template <typename T>
	friend bool operator>(const MyArray<T>& lhs, const MyArray<T>& rhs);
	template <typename T>
	friend bool operator==(const MyArray<T>& lhs, const MyArray<T>& rhs);
	template <typename T>
	friend bool operator!=(const MyArray<T>& lhs, const MyArray<T>& rhs);
};


template <typename T>
void MyArray<T>::pushBack(T itemToInsert) {
	if (size >= capasity) {
		capasity = (capasity) ? capasity * 2 : 1;
		T* newArr = new T[capasity];
		for (size_t i = 0; i < size; ++i) {
			newArr[i] = arr[i];
		}
		newArr[size++] = itemToInsert;
		T* arrToDel = arr;
		arr = newArr;
		delete[] arrToDel;
	}
	else {
		arr[size++] = itemToInsert;
	}
}

template<typename T>
void MyArray<T>::pushFront(T itemToInsert){
	if (size >= capasity) {
		capasity = (capasity) ? capasity * 2 : 1;
		T* newArr = new T[capasity];
		newArr[0] = itemToInsert;
		for (size_t i = 0; i < size; ++i) {
			newArr[i + 1] = arr[i];
		}
		T* arrToDel = arr;
		arr = newArr;
		delete[] arrToDel;
	}
	else {
		for (size_t i = size; i > 0; --i) {
			arr[i] = arr[i - 1];
		}
		arr[0] = itemToInsert;
	}
	++size;
}

//returns the first index of itemToFind (if there is no such element, returns -1)
template <typename T>
int MyArray<T>::find(T itemToFind) const {
	size_t i = 0;
	for (i; i < size; ++i) {
		if (arr[i] == itemToFind) { break; }
	}
	if (i == size) { return -1; }
	else { return i; }
}

template <typename T>
const T& MyArray<T>::operator[](size_t index) const {
	if (index < 0 || index >= size) {
		throw std::out_of_range("index was out of range!");
	}
	else {
		return arr[index];
	}
}

template <typename T>
T& MyArray<T>::operator[](size_t index) {
	if (index < 0 || index >= size) {
		throw std::out_of_range("index was out of range!");
	}
	else {
		return arr[index];
	}
}

template <typename T>
MyArray<T>& MyArray<T>::operator=(const MyArray<T>& arrToCopy) {
	if (this == &arrToCopy) {
		return *this;
	}
	size = arrToCopy.size;
	capasity = arrToCopy.capasity;
	delete[] arr;
	arr = new T[capasity];
	for (size_t i = 0; i < size; ++i) {
		arr[i] = arrToCopy.arr[i];
	}
	return *this;
}

template <typename T>
MyArray<T>& MyArray<T>::operator=(MyArray<T>&& arrToMove) {
	if (this == &arrToMove) {
		return *this;
	}
	size = arrToMove.size;
	capasity = arrToMove.capasity;
	delete[] arr;
	arr = arrToMove.arr;
	arrToMove.arr = nullptr;
	arrToMove.size = 0;
	return *this;
}

template <typename T>
void MyArray<T>::insert(size_t index, T itemToInsert) {
	if (size >= capasity) {
		capasity = (capasity) ? capasity * 2 : 1;
		T* newArr = new T[capasity];
		size_t i = 0;
		for (i; i < index; ++i) {
			newArr[i] = arr[i];
		}
		newArr[i] = itemToInsert;
		for (i; i < size; ++i) {
			newArr[i + 1] = arr[i];
		}
		++size;
		T* arrToDel = arr;
		arr = newArr;
		delete[] arrToDel;
	}
	else {
		int i = size;
		for (i; i > index; --i) {
			arr[i] = arr[i - 1];
		}
		arr[i] = itemToInsert;
	}
	++size;
}

template <typename T>
T MyArray<T>::popBack() {
	if (!(size && capasity)) {
		throw std::runtime_error("array is already empty!");
	}
	T* newArr = new T[capasity];
	for (size_t i = 0; i < size - 1; ++i) {
		newArr[i] = arr[i];
	}
	T temp = arr[size - 1];
	--size;
	T* arrToDel = arr;
	arr = newArr;
	delete[] arrToDel;
	return temp;
}

template<typename T>
T MyArray<T>::popFront() {
	if (!(size && capasity)) {
		throw std::runtime_error("array is already empty!");
	}
	T* newArr = new T[capasity];
	for (size_t i = 1; i < size; ++i) {
		newArr[i - 1] = arr[i];
	}
	T temp = arr[0];
	--size;
	T* arrToDel = arr;
	arr = newArr;
	delete[] arrToDel;
	return temp;
}

template <typename T>
void MyArray<T>::remove(size_t indexForRemoving) {
	if (indexForRemoving < 0 || indexForRemoving >= size) {
		throw std::out_of_range("index was out of range!");
	}
	T* newArr = new T[capasity];
	size_t i = 0;
	for (i; i < indexForRemoving; ++i) {
		newArr[i] = arr[i];
	}
	for (i; i < size - 1; ++i) {
		newArr[i] = arr[i + 1];
	}
	--size;
	T* arrToDell = arr;
	arr = newArr;
	delete[] arrToDell;
}

template <typename T>
void MyArray<T>::del(T itemToDel) {
	int index = find(itemToDel);
	if (index >= 0) {
		remove(index);
	}
}

template <typename T>
void MyArray<T>::delAll(T itemsToDel) {
	T* newArr = new T[capasity];
	size_t j = 0;
	for (size_t i = 0; i < size; ++i) {
		if (arr[i] != itemsToDel) {
			newArr[j++] = arr[i];
		}
	}
	size = j;
	T* arrToDel = arr;
	arr = newArr;
	delete[] arrToDel;
}

template<typename T>
void MyArray<T>::terminate() {
	delete[] arr;
	size = capasity = 0;
	arr = nullptr;
}

template <typename T>
T MyArray<T>::getMax() const {
	if (!isEmpty()) {
		T max = arr[0];
		for (size_t i = 1; i < size; ++i) {
			if (max < arr[i]) {
				max = arr[i];
			}
		}
		return max;
	}
	else {
		throw std::runtime_error("Array is empty!");
	}
}

template <typename T>
T* MyArray<T>::getSubsequenceByIndexes(size_t begin, size_t end) {
	if (end >= begin && end < size && begin >= 0) {
		T* temp = new T[end - begin + 1];
		size_t newIndex = 0;
		for (size_t i = begin; i <= end; ++i) {
			temp[newIndex] = arr[i];
			++newIndex;
		}
		return temp;
	}
	else {
		throw std::out_of_range("The indexes were out of range!");
	}
}

template <typename T>
void MyArray<T>::noDubs() {
	if (!isEmpty()) {
		T* newArr = new T[capasity];
		newArr[0] = arr[0];
		size_t indexOfNewArr = 1;
		for (size_t i = 1; i < size; ++i) {
			size_t j = 0;
			for (j; j < indexOfNewArr; ++j) {
				if (arr[i] == newArr[j]) { break; }
			}
			if (j == indexOfNewArr) { newArr[indexOfNewArr++] = arr[i]; }
		}
		size = indexOfNewArr;
		T* arrToDell = arr;
		arr = newArr;
		delete[] arrToDell;
	}
}

template <typename T>
void MyArray<T>::noDubs(T itemNoDubs) {
	if (!isEmpty()) {
		int left = find(itemNoDubs);
		if (left < 0) {
			return;
		}
		T* newArr = new T[capasity];
		size_t j = 0;
		for (size_t i = 0; i <= left; ++i) {
			newArr[j++] = arr[i];
		}
		for (size_t i = ++left; i < size; ++i) {
			if (arr[i] != itemNoDubs) {
				newArr[j++] = arr[i];
			}
		}
		size = j;
		T* arrToDell = arr;
		arr = newArr;
		delete[] arrToDell;
	}
}

template <typename T>
void MyArray<T>::merge(const MyArray<T>& arrA, const MyArray<T>& arrB) {
	if (arr) {
		delete[] arr;
	}
	arr = new T[arrA.capasity + arrB.capasity];
	size = arrA.size + arrB.size;
	size_t aDex = 0, bDex = 0, cDex = 0;
	while (aDex < arrA.size && bDex < arrB.size) {
		if (arrA[aDex] < arrB[bDex]) {
			arr[cDex++] = arrA[aDex++];
		}
		else {
			arr[cDex++] = arrB[bDex++];
		}
	}
	while (aDex < arrA.size) {
		arr[cDex++] = arrA[aDex++];
	}
	while (bDex < arrB.size) {
		arr[cDex++] = arrB[bDex++];
	}
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const MyArray<T>& arrToOutput) {
	for (size_t i = 0; i < arrToOutput.size; ++i) {
		os << arrToOutput.arr[i] << ' ';
	}
	return os;
}

template <typename T>
bool operator<(const MyArray<T>& lhs, const MyArray<T>& rhs) {
	if (lhs.size < rhs.size) { return true; }
	else if (lhs.size > rhs.size) { return false; }
	else {
		for (size_t i = 0; i < lhs.size; ++i) {
			if (!(lhs.arr[i] < rhs.arr[i])) {
				return false;
			}
		}
		return true;
	}
}

template <typename T>
bool operator>(const MyArray<T>& lhs, const MyArray<T>& rhs) {
	return rhs < lhs;
}

template <typename T>
bool operator==(const MyArray<T>& lhs, const MyArray<T>& rhs) {
	return !(lhs < rhs || lhs > rhs);
}

template <typename T>
bool operator!=(const MyArray<T>& lhs, const MyArray<T>& rhs) {
	return !(lhs == rhs);
}

#endif