#include "data_structures.h"
#include <type_traits>
#include <stdexcept>

using namespace std;

Queue::Queue()
{
	_front = NULL;
	_rear = NULL;
	_temp = NULL;
	_size = 0;
}

Queue::~Queue()
{
	Node* current = _front;
	Node* next;

	while (current != NULL) {
		next = current->next;
		delete current;
		current = next;
	}
}

bool Queue::empty() const
{
	return (size() == 0);
}

size_t Queue::size() const
{
	return _size;
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
		_temp = new Node;
		_rear->next = _temp;
		_temp->data = val;
		_temp->next = NULL;
		_rear = _temp;
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
		_temp = _front->next;
		delete _front;
		_front = _temp;
	}
	else {
		delete _front;
		_front = NULL;
		_rear = NULL;
	}
	
	--_size;
}
