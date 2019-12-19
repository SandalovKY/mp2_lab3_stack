#ifndef TSTACK_H
#define TSTACK_H
#include <iostream>
const int maxMemSize = 100;

template<typename T>
class TStack
{
protected:
	T* pMem;
	int MemSize;
	int DataCount;
public:
	TStack(int size = maxMemSize);
	TStack(TStack const& st);
	~TStack();

	TStack& operator=(TStack const& st);
	bool isEmpty() const;
	bool isFull() const;
	void Put(const T& Val);
	virtual T Get();
	T CheckLast();
};

template<typename T>
TStack<T>::TStack(int size) {
	if (size < 0 || size > maxMemSize)
		throw std::out_of_range("Было введено некорректное значение длины создаваемого стека");
	if (size == 0)
		size = maxMemSize;
	MemSize = size;
	DataCount = 0;
	pMem = new T[MemSize];
}

template<typename T>
TStack<T>::~TStack() {
	if (pMem != NULL) {
		delete[] pMem;
		pMem = NULL;
	}
}
template<typename T>
TStack<T>::TStack(TStack const& st) {
	MemSize = st.MemSize;
	DataCount = st.DataCount;
	pMem = new T[MemSize];
	for (int i = 0; i < DataCount; ++i) {
		pMem[i] = st.pMem[i];
	}
}

template<typename T>
TStack<T>& TStack<T>::operator=(TStack const& st) {
	if (this != &st) {
		if (MemSize != st.MemSize) {
			delete[] pMem;
			pMem = new T[st.MemSize];
		}
		MemSize = st.MemSize;
		DataCount = st.DataCount;
		for (int i = 0; i < DataCount; ++i) {
			pMem[i] = st.pMem[i];
		}
	}
	return *this;
}

template<typename T>
bool TStack<T>::isEmpty() const { return (DataCount == 0); }

template<typename T>
bool TStack<T>::isFull() const { return (DataCount == MemSize); }

template<typename T>
void TStack<T>::Put(const T& Val) {
	if (isFull())
		throw std::out_of_range("Стек полон!");
	else {
		DataCount++;
		pMem[DataCount - 1] = Val;
	}
}

template<typename T>
T TStack<T>::Get() {
	if (isEmpty())
		throw std::out_of_range("Стек пуст!");
	else {
		T tmp = pMem[DataCount - 1];
		DataCount--;
		return(tmp);
	}
}

template<typename T>
T TStack<T>::CheckLast() {
	return(pMem[DataCount - 1]);
}

#endif