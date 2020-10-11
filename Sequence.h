#ifndef SEQUENCE_H_
#define SEQUENCE_H_

template <typename T>
class Sequence
{
public:
	Sequence<T>() = default;
	virtual ~Sequence() = default;
	virtual void pushFront(T) = 0;
	virtual void pushBack(T) = 0;
	virtual T& getFront() = 0;
	virtual const T& getFront() const = 0;
	virtual T& getBack() = 0;
	virtual const T& getBack() const = 0;
	virtual T popBack() = 0;
	virtual T popFront() = 0;
	virtual bool isEmpty() const = 0;
	virtual size_t len() const = 0;
	virtual const T& operator[](size_t) const = 0;
	virtual T& operator[](size_t) = 0;
	virtual int find(T) = 0;
	virtual void insert(size_t, T) = 0;
	virtual void del(T) = 0;
	virtual void remove(size_t) = 0;
	virtual void terminate() = 0;
	virtual T* getSubsequenceByIndexes(size_t, size_t) = 0;
};

#endif // !SEQUENCE_H_
