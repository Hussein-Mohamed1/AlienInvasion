#pragma once
#include "LinkedQueue.h"
template<class T>
class DoublyLinkedQueue :public LinkedQueue<T>
{
public:
	bool DequeueFromBack(Node<T>* Back)
	{
		if (!backPtr)
			return false;

		if (backPtr == frontPtr){
			T Data = 0;
			dequeue(Back, Data);
		}

		else {
			Back = backPtr;
			backPtr = backPtr->getPrev();
			backPtr->setNext(nullptr);
		}
		return true;
	}
	bool DoublyDequeue(Node<T>* Front, Node<T>* Back)
	{
		if (dequeue(Front) && DequeueFromBack(Back))
			return true;
		return false;
	}
};

