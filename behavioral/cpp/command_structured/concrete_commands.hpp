#pragma once
#include "interfaces.hpp"
#include "receivers.hpp"

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
