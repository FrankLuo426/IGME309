#pragma once
#include <iostream>

using namespace std;

template <class T>
class Queue
{
	private T* queue;
	private int size;


	public Queue();
	// Rule of Three
	public Queue(const Queue& _otherQueue);
	public Queue<T>& operator=(const Queue<T>& other);
	public ~Queue();

	//Push 每 Add information to the queue. If the queue ran out of space to contain data, it should
	//allocate more space to contain the new information.You may sort here or make an additional
	//helper method that does it for you.Any sorting algorithm is fine for this assignment.
	public void Push(T _item);

	//Pop 每 Removes information of the queue from the front, to make things easier you do not need to
	//reallocate the queue contents into a smaller container when you remove information from it; you
	//can just shift the entries one index down.You can keep the same size for your pointer arrayand
	//have an index to know where the last element is stored.You do not need to return any
	//information from the queue just eliminate the entry.
	public T Pop();
	
	//Print 每 A method that writes in console the contents of the queue (provided the operation is
	//defined for the data type, all basic data types as integers, doubles, chars, floats, shorts, etc are
	//very well defined.When your queue use a class object, the class needs to have a definition on
	//what happens when you call an std::cout via a friend function, you can assume any class object I
	//use for testing the homework will contain this definition
	public void Print();
	
	//A1 - Templated Priority Queue - IGME.309.01 - Data Struc & Alg Game & Sim II
	public int GetSize();

	//IsEmpty 每 A method that returns a Boolean that informs whether or not a queue contains no
	//entries.
	public bool IsEmpty();

	//Sort the Queue
	public void Sort(T* _queue, int _size);
};

//Default constructor
template<class T>
inline Queue<T>::Queue() {
	queue = new T[1];
	size = 0;
	queue[0] = 0;
}

//Copy constructor
template<class T>
inline Queue<T>::Queue(const Queue& _otherQueue) {
	size = _otherQueue.size;
	queue = new T[size];
	for (int i = 0; i < size; i++) {
		queue[i] = _otherQueue.queue[i];
	}
}

//copy assignment constructor
template<class T>
inline Queue<T>& Queue<T>::operator=(const Queue<T>& other) {
	if (this == &other) {
		return *this;
	}

	if (queue != nullptr) {
		delete queue;
		queue = nullptr;
		size = 0;
	}

	size = other.size;
	queue = new T[size];
	for (int i = 0; i < size; i++) {
		queue[i] = other[i];
	}

	return *this;
}

//Destructor
template<class T>
inline Queue<T>::~Queue() {
	delete queue;
	queue = nullptr;
}

//Adds an item to the queue
template<class T>
inline void Queue<T>::Push(T _item) {
	if (queue[size] == 0) {
		T* oldqueue = queue;
		queue = new T[(size + 1) * 2];	//creates new [] double the original size
		queue[((size + 1) * 2) - 1] = 0;
		for (int i = 0; i < size; i++) {
			queue[i] = oldqueue[i];
		}
		delete oldqueue;
	}
	queue[size] = _item;
	size++;
	Sort(queue, size);
}

//Removes item from the top of the queue
template<class T>
inline T Queue<T>::Pop() {
	if (size > 0) {
		T item = queue[0];
		for (int i = 0; i < size - 1; i++) {
			queue[i] = queue[i + 1];
		}
		queue[size - 1] = 0;
		size--;
		return item;
	}
	return 0;
}

//Prints all items on queue
template<class T>
inline void Queue<T>::Print() {
	cout << "\n--Start of queue--\n";
	for (int i = size - 1; i >= 0; i--) {
		cout << queue[size - i - 1] << endl;
	}
	cout << "--End of queue--\n";
}

//returns the number of elements in the queue
template<class T>
inline int Queue<T>::GetSize() {
	return size;
}

//Returns true if the queue is empty
template<class T>
inline bool Queue<T>::IsEmpty() {
	if (size == 0) {
		return true;
	}
	return false;
}

//Recursively sorts array pushing larger elements to the back
template<class T>
inline void Queue<T>::Sort(T* _queue, int _size)
{
	// Base case
	if (_size == 1)
		return;

	for (int i = 0; i < _size - 1; i++) {
		if (_queue[i] > _queue[i + 1]) {
			swap(_queue[i], _queue[i + 1]);
		}
	}
	// Largest element gets pushed to the back
	// recur for remaining array
	Sort(_queue, _size - 1);
}