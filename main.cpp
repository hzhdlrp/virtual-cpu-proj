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

    void setInputFile(std::ifstream *input) {
        _inputFile = input;
    }
    void setOutputFile(std::ofstream *output) {
        _outputFile = output;
    }

    void start(std::ifstream *input, std::ofstream *output) {
        setInputFile(input);
        setOutputFile(output);

    }
private:
    std::ifstream *_inputFile = nullptr;
    std::ofstream *_outputFile = nullptr;
    bool _begin = false;

    Stack<size_t> _stack;
    Registers registers;
    std::vector<std::string> _commandsNamesStack;
    std::map<std::string, std::unique_ptr<Commands>> _commandsByNames = {
            {"BEGIN", std::make_unique<Begin>()},
            {"END", std::make_unique<End>()},
            {"PUSH", std::make_unique<Push>(_inputFile, &_stack)},
            {"PUSHR", std::make_unique<Pushr>(_inputFile, &_stack, &registers)},
            {"POP", std::make_unique<Pop>(&_stack)},

    };
};
int main() {
    return 0;
}