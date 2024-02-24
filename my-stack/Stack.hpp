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

    void push(T);
    void pop();
    T top();
private:
    StackNode<T> *_top = nullptr;
};

template<class T>
Stack<T>::Stack() = default;

template<class T>
Stack<T>::Stack(Stack &&other) {
    _top = other._top;
    other._top = nullptr;
}

template<class T>
Stack<T>& Stack<T>::operator=(Stack<T> && other) {
    _top = other._top;
    other._top = nullptr;
    return *this;
}

template<class T>
Stack<T>::~Stack() {
    while (_top) {
        auto next = _top->next;
        delete(_top);
        _top = next;
    }
}

template<class T>
void Stack<T>::push(T data) {
    auto *ptr = _top;
    _top = new StackNode<T>;
    _top->data = data;
    _top->next = ptr;
}

template<class T>
void Stack<T>::pop() {
    StackNode<T> *ptr = _top;
    if (_top) {
        _top = _top->next;
    }
    delete(ptr);
}

template<class T>
T Stack<T>::top() {
    return _top->data;
}