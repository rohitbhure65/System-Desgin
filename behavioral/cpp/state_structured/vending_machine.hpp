#pragma once
#include "interfaces.hpp"
#include <iostream>

class VendingMachine {
private:
    std::unique_ptr<State> currentState;
    int coinCount;
    int stockCount;
    
public:
    VendingMachine(int initialStock) : coinCount(0), stockCount(initialStock) {
        if (initialStock > 0) {
            currentState = std::make_unique<NoCoinState>(this);
        } else {
            currentState = std::make_unique<SoldOutState>(this);
        }
    }
    
    void setState(std::unique_ptr<State> state) {
        currentState = std::move(state);
    }
    
    void insertCoin() {
        currentState->insertCoin();
    }
    
    void ejectCoin() {
        currentState->ejectCoin();
    }
    
    void pressButton() {
        currentState->pressButton();
    }
    
    void dispense() {
        currentState->dispense();
    }
    
    void addCoin() {
        coinCount++;
        std::cout << "Coin inserted. Total coins: " << coinCount << std::endl;
    }
    
    void returnCoin() {
        if (coinCount > 0) {
            coinCount--;
            std::cout << "Coin returned. Total coins: " << coinCount << std::endl;
        }
    }
    
    void releaseProduct() {
        if (stockCount > 0) {
            stockCount--;
            coinCount--;
            std::cout << "Product dispensed. Stock: " << stockCount << ", Coins: " << coinCount << std::endl;
        }
    }
    
    int getCoinCount() const {
        return coinCount;
    }
    
    int getStockCount() const {
        return stockCount;
    }
};

class NoCoinState : public State {
private:
    VendingMachine* machine;
    
public:
    NoCoinState(VendingMachine* machine) : machine(machine) {}
    
    void insertCoin() override {
        std::cout << "Coin inserted..." << std::endl;
        machine->addCoin();
        machine->setState(std::make_unique<HasCoinState>(machine));
    }
    
    void ejectCoin() override {
        std::cout << "No coin to eject" << std::endl;
    }
    
    void pressButton() override {
        std::cout << "Please insert a coin first" << std::endl;
    }
    
    void dispense() override {
        std::cout << "Please insert a coin first" << std::endl;
    }
};

class HasCoinState : public State {
private:
    VendingMachine* machine;
    
public:
    HasCoinState(VendingMachine* machine) : machine(machine) {}
    
    void insertCoin() override {
        std::cout << "Coin already inserted" << std::endl;
    }
    
    void ejectCoin() override {
        std::cout << "Coin ejected" << std::endl;
        machine->returnCoin();
        machine->setState(std::make_unique<NoCoinState>(machine));
    }
    
    void pressButton() override {
        std::cout << "Button pressed..." << std::endl;
        if (machine->getStockCount() > 0) {
            machine->setState(std::make_unique<DispensingState>(machine));
            machine->dispense();
        } else {
            std::cout << "Out of stock" << std::endl;
            machine->setState(std::make_unique<SoldOutState>(machine));
        }
    }
    
    void dispense() override {
        std::cout << "Press button to dispense" << std::endl;
    }
};

class DispensingState : public State {
private:
    VendingMachine* machine;
    
public:
    DispensingState(VendingMachine* machine) : machine(machine) {}
    
    void insertCoin() override {
        std::cout << "Please wait, dispensing..." << std::endl;
    }
    
    void ejectCoin() override {
        std::cout << "Cannot eject during dispensing" << std::endl;
    }
    
    void pressButton() override {
        std::cout << "Already dispensing..." << std::endl;
    }
    
    void dispense() override {
        machine->releaseProduct();
        if (machine->getStockCount() > 0) {
            machine->setState(std::make_unique<NoCoinState>(machine));
        } else {
            machine->setState(std::make_unique<SoldOutState>(machine));
        }
    }
};

class SoldOutState : public State {
private:
    VendingMachine* machine;
    
public:
    SoldOutState(VendingMachine* machine) : machine(machine) {}
    
    void insertCoin() override {
        std::cout << "Cannot insert coin, machine is sold out" << std::endl;
    }
    
    void ejectCoin() override {
        std::cout << "Cannot eject, no coin inserted" << std::endl;
    }
    
    void pressButton() override {
        std::cout << "Machine is sold out" << std::endl;
    }
    
    void dispense() override {
        std::cout << "Machine is sold out" << std::endl;
    }
};
