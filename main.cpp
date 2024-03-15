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
        std::string cmd = std::string("");
        do {

            *_inputFile >> cmd;
            if (_commandsByNames.contains(cmd)) {
                _commandsByNames[cmd]->set(_inputFile);
                _commandsVector.push_back(std::make_unique<Commands>(*_commandsByNames[cmd]));
                //_commandsVector.push_back(std::make_unique<Begin>());
                ((_commandsVector[_commandsVector.size() - 1]))->method();
                if (cmd == std::string("BEGIN")) _isBegun = true;
                if (_isBegun) {
                    (_commandsByNames[cmd])->doit();
                }
            } else {
                cmd.pop_back();
                _labelsIndexes[cmd] = _commandsVector.size() - 1;
            }
        } while (cmd != std::string("END"));
        _commandsVector[0]->doit();
    }

    explicit Virtual(std::ifstream *input) {
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
        _commandsByNames["JMP"] = std::make_unique<Jmp>(&_commandsVector, &_labelsIndexes);
        _commandsByNames["JNE"] = std::make_unique<Jne>(&_commandsVector, &_labelsIndexes, &_stack, &_registers);
    }
private:
    std::ifstream *_inputFile = nullptr;
    Stack<size_t> _stack;
    Registers _registers;
    std::vector<std::unique_ptr<Commands>> _commandsVector;
    std::map<std::string , size_t> _labelsIndexes;
//    std::vector<int> _functionsIndexes;
//    bool _inFunction = false;
    bool _isBegun = false;
    std::map<std::string, std::unique_ptr<Commands>> _commandsByNames;
};

int main() {
    std::string inputFile("/Users/vadimleonov/Desktop/алгосы/virtual-cpu-tests/fibo");
//    std::cin >> inputFile;
//    /Users/vadimleonov/Desktop/алгосы/virtual-cpu-tests/fibo
    std::ifstream input(inputFile);
    Virtual myCpu(&input);
    myCpu.start();
    return 0;
}