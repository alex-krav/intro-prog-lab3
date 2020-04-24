#ifndef DATA_STR_H
#define DATA_STR_H

using namespace std;

struct Node {
    int data;
    struct Node* next;
};

class BaseQueue 
{
protected:
    Node* _front;
    size_t _size;

public:
    BaseQueue();
    virtual ~BaseQueue();

    bool empty() const; // queue empty?
    size_t size() const; // queue size
    virtual void push(int val) = 0; // insert new element at the end 
    virtual void pop() = 0; // remove next element
};

class Queue : public BaseQueue
{
    Node* _rear;

public:
    Queue();

    void push(int val);
    void pop();
    int& front(); // ref to next element
    int& back(); // ref to last element
};

class PriorityQueue : public BaseQueue
{
public:
    void push(int val);
    void pop();
    int& top(); // ref to the top element
};

#endif 
