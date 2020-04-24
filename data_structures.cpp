#include "data_structures.h"
#include <type_traits>
#include <stdexcept>

using namespace std;

BaseQueue::BaseQueue()
{
	_front = NULL;
	_size = 0;
}

BaseQueue::~BaseQueue()
{
	Node* current = _front;
	Node* next;

	while (current != NULL) {
		next = current->next;
		delete current;
		current = next;
	}
}

bool BaseQueue::empty() const
{
	return (size() == 0);
}

size_t BaseQueue::size() const
{
	return _size;
}

/*****************************************************/

Queue::Queue()
{
	_rear = NULL;
}

int& Queue::front()
{
	if (empty())
	{
		throw runtime_error("Queue is empty");
	}
	return _front->data;
}

int& Queue::back()
{
	if (empty())
	{
		throw runtime_error("Queue is empty");
	}
	return _rear->data;
}

void Queue::push(int val)
{
	if (_rear == NULL) {
		_rear = new Node;
		_rear->next = NULL;
		_rear->data = val;
		_front = _rear;
	}
	else {
		Node* temp = new Node;
		_rear->next = temp;
		temp->data = val;
		temp->next = NULL;
		_rear = temp;
	}
	++_size;
}

void Queue::pop()
{
	if (empty())
	{
		throw runtime_error("Queue is empty");
	}

	if (_front->next != NULL) {
		Node* temp = _front->next;
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

int& PriorityQueue::top()
{
	if (empty())
	{
		throw runtime_error("PriorityQueue is empty");
	}
	return _front->data;
}

void PriorityQueue::push(int val)
{
	Node* temp = new Node;
	temp->data = val;

	if (_front == NULL || val > _front->data) {
		temp->next = _front;
		_front = temp;
	} 
	else {
		Node *prev = _front;
		while (prev->next != NULL && prev->next->data >= val)
			prev = prev->next;
		temp->next = prev->next;
		prev->next = temp;
	}

	++_size;
}

void PriorityQueue::pop()
{
	if (empty())
	{
		throw runtime_error("Queue is empty");
	}

	if (_front->next != NULL) {
		Node* temp = _front->next;
		delete _front;
		_front = temp;
	}
	else {
		delete _front;
		_front = NULL;
	}

	--_size;
}
