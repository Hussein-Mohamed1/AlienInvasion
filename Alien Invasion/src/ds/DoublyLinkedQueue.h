#pragma once
#include "LinkedQueue.h"
template<class T>
class DoublyLinkedQueue :public LinkedQueue<T>
{
public:
	bool DequeueFromFront(Node<T>* Ptr, T Data)
	{
		if (!frontPtr)
			retutn false;

		Ptr = frontPtr;

		if (frontPtr == backPtr)
		{
			dequeue(Ptr, Data);
		}

		else {
			frontPtr = frontPtr->getNext();
			frontPtr->setPrev(nullptr);
		}
		return true;
	}
};

