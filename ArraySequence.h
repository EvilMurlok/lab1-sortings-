#ifndef ARRAYSEQUENCE_H_
#define ARRAYSEQUENCE_H_

#include <iostream>
#include <utility>
#include "Sequence.h"
#include "Array.h"

template <typename T>
class ArraySequence : public Sequence<T>
{
public:
	ArraySequence() : sizeOfArr{ 0 }, readyArr{ MyArray<T>() } {};
	explicit ArraySequence(size_t sz) : sizeOfArr{ sz }, readyArr{ MyArray<T>(sz) } {}
	explicit ArraySequence(size_t sz, T itemToFill) : sizeOfArr{ sz }, readyArr{ MyArray<T>(sz, itemToFill) } {};
	ArraySequence(const ArraySequence<T>& arrToCopy) : sizeOfArr{ arrToCopy.sizeOfArr }, readyArr{ MyArray<T>(arrToCopy.readyArr) } {};
	ArraySequence(ArraySequence<T>&& arrToMove) : sizeOfArr{ arrToMove.sizeOfArr }, readyArr{ MyArray<T>(std::move(arrToMove.readyArr)) } {};

	virtual ~ArraySequence() = default;
	
	void pushFront(T) override;
	void pushBack(T) override;

	T& getFront() override;
	const T& getFront() const override;

	T& getBack() override;
	const T& getBack() const override;

	T popBack() override;
	T popFront() override;

	bool isEmpty() const override;
	size_t len()const override;

	const T& operator[](size_t) const override;
	T& operator[](size_t) override;

	int find(T) override;
	void insert(size_t, T) override;

	void del(T) override;
	void remove(size_t) override;
	void terminate() override;

	T* getSubsequenceByIndexes(size_t, size_t) override;

	template <typename T>
	friend std::ostream& operator<<(std::ostream& os, const ArraySequence<T>& arrToOutput);
private:
	MyArray<T> readyArr;
	size_t sizeOfArr;
};


template <typename T>
void ArraySequence<T>::pushBack(T itemToPush) {
	readyArr.pushBack(itemToPush);
	++sizeOfArr;
}

template <typename T>
void ArraySequence<T>::pushFront(T itemToPush) {
	readyArr.pushFront(itemToPush);
	++sizeOfArr;
}

template <typename T>
T ArraySequence<T>::popBack() {
	--sizeOfArr;
	return readyArr.popBack();

}

template <typename T>
T ArraySequence<T>::popFront() {
	--sizeOfArr;
	return readyArr.popFront();
}

template <typename T>
T& ArraySequence<T>::getBack() {
	if (sizeOfArr < 1) {
		throw std::runtime_error("The list is already empty!");
	}
	return readyArr.getBack();
}

template <typename T>
const T& ArraySequence<T>::getBack() const {
	if (sizeOfArr < 1) {
		throw std::runtime_error("The list is already empty!");
	}
	return readyArr.getBack();
}

template <typename T>
T& ArraySequence<T>::getFront() {
	if (sizeOfArr < 1) {
		throw std::runtime_error("The list is already empty!");
	}
	return readyArr.getFront();
}

template <typename T>
const T& ArraySequence<T>::getFront() const {
	if (sizeOfArr < 1) {
		throw std::runtime_error("The list is already empty!");
	}
	return readyArr.getFront();
}

template <typename T>
T& ArraySequence<T>::operator[](size_t index) {
	if (index < 0 || index >= sizeOfArr) {
		throw std::out_of_range("The index was out of range!");
	}
	return readyArr[index];
}

template <typename T>
const T& ArraySequence<T>::operator[](size_t index) const {
	if (index < 0 || index >= sizeOfArr) {
		throw std::out_of_range("The index was out of range!");
	}
	return readyArr[index];
}

template <typename T>
bool ArraySequence<T>::isEmpty() const {
	return readyArr.isEmpty();
}

template <typename T>
size_t ArraySequence<T>::len() const {
	return readyArr.len();
}

template <typename T>
int ArraySequence<T>::find(T itemToFind) {
	return readyArr.find(itemToFind);
}

template <typename T>
void ArraySequence<T>::insert(size_t index, T itemToInsert) {
	if (index < 0 || index > sizeOfArr) { throw std::out_of_range("The index was out of range!"); }
	readyArr.insert(index, itemToInsert);
	++sizeOfArr;
}

template <typename T>
void ArraySequence<T>::del(T itemToDel) {
	readyArr.del(itemToDel);
	--sizeOfArr;
}

template <typename T>
void ArraySequence<T>::remove(size_t index) {
	if (index < 0 || index >= sizeOfArr) { throw std::out_of_range("The index was out of range!"); }
	readyArr.remove(index);
	--sizeOfArr;
}

template <typename T>
void ArraySequence<T>::terminate() {
	readyArr.terminate();
	sizeOfArr = 0;
}

template <typename T>
T* ArraySequence<T>::getSubsequenceByIndexes(size_t begin, size_t end) {
	if (end >= begin && end < sizeOfArr && begin >= 0) {
		return readyArr.getSubsequenceByIndexes(begin, end);
	}
	else {
		throw std::out_of_range("The indexes were out of range!");
	}
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const ArraySequence<T>& arrToOutput) {
	os << arrToOutput.readyArr;
	return os;
}
#endif