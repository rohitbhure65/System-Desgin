/*
 * COMMAND DESIGN PATTERN
 * 
 * WHAT IS IT?
 * The Command pattern turns a request into a stand-alone object that contains all information about the request.
 * It lets you parameterize clients with different requests, queue or log requests, and support undoable operations.
 * 
 * WHY DOES IT EXIST?
 * - When you want to parameterize objects with operations
 * - When you want to queue operations, schedule their execution, or execute them remotely
 * - When you need to support undo operations
 * - When you want to decouple the object that invokes an operation from the one that knows how to perform it
 * 
 * WHEN TO USE IT?
 * - When you want to parameterize objects with an operation to execute
 * - When you want to queue operations, schedule their execution, or execute them remotely
 * - When you need to support undo/redo functionality
 * - When you want to decouple the invoker from the receiver
 * - Common use cases: GUI buttons and menus, multi-level undo, macro recording, transactional systems
 * 
 * PROS:
 * - Decouples the object that invokes the operation from the one that knows how to perform it
 * - Can add new commands without changing existing code (Open/Closed Principle)
 * - Allows you to assemble commands into more complex commands (composite pattern)
 * - Supports undo/redo operations
 * 
 * CONS:
 * - Can lead to many small command classes (code complexity)
 * - Can complicate the code if the receiver and command are tightly coupled
 * - May introduce additional layers of indirection
 * - Can make debugging more difficult
 * 
 * REAL-WORLD ANALOGY:
 * Think of a restaurant order. The customer (client) places an order (command) with the waiter (invoker). The waiter writes down the order and gives it to the kitchen (receiver). The kitchen executes the command (prepares the meal). The order can be cancelled (undo) before it's prepared, and multiple orders can be queued.
 */

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <stack>

// Receiver - knows how to perform the operations
class Light {
public:
    void on() {
        std::cout << "Light is ON" << std::endl;
    }
    
    void off() {
        std::cout << "Light is OFF" << std::endl;
    }
};

class Stereo {
public:
    void on() {
        std::cout << "Stereo is ON" << std::endl;
    }
    
    void off() {
        std::cout << "Stereo is OFF" << std::endl;
    }
    
    void setVolume(int level) {
        std::cout << "Stereo volume set to " << level << std::endl;
    }
};

// Command interface - declares the execute method
class Command {
public:
    virtual ~Command() = default;
    virtual void execute() = 0;
    virtual void undo() = 0;
};

// Concrete Command 1: Light On
class LightOnCommand : public Command {
private:
    Light& light;
    
public:
    LightOnCommand(Light& light) : light(light) {}
    
    void execute() override {
        light.on();
    }
    
    void undo() override {
        light.off();
    }
};

// Concrete Command 2: Light Off
class LightOffCommand : public Command {
private:
    Light& light;
    
public:
    LightOffCommand(Light& light) : light(light) {}
    
    void execute() override {
        light.off();
    }
    
    void undo() override {
        light.on();
    }
};

// Concrete Command 3: Stereo On with Volume
class StereoOnCommand : public Command {
private:
    Stereo& stereo;
    int previousVolume;
    
public:
    StereoOnCommand(Stereo& stereo) : stereo(stereo), previousVolume(0) {}
    
    void execute() override {
        stereo.on();
        stereo.setVolume(10);
        previousVolume = 10;
    }
    
    void undo() override {
        stereo.setVolume(previousVolume);
        stereo.off();
    }
};

// Concrete Command 4: Stereo Off
class StereoOffCommand : public Command {
private:
    Stereo& stereo;
    
public:
    StereoOffCommand(Stereo& stereo) : stereo(stereo) {}
    
    void execute() override {
        stereo.off();
    }
    
    void undo() override {
        stereo.on();
    }
};

// Invoker - asks the command to carry out the request
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

// Example 2: Macro Command
// Shows how multiple commands can be combined into one

class MacroCommand : public Command {
private:
    std::vector<std::shared_ptr<Command>> commands;
    
public:
    void addCommand(std::shared_ptr<Command> command) {
        commands.push_back(command);
    }
    
    void execute() override {
        for (const auto& command : commands) {
            command->execute();
        }
    }
    
    void undo() override {
        // Undo in reverse order
        for (auto it = commands.rbegin(); it != commands.rend(); ++it) {
            (*it)->undo();
        }
    }
};

