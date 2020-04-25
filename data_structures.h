#ifndef DATA_STR_H
#define DATA_STR_H

#include <type_traits>
#include <stdexcept>

using namespace std;

template<typename T, typename P>
struct Pair {
	T value;
	P priority;
};

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
	virtual void push(T val) {} // insert new element at the end 
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

template<typename T, typename P>
class PriorityQueue: BaseQueue<Pair<T,P>>
{
	typedef Pair<T, P> PQElement;
	using BaseQueue<PQElement>::_size;
	using BaseQueue<PQElement>::_front;
	bool (*comparator)(P, P);

public:
	using BaseQueue<PQElement>::empty;
	using BaseQueue<PQElement>::size;

	PriorityQueue() {}
	PriorityQueue(bool (*comparator)(P, P));

    void push(T val, P priority); // insert new element at the end 
    void pop(); // remove next element
    T& top(); // ref to the top element
};

/************************ BaseQueue *****************************/

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

/************************* Queue ****************************/

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
		_rear->data = val;
		_rear->next = NULL;
		_front = _rear;
	}
	else {
		Node<T>* temp = new Node<T>;
		temp->data = val;
		temp->next = NULL;
		_rear->next = temp;
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

/************************** PriorityQueue ***************************/

template<typename T, typename P>
PriorityQueue<T, P>::PriorityQueue(bool (*comparator_)(P, P))
{
	comparator = comparator_;
}

template<typename P>
bool greater_comp(P left, P right) {
	return left > right;
}

template<typename P>
bool less_comp(P left, P right) {
	return left < right;
}

template<typename T, typename P>
T& PriorityQueue<T, P>::top()
{
	if (empty())
	{
		throw runtime_error("PriorityQueue is empty");
	}
	return _front->data.value;
}

template<typename T, typename P>
void PriorityQueue<T, P>::push(T val, P priority)
{
	Pair<T, P>* pair = new Pair<T, P>;
	pair->value = val; pair->priority = priority;
	Node<Pair<T, P>>* temp = new Node<Pair<T, P>>;
	temp->data = *pair;

	if (_front == NULL || comparator(priority, _front->data.priority)) {
		temp->next = _front;
		_front = temp;
	}
	else {
		Node<Pair<T, P>>* prev = _front;
		while (prev->next != NULL && (comparator(prev->next->data.priority, priority) || prev->next->data.priority == priority))
			prev = prev->next;
		temp->next = prev->next;
		prev->next = temp;
	}

	++_size;
}

template<typename T, typename P>
void PriorityQueue<T, P>::pop()
{
	if (empty())
	{
		throw runtime_error("Queue is empty");
	}

	if (_front->next != NULL) {
		Node<PQElement>* temp = _front->next;
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
