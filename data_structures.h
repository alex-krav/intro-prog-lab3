#ifndef DATA_STR_H
#define DATA_STR_H

using namespace std;

struct Node {
    int data;
    struct Node* next;
};

class Queue
{
    Node* _front;
    Node* _rear;
    Node* _temp;
    size_t _size;

public:
    Queue();
    ~Queue();

    bool empty() const; // queue empty?
    size_t size() const; // queue size
    int& front(); // ref to next element
    int& back(); // ref to last element
    void push(int val); // insert new element at the end 
    void pop(); // remove next element
};

#endif 
