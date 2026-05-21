#pragma once
#include <iostream>

class BypasableSingleton {
private:
    static BypasableSingleton* instance;
    BypasableSingleton() { std::cout << "BypasableSingleton: Instance created." << std::endl; }

public:
    static BypasableSingleton* getInstance() {
        if (!instance) instance = new BypasableSingleton();
        return instance;
    }

    friend class SingletonHacker;
};

BypasableSingleton* BypasableSingleton::instance = nullptr;

class SingletonHacker {
public:
    static BypasableSingleton* createNewInstance() {
        return new BypasableSingleton();
    }
};
