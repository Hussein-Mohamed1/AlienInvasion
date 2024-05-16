#pragma once

#include "LinkedQueue.h"

template<class T>
class DoublyLinkedQueue : public LinkedQueue<T> {
    int backOrFront{
            0}; ///@note 0 for front, 1 for back, this variable is used to track from which side the last dequeue operation happened
public:
    int getBackOrFront() const {
        return backOrFront;
    }

public:
    bool dequeue(T &Item) {
        ///@note maybe unnecessary but I added this to make sure that a drone is picked from either side using doublyDequeue
        return LinkedQueue<T>::dequeue(Item);

    }

    bool DequeueFromBack(T &Back) {
        if (!this->backPtr)
            return false;

        if (this->backPtr->getItem()->getId() == this->frontPtr->getItem()->getId()) {
            return LinkedQueue<T>::dequeue(Back);
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
        return false;
    }
};