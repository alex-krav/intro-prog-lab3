#include "data_structures.h"
#include <iostream>

using namespace std;

int main() {

    try {
        PriorityQueue<char, int> queue;
        cout << "empty: " << queue.empty() << endl;
        cout << "size: " << queue.size() << endl;

        queue.push('a', 3);
        queue.push('b', 2);
        queue.push('c', 1);

        cout << "top: " << queue.top() << endl;
        cout << "empty: " << queue.empty() << endl;
        cout << "size: " << queue.size() << endl;
        cout << endl;

        while (queue.size()) {
            cout << "top: " << queue.top() << endl;
            queue.pop();
        }
        cout << "empty: " << queue.empty() << endl;
        cout << "size: " << queue.size() << endl;

        queue.pop();
        delete(&queue);
    }
    catch (exception e) {
        cerr << e.what() << endl;
    }
    

    return 0;
}