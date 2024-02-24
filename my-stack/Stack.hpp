#ifndef PROJECT2_STACK_HPP
#define PROJECT2_STACK_HPP

#endif //PROJECT2_STACK_HPP

template<class T>
struct StackNode {
    StackNode<T> *next = nullptr;
    T data;

    StackNode();
    StackNode(T, StackNode<T> *);
    StackNode(const StackNode &) = delete;
    StackNode(StackNode &&);
    StackNode& operator=(const StackNode &) = delete;
    StackNode& operator=(StackNode &&);
    ~StackNode();
};

template<class T>
StackNode<T>::StackNode() = default;

template<class T>
StackNode<T>::StackNode(T data, StackNode<T> *ptr): data(data), next(ptr) {}


template<class T>
StackNode<T>::StackNode(StackNode &&other) {
    data = other.data;
    next = other.next;
    other.next = nullptr;
}

template<class T>
StackNode<T>& StackNode<T>::operator=(StackNode<T> &&other) {
    data = other.data;
    next = other.next;
    other.next = nullptr;
    return *this;
}

template<class T>
StackNode<T>::~StackNode() {
    delete data;
}

template<class T>
class Stack {
public:
    Stack();
    Stack(const Stack &) = delete;
    Stack(Stack &&);
    Stack& operator=(const Stack &) = delete;
    Stack& operator=(Stack &&);
    ~Stack();

private:
    StackNode<T> *top = nullptr;
};

template<class T>
Stack<T>::Stack() = default;

template<class T>
Stack<T>::Stack(Stack &&other) {
    top = other.top;
    other.top = nullptr;
}

template<class T>
Stack<T>& Stack<T>::operator=(Stack<T> && other) {
    top = other.top;
    other.top = nullptr;
    return *this;
}

template<class T>
Stack<T>::~Stack() {
    while (top) {
        auto next = top->next;
        delete(top);
        top = next;
    }
}