#pragma once

#include "priNode.h"


//This class implements the priority queue as a sorted list (Linked List)
//The item with the highest priority is at the front of the queue

enum { HighestPri = 0, LowestPri = 1 };
template<typename T>
class priQueue 
{
    priNode<T> *head;
    

    int itemCount{0};
public:
    int getCount() const {
        return itemCount;
    }

public:
    priQueue() : head(nullptr) {}

    ~priQueue() {
        T tmp;
        int p;
        while (dequeue(tmp, p));
    }

    //insert the new node in its correct position according to its priority
     //  default Case HighestPri  0  ,    LowestPti    1    is the third Argument to Func
    void enqueue(const T &data, int priority , int CaseOfInsertion=HighestPri )  
    {
            priNode<T>* newNode = new priNode<T>(data, priority);
            
            if (LowestPri)
                priority = -priority;

        if (head == nullptr || priority > head->getPri()) {

            newNode->setNext(head);
            head = newNode;
            return;
        }

        priNode<T> *current = head;
        while (current->getNext() && priority <= current->getNext()->getPri()) {
            current = current->getNext();
        }
        newNode->setNext(current->getNext());
        current->setNext(newNode);
        itemCount++;
    }

    bool dequeue(T &topEntry, int &pri)
    {
        if (isEmpty())
            return false;

        topEntry = head->getItem(pri);
        priNode<T> *temp = head;
        head = head->getNext();
        delete temp;
        itemCount--;
        return true;
    }

    bool peek(T &topEntry, int &pri) {
        if (isEmpty())
            return false;

        topEntry = head->getItem(pri);

        return true;
    }

    bool isEmpty() const {
        return head == nullptr;
    }
};
