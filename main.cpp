#include <iostream>
#include "data_structures.h"

using namespace std;

int main() {

    try {
        PriorityQueue queue;
        cout << "empty: " << queue.empty() << endl;
        cout << "size: " << queue.size() << endl;

        int arr[] = { 5,7,9 };
        for (int item : arr) {
            queue.push(item);
        }
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