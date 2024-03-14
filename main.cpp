#include <iostream>
#include "my-stack/Stack.hpp"
#include <fstream>
#include <memory>
#include <vector>
#include <map>
#include "commands.hpp"

class Virtual {
public:
    void start() {
        do {
            std::string cmd = std::string("");
            *_inputFile >> cmd;
            std::unique_ptr<Commands> command = std::make_unique<Commands>();
            *command = *_commandsByNames[cmd];
            command->setReg(_inputFile);
            command->setValue(_inputFile);
            _commandsVector.push_back(command);
            if (cmd == std::string("BEGIN")) _isBegun = true;

            if (_isBegun) {
                if (_commandsByNames.contains(cmd)) {
                    _commandsByNames[cmd]->doit();
                }
            }
        } while (cmd != std::string("END"));
    }

    Virtual(std::ifstream *input) {
        if (!input) throw std::runtime_error("null on input stream");
        _inputFile = input;
        _commandsByNames["BEGIN"] = std::make_unique<Begin>();
        _commandsByNames["END"] = std::make_unique<End>();
        _commandsByNames["PUSH"] = std::make_unique<Push>(&_stack);
        _commandsByNames["PUSHR"] = std::make_unique<Pushr>(&_stack, &_registers);
        _commandsByNames["POP"] = std::make_unique<Pop>(&_stack);
        _commandsByNames["POPR"] = std::make_unique<Popr>(&_stack, &_registers);
        _commandsByNames["ADD"] = std::make_unique<Add>(&_stack, &_registers);
        _commandsByNames["SUB"] = std::make_unique<Sub>(&_stack, &_registers);
        _commandsByNames["MUL"] = std::make_unique<Mul>(&_stack, &_registers);
        _commandsByNames["DIV"] = std::make_unique<Div>(&_stack, &_registers);
        _commandsByNames["OUT"] = std::make_unique<Out>(&_stack);
        _commandsByNames["IN"] = std::make_unique<In>( &_stack);
    }
private:
    std::ifstream *_inputFile = nullptr;
    Stack<size_t> _stack;
    Registers _registers;
    std::vector<std::unique_ptr<Commands>> _commandsVector;
    std::map<std::string , int> _labelsIndexes;
//    std::vector<int> _functionsIndexes;
//    bool _inFunction = false;
    bool _isBegun = false;
    std::map<std::string, std::unique_ptr<Commands>> _commandsByNames;
};

int main() {
    std::string inputFile;
    std::cin >> inputFile;
    //  /Users/vadimleonov/Desktop/алгосы/virtual-cpu-tests/fibo
    std::ifstream input(inputFile);
    Virtual myCpu(&input);
    myCpu.start();
    return 0;
}