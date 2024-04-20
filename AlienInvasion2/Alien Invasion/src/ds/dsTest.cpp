//#include <iostream>
//#include "LinkedQueue.h"
//
//int main() {
//    LinkedQueue<int> queue;
//
//    // Test the isEmpty() method
//    std::cout << "Is the queue empty? " << (queue.isEmpty() ? "Yes" : "No") << std::endl;  // Expected output: Yes
//
//    // Test the enqueue() method
//    queue.enqueue(1);
//    queue.enqueue(2);
//    queue.enqueue(3);
//
//    // Test the isEmpty() method again
//    std::cout << "Is the queue empty? " << (queue.isEmpty() ? "Yes" : "No") << std::endl;  // Expected output: No
//
//    // Test the peek() method
//    int front;
//    if (queue.peek(front)) {
//        std::cout << "The front of the queue is " << front << std::endl;  // Expected output: 1
//    }
//
//    // Test the dequeue() method
//    if (queue.dequeue(front)) {
//        std::cout << "The dequeued element is " << front << std::endl;  // Expected output: 1
//    }
//
//    // Test the peek() method again
//    if (queue.peek(front)) {
//        std::cout << "The front of the queue is " << front << std::endl;  // Expected output: 2
//    }
//
//    return 0;
//}
