#pragma once
#include <iostream>
#include <string>

class CPU {
public:
    void freeze() { std::cout << "CPU: Freezing..." << std::endl; }
    void jump(long position) { std::cout << "CPU: Jumping to position " << position << std::endl; }
    void execute() { std::cout << "CPU: Executing instructions..." << std::endl; }
};

class Memory {
public:
    void load(long position, std::string data) {
        std::cout << "Memory: Loading data '" << data << "' at position " << position << std::endl;
    }
};

class HardDrive {
public:
    std::string read(long lba, int size) {
        std::cout << "HardDrive: Reading " << size << " bytes from LBA " << lba << std::endl;
        return "Boot Data";
    }
};

class Amplifier {
public:
    void on() { std::cout << "Amplifier: ON" << std::endl; }
    void off() { std::cout << "Amplifier: OFF" << std::endl; }
    void setVolume(int level) { std::cout << "Amplifier: Volume set to " << level << std::endl; }
};

class Tuner {
public:
    void on() { std::cout << "Tuner: ON" << std::endl; }
    void off() { std::cout << "Tuner: OFF" << std::endl; }
    void setFrequency(double freq) { std::cout << "Tuner: Frequency set to " << freq << " FM" << std::endl; }
};

class DVDPlayer {
public:
    void on() { std::cout << "DVD Player: ON" << std::endl; }
    void off() { std::cout << "DVD Player: OFF" << std::endl; }
    void play(const std::string& movie) { std::cout << "DVD Player: Playing '" << movie << "'" << std::endl; }
};

class Projector {
public:
    void on() { std::cout << "Projector: ON" << std::endl; }
    void off() { std::cout << "Projector: OFF" << std::endl; }
    void setInput(const std::string& input) { std::cout << "Projector: Input set to " << input << std::endl; }
};

class TheaterLights {
public:
    void on() { std::cout << "Theater Lights: ON" << std::endl; }
    void off() { std::cout << "Theater Lights: OFF" << std::endl; }
    void dim(int level) { std::cout << "Theater Lights: Dimmed to " << level << "%" << std::endl; }
};

class Screen {
public:
    void up() { std::cout << "Screen: UP" << std::endl; }
    void down() { std::cout << "Screen: DOWN" << std::endl; }
};

class PopcornPopper {
public:
    void on() { std::cout << "Popcorn Popper: ON" << std::endl; }
    void off() { std::cout << "Popcorn Popper: OFF" << std::endl; }
    void pop() { std::cout << "Popcorn Popper: Popping popcorn!" << std::endl; }
};

class InventorySystem {
public:
    bool checkInventory(const std::string& item, int quantity) {
        std::cout << "Inventory: Checking " << quantity << " units of " << item << std::endl;
        return true;
    }
    void updateInventory(const std::string& item, int quantity) {
        std::cout << "Inventory: Updating " << quantity << " units of " << item << std::endl;
    }
};

class PaymentSystem {
public:
    bool processPayment(double amount) {
        std::cout << "Payment: Processing payment of $" << amount << std::endl;
        return true;
    }
    void refundPayment(double amount) {
        std::cout << "Payment: Refunding $" << amount << std::endl;
    }
};

class ShippingSystem {
public:
    void scheduleShipping(const std::string& address) {
        std::cout << "Shipping: Scheduling delivery to " << address << std::endl;
    }
    void cancelShipping() {
        std::cout << "Shipping: Cancelling delivery" << std::endl;
    }
};

class NotificationSystem {
public:
    void sendConfirmation(const std::string& email) {
        std::cout << "Notification: Sending confirmation to " << email << std::endl;
    }
    void sendCancellation(const std::string& email) {
        std::cout << "Notification: Sending cancellation to " << email << std::endl;
    }
};
