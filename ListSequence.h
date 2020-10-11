#ifndef LISTSEQUENCE_H_
#define LISTSEQUENCE_H_

#include <iostream>
#include <utility>
#include "List.h"
#include "Sequence.h"

template <typename T>
class ListSequence : public Sequence<T>
{
public:
	ListSequence() :  sizeOfList{ 0 }, readyList{ MyTwoLinkedList<T>() } {};
	ListSequence(const ListSequence<T>& listToCopy) :  sizeOfList{ listToCopy.sizeOfList }, readyList{ MyTwoLinkedList<T>(listToCopy.readyList) } {};
	ListSequence(ListSequence<T>&& listToMove) : sizeOfList{ listToMove.sizeOfList }, readyList{ MyTwoLinkedList<T>(std::move(listToMove.readyList)) } 
												{listToMove.sizeOfList = 0; };
	ListSequence(size_t size) : sizeOfList{ size }, readyList{ MyTwoLinkedList<T>(size) } {};

	virtual ~ListSequence() = default;

	void pushFront(T) override;
	void pushBack(T) override;

	T& getFront() override;
	const T& getFront() const override;

	T& getBack() override;
	const T& getBack() const override;

	T popBack() override;
	T popFront() override;

	bool isEmpty() const override;
	size_t len() const override;

	ListSequence<T>& operator=(const ListSequence<T>& listToCopy) {
		if (&listToCopy == this) { return *this; }
		sizeOfList = listToCopy.sizeOfList;
		readyList = listToCopy.readyList;
		return *this;
	}

	ListSequence<T>& operator=(ListSequence<T>&& listToMove) {
		if (this == &listToMove) { return *this; }
		readyList = std::move(listToMove.readyList);
		sizeOfList = listToMove.sizeOfList;
		return *this;
	}

	const T& operator[](size_t) const override;
	T& operator[](size_t) override;

	int find(T) override;
	void insert(size_t, T) override;

	void del(T) override;
	void remove(size_t) override;
	void terminate() override;

	T* getSubsequenceByIndexes(size_t, size_t) override;

	template <typename T>
	friend std::ostream& operator<<(std::ostream& os, const ListSequence<T>& listToOutput);
private:
	MyTwoLinkedList<T> readyList;
	size_t sizeOfList;
};

template <typename T>
void ListSequence<T>::pushBack(T itemToPush) {
	readyList.pushBack(itemToPush);
	++sizeOfList;
}

template <typename T>
void ListSequence<T>::pushFront(T itemToPush) {
	readyList.pushFront(itemToPush);
	++sizeOfList;
}

template <typename T>
T ListSequence<T>::popBack() {
	--sizeOfList;
	return readyList.popBack();

}

template <typename T>
T ListSequence<T>::popFront() {
	--sizeOfList;
	return readyList.popFront();
}

template <typename T>
T& ListSequence<T>::getBack() {
	if (sizeOfList < 1) {
		throw std::runtime_error("The list is already empty!");
	}
	return readyList.getBack();
}

template <typename T>
const T& ListSequence<T>::getBack() const {
	if (sizeOfList < 1) {
		throw std::runtime_error("The list is already empty!");
	}
	return readyList.getBack();
}

template <typename T>
T& ListSequence<T>::getFront() {
	if (sizeOfList < 1) {
		throw std::runtime_error("The list is already empty!");
	}
	return readyList.getFront();
}

template <typename T>
const T& ListSequence<T>::getFront() const {
	if (sizeOfList < 1) {
		throw std::runtime_error("The list is already empty!");
	}
	return readyList.getFront();
}

template <typename T>
T& ListSequence<T>::operator[](size_t index) {
	if (index < 0 || index >= sizeOfList) {
		throw std::out_of_range("The index was out of range!");
	}
	return readyList[index];
}

template <typename T>
const T& ListSequence<T>::operator[](size_t index) const {
	if (index < 0 || index >= sizeOfList) {
		throw std::out_of_range("The index was out of range!");
	}
	return readyList[index];
}

template <typename T>
bool ListSequence<T>::isEmpty() const {
	return readyList.isEmpty();
}

template <typename T>
size_t ListSequence<T>::len() const {
	return readyList.len();
}

template <typename T>
int ListSequence<T>::find(T itemToFind) {
	return readyList.find(itemToFind);
}

template <typename T>
void ListSequence<T>::insert(size_t index, T itemToInsert) {
	if (index < 0 || index > sizeOfList) { throw std::out_of_range("The index was out of range!"); }
	readyList.insert(index, itemToInsert);
	++sizeOfList;
}

template <typename T>
void ListSequence<T>::del(T itemToDel) {
	readyList.del(itemToDel);
	--sizeOfList;
}

template <typename T>
void ListSequence<T>::remove(size_t index) {
	if (index < 0 || index >= sizeOfList) { throw std::out_of_range("The index was out of range!"); }
	readyList.remove(index);
	--sizeOfList;
}

template <typename T>
void ListSequence<T>::terminate() {
	readyList.terminate();
	sizeOfList = 0;
}

template <typename T>
T* ListSequence<T>::getSubsequenceByIndexes(size_t begin, size_t end) {
	if (end >= begin && end < sizeOfList && begin >= 0) {
		return readyList.getSubsequenceByIndexes(begin, end);
	}
	else {
		throw std::out_of_range("The indexes were out of range!");
	}
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const ListSequence<T>& listToOutput) {
	os << listToOutput.readyList;
	return os;
}
#endif