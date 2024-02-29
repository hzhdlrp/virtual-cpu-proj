#ifndef PROJECT2_STACK_HPP
#define PROJECT2_STACK_HPP

#endif //PROJECT2_STACK_HPP

template<class T>
struct StackNode {
    StackNode<T> *next = nullptr;
    T data;

    StackNode();
    StackNode(const StackNode &);
    StackNode(StackNode &&) noexcept;
    StackNode& operator=(const StackNode &);
    StackNode& operator=(StackNode &&) noexcept;
    ~StackNode();
};

template<class T>
StackNode<T>::StackNode() = default;

template<class T>
StackNode<T>::StackNode(StackNode &&other) noexcept {
    data = other.data;
    next = other.next;
    other.next = nullptr;
}

template<class T>
StackNode<T>::StackNode(const StackNode &other) {
    next = other.next;
    data = other.data;
}

template<class T>
StackNode<T>& StackNode<T>::operator=(StackNode<T> &&other) noexcept {
    data = other.data;
    next = other.next;
    other.next = nullptr;
    return *this;
}

template<class T>
StackNode<T> &StackNode<T>::operator=(const StackNode<T> &other) {
    next = other.next;
    data = other.data;
    return *this;
}

template<class T>
StackNode<T>::~StackNode() = default;

template<class T>
class Stack {
public:
    Stack();
    Stack(const Stack &);
    Stack(Stack &&) noexcept;
    Stack& operator=(const Stack &);
    Stack& operator=(Stack &&) noexcept;
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
Stack<T>::Stack(Stack &&other) noexcept {
    _top = other._top;
    other._top = nullptr;
}

template<class T>
Stack<T>::Stack(const Stack &other) {
    if (other._top != nullptr) {
        _top = new StackNode<T>;
        *_top = *(other._top);
        auto *ptr1 = other._top;
        auto *ptr2 = _top;
        while (ptr1->next) {
            ptr2->next = new StackNode<T>;
            *(ptr2->next) = *(ptr1->next);
            ptr1 = ptr1->next;
            ptr2 = ptr2->next;
        }
    } else {
        _top = nullptr;
    }

}

template<class T>
Stack<T>& Stack<T>::operator=(Stack<T> && other) noexcept {
    _top = other._top;
    other._top = nullptr;
    return *this;
}

template<class T>
Stack<T>& Stack<T>::operator=(const Stack<T> &other) {
    if (other._top != nullptr) {
        _top = new StackNode<T>;
        *_top = *(other._top);
        StackNode<T> *ptr1 = other._top;
        StackNode<T> *ptr2 = _top;
        while (ptr1->next) {
            ptr2->next = new StackNode<T>;
            *(ptr2->next) = *(ptr1->next);
            ptr1 = ptr1->next;
            ptr2 = ptr2->next;
        }
    } else {
        _top = nullptr;
    }
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
    if (_top) {
        return _top->data;
    } else {
        return NULL;
    }
}