#ifndef PROJECT2_COMMANDS_H
#define PROJECT2_COMMANDS_H

#endif //PROJECT2_COMMANDS_H

struct Registers {
    size_t AX = 0;
    size_t BX = 0;
    size_t CX = 0;
    size_t DX = 0;
};

struct Commands {
    virtual void doit() = 0;
    std::ifstream *_inputFile = nullptr;
    std::ifstream *_outputFile = nullptr;
};

struct Begin : Commands {
    void doit() override {}
};

struct End : Commands {
    void doit() override {}
};

struct Push : Commands {
    size_t _value = 0;
    Stack<size_t> *_stack = nullptr;

    Push(std::ifstream *input, Stack<size_t> *stack) {
        _inputFile = input;
        _stack = stack;
    }

    void doit() override {
        if (_inputFile->is_open())
            (*_inputFile) >> _value;
        else
            throw std::runtime_error("can't read a file");

        _stack->push(_value);
    }
};

struct Pushr : Push {
    std::string _reg = std::string("");
    Registers *_registers = nullptr;

    Pushr(std::ifstream *input, Stack<size_t> *stack, Registers *registers) : Push(input, stack) {
        _inputFile = input;
        _stack = stack;
        _registers = registers;
    }

    void doit() override {
        if (_inputFile->is_open())
            (*_inputFile) >> _reg;
        else
            throw std::runtime_error("can't read a file");

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

    Popr(std::ifstream *input, Stack<size_t> *stack, Registers *registers) : Pop(stack) {
        _inputFile = input;
        _stack = stack;
        _registers = registers;
    }

    void doit() override {
        if (_inputFile->is_open())
            (*_inputFile) >> _reg;
        else
            throw std::runtime_error("can't read a file");

        if (_reg == "AX") _stack->push(_registers->AX);
        if (_reg == "BX") _stack->push(_registers->BX);
        if (_reg == "CX") _stack->push(_registers->CX);
        if (_reg == "DX") _stack->push(_registers->DX);
        _stack->pop();
    }



};




