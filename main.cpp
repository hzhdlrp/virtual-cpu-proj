#include <iostream>
#include "my-stack/Stack.hpp"
#include <fstream>
#include <memory>
#include <vector>
#include <memory>
#include <map>
#include "commands.hpp"

class Virtual {
public:
    void start(std::ifstream *input) {
        setInputFile(input);
        std::string cmd;
        do {
            (*_inputFile) >> cmd;
            _commandsByNames[cmd]->doit();
        } while (cmd != std::string("END"));
    }
    Virtual() {
        _commandsByNames["BEGIN"] = std::make_unique<Begin>();
        _commandsByNames["END"] = std::make_unique<End>();
        _commandsByNames["PUSH"] = std::make_unique<Push>(_inputFile, &_stack);
        _commandsByNames["PUSHR"] = std::make_unique<Pushr>(_inputFile, &_stack, &_registers);
        _commandsByNames["POP"] = std::make_unique<Pop>(&_stack);
        _commandsByNames["POPR"] = std::make_unique<Popr>(_inputFile, &_stack, &_registers);
        _commandsByNames["ADD"] = std::make_unique<Add>(&_stack, &_registers);
        _commandsByNames["SUB"] = std::make_unique<Sub>(&_stack, &_registers);
        _commandsByNames["MUL"] = std::make_unique<Mul>(&_stack, &_registers);
        _commandsByNames["DIV"] = std::make_unique<Div>(&_stack, &_registers);
        _commandsByNames["OUT"] = std::make_unique<Out>(&_stack);
        _commandsByNames["IN"] = std::make_unique<In>(_inputFile, &_stack);


    }
private:
    std::ifstream *_inputFile = nullptr;
    Stack<size_t> _stack;
    Registers _registers;
    std::vector<std::string> _commandsNamesStack;

    std::map<std::string, std::unique_ptr<Commands>> _commandsByNames;

    void setInputFile(std::ifstream *input) {
        _inputFile = input;
    }
};

int main() {
    std::ifstream input("/Users/vadimleonov/Desktop/алгосы/virtual-cpu-tests/fibo");
    Virtual myCpu;
    myCpu.start(&input);
    return 0;
}