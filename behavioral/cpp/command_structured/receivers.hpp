#pragma once
#include <iostream>

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
