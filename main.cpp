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
private:
    std::ifstream *_inputFile = nullptr;
    Stack<size_t> _stack;
    Registers _registers;
    std::vector<std::string> _commandsNamesStack;

    std::map<std::string, std::unique_ptr<Commands>> _commandsByNames = {
            {"BEGIN", std::make_unique<Begin>()},
            {"END", std::make_unique<End>()},
            {"PUSH", std::make_unique<Push>(_inputFile, &_stack)},
            {"PUSHR", std::make_unique<Pushr>(_inputFile, &_stack, &_registers)},
            {"POP", std::make_unique<Pop>(&_stack)},
            {"POPR", std::make_unique<Popr>(_inputFile, &_stack, &_registers)},
            {"ADD", std::make_unique<Add>(&_stack, &_registers)},
            {"SUB", std::make_unique<Sub>(&_stack, &_registers)},
            {"MUL", std::make_unique<Mul>(&_stack, &_registers)},
            {"DIV", std::make_unique<Div>(&_stack, &_registers)},
            {"OUT", std::make_unique<Out>(&_stack)},
            {"IN", std::make_unique<In>(_inputFile, &_stack)},
    };

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