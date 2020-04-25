#ifndef DATA_STR_H
#define DATA_STR_H

#include <type_traits>
#include <stdexcept>

using namespace std;

template<typename T>
struct Node {
    T data;
    struct Node<T>* next;
};

template<typename T>
class BaseQueue
{
protected:
	Node<T>* _front;
	size_t _size;

public:
	BaseQueue();
	virtual ~BaseQueue();

	bool empty() const; // queue empty?
	size_t size() const; // queue size
	virtual void push(T val) = 0; // insert new element at the end 
	virtual void pop() = 0; // remove next element
};

template<typename T>
class Queue: BaseQueue<T>
{
	using BaseQueue<T>::_size;
	using BaseQueue<T>::_front;

    Node<T>* _rear;

public:
	using BaseQueue<T>::empty;
	using BaseQueue<T>::size;

	Queue();

    void push(T val); // insert new element at the end 
    void pop(); // remove next element
    T& front(); // ref to next element
    T& back(); // ref to last element
};

template<typename T>
class PriorityQueue: BaseQueue<T>
{
	using BaseQueue<T>::_size;
	using BaseQueue<T>::_front;

public:
	using BaseQueue<T>::empty;
	using BaseQueue<T>::size;

    void push(T val); // insert new element at the end 
    void pop(); // remove next element
    T& top(); // ref to the top element
};

/*****************************************************/

template<typename T>
BaseQueue<T>::BaseQueue()
{
	_front = NULL;
	_size = 0;
}

template<typename T>
BaseQueue<T>::~BaseQueue()
{
	Node<T>* current = _front;
	Node<T>* next;

	while (current != NULL) {
		next = current->next;
		delete current;
		current = next;
	}
}

template<typename T>
bool BaseQueue<T>::empty() const
{
	return (size() == 0);
}

template<typename T>
size_t BaseQueue<T>::size() const
{
	return _size;
}

/*****************************************************/

template<typename T>
Queue<T>::Queue()
{
	_rear = NULL;
}

template<typename T>
T& Queue<T>::front()
{
	if (empty())
	{
		throw runtime_error("Queue is empty");
	}
	return _front->data;
}

template<typename T>
T& Queue<T>::back()
{
	if (empty())
	{
		throw runtime_error("Queue is empty");
	}
	return _rear->data;
}

template<typename T>
void Queue<T>::push(T val)
{
	if (_rear == NULL) {
		_rear = new Node<T>;
		_rear->next = NULL;
		_rear->data = val;
		_front = _rear;
	}
	else {
		Node<T>* temp = new Node<T>;
		_rear->next = temp;
		temp->data = val;
		temp->next = NULL;
		_rear = temp;
	}
	++_size;
}

template<typename T>
void Queue<T>::pop()
{
	if (empty())
	{
		throw runtime_error("Queue is empty");
	}

	if (_front->next != NULL) {
		Node<T>* temp = _front->next;
		delete _front;
		_front = temp;
	}
	else {
		delete _front;
		_front = NULL;
		_rear = NULL;
	}

	--_size;
}

/*****************************************************/

template<typename T>
T& PriorityQueue<T>::top()
{
	if (empty())
	{
		throw runtime_error("PriorityQueue is empty");
	}
	return _front->data;
}

template<typename T>
void PriorityQueue<T>::push(T val)
{
	Node<T>* temp = new Node<T>;
	temp->data = val;

	if (_front == NULL || val > _front->data) {
		temp->next = _front;
		_front = temp;
	}
	else {
		Node<T>* prev = _front;
		while (prev->next != NULL && prev->next->data >= val)
			prev = prev->next;
		temp->next = prev->next;
		prev->next = temp;
	}

	++_size;
}

template<typename T>
void PriorityQueue<T>::pop()
{
	if (empty())
	{
		throw runtime_error("Queue is empty");
	}

	if (_front->next != NULL) {
		Node<T>* temp = _front->next;
		delete _front;
		_front = temp;
	}
	else {
		delete _front;
		_front = NULL;
	}

	--_size;
}

#endif 
