#pragma once
#include <iostream>
#include <mutex>

class SerializedSingleton {
private:
    static SerializedSingleton* instance;
    static std::mutex mutex;

    SerializedSingleton() { std::cout << "SerializedSingleton: Instance created." << std::endl; }

public:
    static SerializedSingleton* getInstance() {
        if (instance == nullptr) {
            std::lock_guard<std::mutex> lock(mutex);
            if (instance == nullptr) {
                instance = new SerializedSingleton();
            }
        }
        return instance;
    }
    
    void doWork() { std::cout << "SerializedSingleton is working..." << std::endl; }
};

SerializedSingleton* SerializedSingleton::instance = nullptr;
std::mutex SerializedSingleton::mutex;
