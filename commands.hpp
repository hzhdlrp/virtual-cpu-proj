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
    virtual void set(std::ifstream *input) {}
    virtual void doit() {}
    virtual void method() {
        std::cout << "." << std::endl;
    }
};

struct Begin : Commands {
    void doit() override {}
    void method() override {
        std::cout << "!" << std::endl;
    }
};

struct End : Commands {
    void doit() override {}
};

struct Push : Commands {
    size_t _value = 0;
    Stack<size_t> *_stack = nullptr;

    void set(std::ifstream *input) override {
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

    void set(std::ifstream *input) override {
        *input >> _reg;
    }

    Pushr(Stack<size_t> *stack, Registers *registers) : Push(stack) {
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

    void set(std::ifstream *input) override {
        *input >> _reg;
    }

    Popr(Stack<size_t> *stack, Registers *registers): Pop(stack) {
        _stack = stack;
        _registers = registers;
    }

    void doit() override {
        if (_reg == "AX") _registers->AX = _stack->top();
        if (_reg == "BX") _registers->BX = _stack->top();
        if (_reg == "CX") _registers->CX = _stack->top();
        if (_reg == "DX") _registers->DX = _stack->top();
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

struct Out : Commands {
    Stack<size_t> *_stack;
    explicit Out(Stack<size_t> *stack)  {
        _stack = stack;
    }

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

struct Jmp : Commands {
    std::string _label = std::string("");
    std::vector<std::unique_ptr<Commands>> *_commandsVector = nullptr;
    std::map<std::string , size_t> *_labelsIndexes = nullptr;
    size_t _index = 0;

    void set(std::ifstream *input) override {
        *input >> _label;
    }

    Jmp(std::vector<std::unique_ptr<Commands>> *commandsVector, std::map<std::string , size_t> *labelsIndexes) {
        _commandsVector = commandsVector;
        _labelsIndexes = labelsIndexes;
        _index = (*_labelsIndexes)[_label];
    }

    void doit() override {
        for (size_t i = _index; i < _commandsVector->size(); ++i) {
            (*_commandsVector)[i]->doit();
        }
    }
};

struct Jne : Jmp {
    Stack<size_t> *_stack;
    Registers *_registers;

    Jne(std::vector<std::unique_ptr<Commands>> *commandsVector, std::map<std::string , size_t> *labelsIndexes, Stack<size_t> *stack, Registers *registers) : Jmp(commandsVector, labelsIndexes) {
        _stack = stack;
        _registers = registers;
    }

    void doit() override {
        _registers->F1X = _stack->top();
        _stack->pop();
        _registers->F2X = _stack->top();
        _stack->push(_registers->F1X);
        if (_registers->F1X != _registers->F2X) {
            Jmp::doit();
        }
    }
};

