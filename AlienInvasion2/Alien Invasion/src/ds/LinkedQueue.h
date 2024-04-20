
/*
This is a program that implements the queue abstract data type using a linked list.
The queue is implemented as a chain of linked nodes that has two pointers,
a frontPtr pointer for the front of the queue and a backPtr pointer for the back of the queue.
*/

/*

				The Node: item of type T and a "next" pointer
					-------------
					| item| next | --->
					-------------
General Queue case:

				 frontPtr																backPtr
					\											   						/
					 \											  					   /
					------------- 	  ------------- 	  ------------- 	  -------------
					| item| next |--->| item| next |--->  | item| next |--->  | item| next |---> NULL
					------------- 	  ------------- 	  ------------- 	  -------------

Empty Case:

				 frontptr	 backptr
						\	 /
						 \	/
					---- NULL ------


Single Node Case:
				 frontPtr	 backPtr
					\		/
					 \	   /
					-----------
					|item| next| -->NULL
					-----------

*/

#ifndef LINKED_QUEUE_
#define LINKED_QUEUE_


#include "Node.h"
#include "QueueADT.h"
#include "iostream"

using namespace std;

template<typename T>
class LinkedQueue : public QueueADT<T> {
protected:
    Node<T> *backPtr{nullptr};
    Node<T> *frontPtr{nullptr};
    int itemCount{0};
public:
    LinkedQueue();

    bool isEmpty() const;

    bool enqueue(const T &newEntry);

    bool dequeue(T &frntEntry);

    bool peek(T &frntEntry) const;

    int getCount() const {
        return itemCount;
    }

    ~LinkedQueue();
};
/////////////////////////////////////////////////////////////////////////////////////////

/*
Function: Queue()
The constructor of the Queue class.

*/

template<typename T>
LinkedQueue<T>::LinkedQueue() {
    backPtr = nullptr;
    frontPtr = nullptr;

}
/////////////////////////////////////////////////////////////////////////////////////////

/*
Function: isEmpty
Sees whether this queue is empty.

Input: None.
Output: True if the queue is empty; otherwise false.
*/
template<typename T>
bool LinkedQueue<T>::isEmpty() const {
    return (frontPtr == nullptr);
}

/////////////////////////////////////////////////////////////////////////////////////////

/*Function:enqueue
Adds newEntry at the back of this queue.

Input: newEntry .
Output: True if the operation is successful; otherwise false.
*/

template<typename T>
bool LinkedQueue<T>::enqueue(const T &newEntry) {

    itemCount++;

    Node<T> *newNodePtr = new Node<T>(newEntry);
    // Insert the new node
    if (isEmpty())    //special case if this is the first node to insert
        frontPtr = newNodePtr; // The queue is empty
    else {
        backPtr->setNext(newNodePtr); // The queue was not empty
        newNodePtr->setPrev(backPtr);
    }

    backPtr = newNodePtr; // New node is the last node now
    return true;
} // end enqueue


/////////////////////////////////////////////////////////////////////////////////////////////////////////

/*Function: dequeue
Removes the front of this queue. That is, removes the item that was added
earliest.

Input: None.
Output: True if the operation is successful; otherwise false.
*/

template<typename T>
bool LinkedQueue<T>::dequeue(T &frntEntry) {
    if (isEmpty())
        return false;
    Node<T> *nodeToDeletePtr = frontPtr;
    frntEntry = frontPtr->getItem();
    frontPtr = frontPtr->getNext();

    if (frontPtr)
        frontPtr->setPrev(nullptr);

    if (nodeToDeletePtr == backPtr)
        frontPtr = backPtr = nullptr;


    // Free memory reserved for the dequeued node
    delete nodeToDeletePtr;

    itemCount--;

    return true;
}



/////////////////////////////////////////////////////////////////////////////////////////

/*
Function: peek
copies the front of this queue to the passed param. The operation does not modify the queue.

Input: None.
Output: The front of the queue.
*/

template<typename T>
bool LinkedQueue<T>::peek(T &frntEntry) const {
    if (isEmpty())
        return false;

    frntEntry = frontPtr->getItem();
    return true;

}
///////////////////////////////////////////////////////////////////////////////////

template<typename T>
LinkedQueue<T>::~LinkedQueue() {
    //Free all nodes in the queue
    T temp;
    while (dequeue(temp));
}

#endif

