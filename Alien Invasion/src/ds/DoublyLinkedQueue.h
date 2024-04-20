#pragma once

#include "LinkedQueue.h"

template<class T>
class DoublyLinkedQueue : public LinkedQueue<T> {
    int backOrFront{0};
public:
    bool DequeueFromBack(T &Back) {
        if (!this->backPtr)
            return false;

        if (this->backPtr->getItem()->getId() == this->frontPtr->getItem()->getId()) {
            return  LinkedQueue<T>::dequeue(Back);
        } else {
            Back = this->backPtr->getItem();
            this->backPtr = this->backPtr->getPrev();
            this->backPtr->setNext(nullptr);
            this->itemCount--;
            return true;
        }

    }

    bool DoublyDequeue(T &Item) {
        if (!backOrFront) {
            backOrFront = 1;
            return LinkedQueue<T>::dequeue(Item);
        } else {
            backOrFront = 0;
            return DequeueFromBack(Item);
        }
    }
};

