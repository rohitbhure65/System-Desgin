#pragma once
#include "interfaces.hpp"
#include <vector>
#include <stack>

class RemoteControl {
private:
    std::vector<std::shared_ptr<Command>> commandHistory;
    std::stack<std::shared_ptr<Command>> undoStack;
    
public:
    void setCommand(std::shared_ptr<Command> command) {
        commandHistory.push_back(command);
    }
    
    void buttonPressed(size_t slot) {
        if (slot < commandHistory.size()) {
            commandHistory[slot]->execute();
            undoStack.push(commandHistory[slot]);
        }
    }
    
    void undoButtonPressed() {
        if (!undoStack.empty()) {
            undoStack.top()->undo();
            undoStack.pop();
        } else {
            std::cout << "Nothing to undo" << std::endl;
        }
    }
};
