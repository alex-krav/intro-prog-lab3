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
class Queue
{
    Node<T>* _front;
    Node<T>* _rear;
    size_t _size;

public:
    Queue();
    virtual ~Queue();

    bool empty() const; // queue empty?
    size_t size() const; // queue size
    void push(T val); // insert new element at the end 
    void pop(); // remove next element
    T& front(); // ref to next element
    T& back(); // ref to last element
};

template<typename T>
class PriorityQueue
{
    Node<T>* _front;
    size_t _size;

public:
    PriorityQueue();
    ~PriorityQueue();

    bool empty() const; // queue empty?
    size_t size() const; // queue size
    void push(T val); // insert new element at the end 
    void pop(); // remove next element
    T& top(); // ref to the top element
};

/*****************************************************/

template<typename T>
Queue<T>::Queue()
{
	_front = NULL;
	_rear = NULL;
	_size = 0;
}

template<typename T>
Queue<T>::~Queue()
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
bool Queue<T>::empty() const
{
	return (size() == 0);
}

template<typename T>
size_t Queue<T>::size() const
{
	return _size;
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
PriorityQueue<T>::PriorityQueue()
{
	_front = NULL;
	_size = 0;
}

template<typename T>
PriorityQueue<T>::~PriorityQueue()
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
bool PriorityQueue<T>::empty() const
{
	return (size() == 0);
}

template<typename T>
size_t PriorityQueue<T>::size() const
{
	return _size;
}

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
