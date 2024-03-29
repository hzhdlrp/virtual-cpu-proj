#ifndef PROJECT2_COMPILATION_H
#define PROJECT2_COMPILATION_H

#endif //PROJECT2_COMPILATION_H

#include "Stack.hpp"
#include <fstream>
#include <memory>
#include <vector>
#include <map>
#include <functional>
#include "commands.hpp"

class Virtual {
public:
    void read() {
        std::string cmd = std::string("");
        int i = 0;
        while (!_inputFile->eof()) {
            *_inputFile >> cmd;
            if (_commandsByNames.contains(cmd)) {
                _commandsVector.push_back(_commandsByNames[cmd]());
                if (cmd == "BEGIN") {
                    _labelsIndexes[cmd] = _commandsVector.size() - 1;
                }
                if (cmd == "CALL") {
                    _commandsVector[_commandsVector.size() - 1]->setIndex(i);
                }
                _commandsVector[_commandsVector.size() - 1]->set(_inputFile);
            } else {
                cmd.pop_back();
                _labelsIndexes[cmd] = _commandsVector.size();
                --i;
            }
            ++i;
        }
        _commandsVector.pop_back();
    }

    void execute() {
        size_t i = _labelsIndexes["BEGIN"];
        while (i < _commandsVector.size()) {
            _commandsVector[i]->doit(&i);
            ++i;
        }
    }

    explicit Virtual(std::ifstream *input) {
        if (!input) throw std::runtime_error("null on input stream");
        _inputFile = input;
        _commandsByNames["BEGIN"] = [](){return std::make_unique<Begin>();};
        _commandsByNames["END"] = []() {return std::make_unique<End>();};
        _commandsByNames["PUSH"] = [&]() {return std::make_unique<Push>(&_stack);};
        _commandsByNames["PUSHR"] = [&]() {return std::make_unique<Pushr>(&_stack, &_registers);};
        _commandsByNames["POP"] = [&]() {return std::make_unique<Pop>(&_stack);};
        _commandsByNames["POPR"] =  [&]() {return std::make_unique<Popr>(&_stack, &_registers);};
        _commandsByNames["ADD"] = [&]() {return std::make_unique<Add>(&_stack, &_registers);};
        _commandsByNames["SUB"] = [&]() {return std::make_unique<Sub>(&_stack, &_registers);};
        _commandsByNames["MUL"] = [&]() {return std::make_unique<Mul>(&_stack, &_registers);};
        _commandsByNames["DIV"] = [&]() {return std::make_unique<Div>(&_stack, &_registers);};
        _commandsByNames["OUT"] = [&]() {return std::make_unique<Out>(&_stack);};
        _commandsByNames["IN"] = [&]() {return std::make_unique<In>( &_stack);};
        _commandsByNames["JMP"] = [&]() {return std::make_unique<Jmp>(&_commandsVector, &_labelsIndexes);};
        _commandsByNames["JNE"] = [&]() {return std::make_unique<Jne>(&_commandsVector, &_labelsIndexes, &_stack, &_registers);};
        _commandsByNames["JEQ"] = [&]() {return std::make_unique<Jeq>(&_commandsVector, &_labelsIndexes, &_stack, &_registers);};
        _commandsByNames["JA"] = [&]() {return std::make_unique<Ja>(&_commandsVector, &_labelsIndexes, &_stack, &_registers);};
        _commandsByNames["JAE"] = [&]() {return std::make_unique<Jae>(&_commandsVector, &_labelsIndexes, &_stack, &_registers);};
        _commandsByNames["JB"] = [&]() {return std::make_unique<Jb>(&_commandsVector, &_labelsIndexes, &_stack, &_registers);};
        _commandsByNames["JBE"] = [&]() {return std::make_unique<Jbe>(&_commandsVector, &_labelsIndexes, &_stack, &_registers);};
        _commandsByNames["CALL"] = [&]() {return std::make_unique<Call>(&_commandsVector, &_labelsIndexes, &_callsIndexes);};
        _commandsByNames["RET"] = [&]() {return std::make_unique<Ret>(&_commandsVector, &_labelsIndexes, &_callsIndexes);};

    }
private:
    std::ifstream *_inputFile = nullptr;
    Stack<size_t> _stack;
    Registers _registers;
    std::vector<std::unique_ptr<Commands>> _commandsVector;
    std::map<std::string , size_t> _labelsIndexes;
    std::map<std::string, std::function<std::unique_ptr<Commands>()>> _commandsByNames;
    std::vector<size_t> _callsIndexes;
};
