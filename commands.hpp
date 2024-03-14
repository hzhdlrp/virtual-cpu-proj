#include <utility>

#ifndef PROJECT2_COMMANDS_H
#define PROJECT2_COMMANDS_H

#endif //PROJECT2_COMMANDS_H

struct Registers {
    size_t AX = 0;
    size_t BX = 0;
    size_t CX = 0;
    size_t DX = 0;
    size_t F1X = 0;
    size_t F2X = 0;
};

struct Commands {
    Commands() = default;
    virtual void setReg(std::ifstream *input) {}
    virtual void setValue(std::ifstream *input) {}
    virtual void doit() {};
};

struct Begin : Commands {
    void doit() override {
    }
};

struct End : Commands {
    void doit() override {}
};

struct Push : Commands {
    size_t _value = 0;
    Stack<size_t> *_stack = nullptr;

    void setValue(std::ifstream *input) override {
        *input >> _value;
    }

    explicit Push(Stack<size_t> *stack) {
        _stack = stack;
    }

    void doit() override {
        _stack->push(_value);
    }
};

struct Pushr : Push {
    std::string _reg = std::string("");
    Registers *_registers = nullptr;

    void setReg(std::ifstream *input) override {
        *input >> _reg;
    }

    Pushr(Stack<size_t> *stack, Registers *registers) : Push(stack) {
        _stack = stack;
        _registers = registers;
    }

    void doit() override {
        if (_reg == "AX") _stack->push(_registers->AX);
        if (_reg == "BX") _stack->push(_registers->BX);
        if (_reg == "CX") _stack->push(_registers->CX);
        if (_reg == "DX") _stack->push(_registers->DX);
    }
};

struct Pop : Commands {
    Stack<size_t> *_stack = nullptr;

    explicit Pop(Stack<size_t> *stack) {
        _stack = stack;
    }

    void doit() override {
        _stack->pop();
    }
};

struct Popr : Pop {
    std::string _reg = std::string("");
    Registers *_registers = nullptr;

    void setReg(std::ifstream *input) override {
        *input >> _reg;
    }

    Popr(Stack<size_t> *stack, Registers *registers): Pop(stack) {
        _stack = stack;
        _registers = registers;
    }

    void doit() override {
        if (_reg == "AX") _stack->push(_registers->AX);
        if (_reg == "BX") _stack->push(_registers->BX);
        if (_reg == "CX") _stack->push(_registers->CX);
        if (_reg == "DX") _stack->push(_registers->DX);
        _stack->pop();
    }
};

struct Add : Commands {
    Stack<size_t> *_stack;
    Registers *_registers;

    Add(Stack<size_t> *stack, Registers *registers) {
        _stack = stack;
        _registers = registers;
    }

    void doit() override {
        _registers->F1X = _stack->top();
        _stack->pop();
        _registers->F2X = _stack->top();
        _stack->push(_registers->F1X + _registers->F2X);
    }
};

struct Sub : Commands {
    Stack<size_t> *_stack;
    Registers *_registers;

    Sub(Stack<size_t> *stack, Registers *registers) {
        _stack = stack;
        _registers = registers;
    }

    void doit() override {
        _registers->F1X = _stack->top();
        _stack->pop();
        _registers->F2X = _stack->top();
        _stack->push(_registers->F1X - _registers->F2X);
    }
};

struct Mul : Commands {
    Stack<size_t> *_stack;
    Registers *_registers;

    Mul(Stack<size_t> *stack, Registers *registers) {
        _stack = stack;
        _registers = registers;
    }

    void doit() override {
        _registers->F1X = _stack->top();
        _stack->pop();
        _registers->F2X = _stack->top();
        _stack->push(_registers->F1X * _registers->F2X);
    }
};

struct Div : Commands {
    Stack<size_t> *_stack;
    Registers *_registers;

    Div(Stack<size_t> *stack, Registers *registers) {
        _stack = stack;
        _registers = registers;
    }

    void doit() override {
        _registers->F1X = _stack->top();
        _stack->pop();
        _registers->F2X = _stack->top();
        _stack->push(_registers->F1X / _registers->F2X);
    }
};

struct Out : Pop {
    explicit Out(Stack<size_t> *stack) : Pop(stack) {}

    void doit() override {
        std::cout << _stack->top() << std::endl;
        _stack->pop();
    }
};

struct In : Push {
    explicit In(Stack<size_t> *stack) : Push(stack) {}

    void doit() override {
        std::cin >> _value;
        _stack->push(_value);
    }
};

