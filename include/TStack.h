#ifndef TSTACK_H
#define TSTACK_H
#include <iostream>
const int maxMemSize = 100; // максимальная длина стека

template<typename T>
class TStack {
protected:
	T* pMem; // массив элементов стека
	int MemSize; // размер стека
	int DataCount; // количество элементов стека
public:
	TStack(int size = maxMemSize); // конструктор с параметрами/по молчанию
	TStack(TStack const& st); // конструктор копирования
	~TStack(); // деструктор

	TStack& operator=(TStack const& st); // операция присваивания
	bool isEmpty() const; // проверка стека на пустоту
	bool isFull() const; // проверка стека на полноту
	void Put(const T& Val); // помещение нового элемента в стек
	virtual T Get(); // выталкивание элемента из стека
	T CheckLast(); // просмотр последнего элемента стека
};
//..............................................................................................//
template<typename T>
TStack<T>::TStack(int size) { // конструктор с параметрами(по умолчанию)
	if (size < 0 || size > maxMemSize)
		throw std::out_of_range("Было введено некорректное значение длины создаваемого стека");
	if (size == 0)
		size = maxMemSize;
	MemSize = size;
	DataCount = 0;
	pMem = new T[MemSize];
}
//...............................................................................................//
template<typename T>
TStack<T>::~TStack() { // деструктор
	if (pMem != NULL) {
		delete[] pMem;
		pMem = NULL;
	}
}
//...............................................................................................//
template<typename T>
TStack<T>::TStack(TStack const& st) { //конструктор копирования
	MemSize = st.MemSize;
	DataCount = st.DataCount;
	pMem = new T[MemSize];
	for (int i = 0; i < DataCount; ++i) {
		pMem[i] = st.pMem[i];
	}
}
//................................................................................................//
template<typename T>
TStack<T>& TStack<T>::operator=(TStack const& st) { // операция присваивания
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
//.................................................................................................//
template<typename T>
bool TStack<T>::isEmpty() const { return (DataCount == 0); } // проверка на пустоту
//.................................................................................................//
template<typename T>
bool TStack<T>::isFull() const { return (DataCount == MemSize); } // проверка на полноту
//.................................................................................................//
template<typename T>
void TStack<T>::Put(const T& Val) { // добавление элемента в стек
	if (isFull())
		throw std::out_of_range("Стек полон!");
	else {
		DataCount++;
		pMem[DataCount - 1] = Val;
	}
}
//.................................................................................................//
template<typename T>
T TStack<T>::Get() { // выталкивание элемента из стека
	if (isEmpty())
		throw std::out_of_range("Стек пуст!");
	else {
		T tmp = pMem[DataCount - 1];
		DataCount--;
		return(tmp);
	}
}
//..................................................................................................//
template<typename T>
T TStack<T>::CheckLast() { // просмотр последнего элемента стека
	if (isEmpty())
		throw std::out_of_range("Стек пуст!");
	return(pMem[DataCount - 1]);
}

#endif