// Example 3: Transaction Command
// Shows how Command can be used for transactional operations

class BankAccount {
private:
    double balance;
    
public:
    BankAccount(double initialBalance = 0) : balance(initialBalance) {}
    
    void deposit(double amount) {
        balance += amount;
        std::cout << "Deposited $" << amount << ". New balance: $" << balance << std::endl;
    }
    
    void withdraw(double amount) {
        if (balance >= amount) {
            balance -= amount;
            std::cout << "Withdrew $" << amount << ". New balance: $" << balance << std::endl;
        } else {
            std::cout << "Insufficient funds" << std::endl;
        }
    }
    
    double getBalance() const {
        return balance;
    }
};

class DepositCommand : public Command {
private:
    BankAccount& account;
    double amount;
    
public:
    DepositCommand(BankAccount& account, double amount) 
        : account(account), amount(amount) {}
    
    void execute() override {
        account.deposit(amount);
    }
    
    void undo() override {
        account.withdraw(amount);
    }
};

class WithdrawCommand : public Command {
private:
    BankAccount& account;
    double amount;
    bool success;
    
public:
    WithdrawCommand(BankAccount& account, double amount) 
        : account(account), amount(amount), success(false) {}
    
    void execute() override {
        double oldBalance = account.getBalance();
        account.withdraw(amount);
        success = (account.getBalance() < oldBalance);
    }
    
    void undo() override {
        if (success) {
            account.deposit(amount);
        }
    }
};

int main() {
    std::cout << "=== Command Pattern Demo ===" << std::endl << std::endl;
    
    // Example 1: Remote Control
    std::cout << "--- Remote Control Example ---" << std::endl;
    
    Light livingRoomLight;
    Stereo livingRoomStereo;
    
    auto lightOn = std::make_shared<LightOnCommand>(livingRoomLight);
    auto lightOff = std::make_shared<LightOffCommand>(livingRoomLight);
    auto stereoOn = std::make_shared<StereoOnCommand>(livingRoomStereo);
    auto stereoOff = std::make_shared<StereoOffCommand>(livingRoomStereo);
    
    RemoteControl remote;
    remote.setCommand(lightOn);
    remote.setCommand(lightOff);
    remote.setCommand(stereoOn);
    remote.setCommand(stereoOff);
    
    std::cout << "\nTurning on light (slot 0):" << std::endl;
    remote.buttonPressed(0);
    
    std::cout << "\nTurning on stereo (slot 2):" << std::endl;
    remote.buttonPressed(2);
    
    std::cout << "\nUndo last action:" << std::endl;
    remote.undoButtonPressed();
    
    std::cout << "\nTurning off light (slot 1):" << std::endl;
    remote.buttonPressed(1);
    
    std::cout << "\nUndo last action:" << std::endl;
    remote.undoButtonPressed();
    
    std::cout << std::endl;
    
    // Example 2: Macro Command
    std::cout << "--- Macro Command Example ---" << std::endl;
    
    auto partyMode = std::make_shared<MacroCommand>();
    partyMode->addCommand(lightOn);
    partyMode->addCommand(stereoOn);
    
    auto shutdownMode = std::make_shared<MacroCommand>();
    shutdownMode->addCommand(stereoOff);
    shutdownMode->addCommand(lightOff);
    
    std::cout << "\nActivating party mode:" << std::endl;
    partyMode->execute();
    
    std::cout << "\nActivating shutdown mode:" << std::endl;
    shutdownMode->execute();
    
    std::cout << "\nUndo shutdown:" << std::endl;
    shutdownMode->undo();
    
    std::cout << std::endl;
    
    // Example 3: Transaction Command
    std::cout << "--- Transaction Command Example ---" << std::endl;
    
    BankAccount myAccount(1000);
    
    std::cout << "\nInitial balance: $" << myAccount.getBalance() << std::endl;
    
    auto deposit = std::make_shared<DepositCommand>(myAccount, 500);
    auto withdraw = std::make_shared<WithdrawCommand>(myAccount, 200);
    
    std::cout << "\nExecuting deposit:" << std::endl;
    deposit->execute();
    
    std::cout << "\nExecuting withdrawal:" << std::endl;
    withdraw->execute();
    
    std::cout << "\nUndo withdrawal:" << std::endl;
    withdraw->undo();
    
    std::cout << "\nFinal balance: $" << myAccount.getBalance() << std::endl;
    
    return 0;
}
