#ifndef _NODE
#define _NODE

template<typename T>
class Node {
private:
    T item; // A data item
    Node<T> *next; // Pointer to next node
    Node<T> *prev;
public:
    Node();

    Node(const T &r_Item);

    Node(const T &r_Item, Node<T> *nextNodePtr, Node<T> *prevPtr = nullptr);

    void setItem(const T &r_Item);

    void setNext(Node<T> *nextNodePtr);

    T getItem() const;

    Node<T> *getNext() const;

    Node<T> *getPrev() const;

    void setPrev(Node<T> *prev);
}; // end Node
#endif

template<typename T>
Node<T>::Node() {
    next = prev = nullptr;
}

template<typename T>
Node<T>::Node(const T &r_Item) {
    item = r_Item;
    next = prev = nullptr;
}

template<typename T>
Node<T>::Node(const T &r_Item, Node<T> *nextNodePtr, Node<T> *prevPtr) {
    item = r_Item;
    next = nextNodePtr;
    prev = prevPtr;
}

template<typename T>
void Node<T>::setItem(const T &r_Item) {
    item = r_Item;
}

template<typename T>
void Node<T>::setNext(Node<T> *nextNodePtr) {
    next = nextNodePtr;
}

template<typename T>
Node<T> *Node<T>::getPrev() const {
    return prev;
}

template<typename T>
void Node<T>::setPrev(Node<T> *l_prev) {
    Node::prev = l_prev;
}

template<typename T>
T Node<T>::getItem() const {
    return item;
}

template<typename T>
Node<T> *Node<T>::getNext() const {
    return next;
}

