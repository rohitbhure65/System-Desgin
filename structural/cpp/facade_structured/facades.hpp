#pragma once
#include "subsystems.hpp"
#include <memory>

class ComputerFacade {
private:
    std::unique_ptr<CPU> cpu;
    std::unique_ptr<Memory> memory;
    std::unique_ptr<HardDrive> hardDrive;
public:
    ComputerFacade() : cpu(std::make_unique<CPU>()), memory(std::make_unique<Memory>()), hardDrive(std::make_unique<HardDrive>()) {}
    void start() {
        std::cout << "=== Starting Computer ===" << std::endl;
        cpu->freeze();
        memory->load(0, hardDrive->read(0, 1024));
        cpu->jump(0);
        cpu->execute();
        std::cout << "=== Computer Started ===" << std::endl;
    }
    void shutdown() {
        std::cout << "=== Shutting Down Computer ===" << std::endl;
        std::cout << "CPU: Stopping..." << std::endl;
        std::cout << "Memory: Clearing..." << std::endl;
        std::cout << "HardDrive: Spinning down..." << std::endl;
        std::cout << "=== Computer Shutdown ===" << std::endl;
    }
};

class HomeTheaterFacade {
private:
    std::unique_ptr<Amplifier> amp;
    std::unique_ptr<Tuner> tuner;
    std::unique_ptr<DVDPlayer> dvd;
    std::unique_ptr<Projector> projector;
    std::unique_ptr<TheaterLights> lights;
    std::unique_ptr<Screen> screen;
    std::unique_ptr<PopcornPopper> popper;
public:
    HomeTheaterFacade() : amp(std::make_unique<Amplifier>()), tuner(std::make_unique<Tuner>()), dvd(std::make_unique<DVDPlayer>()), projector(std::make_unique<Projector>()), lights(std::make_unique<TheaterLights>()), screen(std::make_unique<Screen>()), popper(std::make_unique<PopcornPopper>()) {}
    void watchMovie(const std::string& movie) {
        std::cout << "\n=== Get ready to watch a movie ===" << std::endl;
        popper->on(); popper->pop();
        lights->dim(10);
        screen->down();
        projector->on(); projector->setInput("DVD");
        amp->on(); amp->setVolume(5);
        dvd->on(); dvd->play(movie);
        std::cout << "=== Movie is playing ===" << std::endl;
    }
    void endMovie() {
        std::cout << "\n=== Shutting movie theater down ===" << std::endl;
        popper->off(); lights->on(); screen->up();
        projector->off(); amp->off(); dvd->off();
        std::cout << "=== Movie theater shut down ===" << std::endl;
    }
    void listenToRadio(double frequency) {
        std::cout << "\n=== Tuning in to radio ===" << std::endl;
        amp->on(); amp->setVolume(5);
        tuner->on(); tuner->setFrequency(frequency);
        std::cout << "=== Radio is playing ===" << std::endl;
    }
    void turnOffRadio() {
        std::cout << "\n=== Shutting down radio ===" << std::endl;
        tuner->off(); amp->off();
        std::cout << "=== Radio turned off ===" << std::endl;
    }
};

class OrderFacade {
private:
    std::unique_ptr<InventorySystem> inventory;
    std::unique_ptr<PaymentSystem> payment;
    std::unique_ptr<ShippingSystem> shipping;
    std::unique_ptr<NotificationSystem> notification;
public:
    OrderFacade() : inventory(std::make_unique<InventorySystem>()), payment(std::make_unique<PaymentSystem>()), shipping(std::make_unique<ShippingSystem>()), notification(std::make_unique<NotificationSystem>()) {}
    bool placeOrder(const std::string& item, int quantity, double amount, const std::string& address, const std::string& email) {
        std::cout << "\n=== Processing Order ===" << std::endl;
        if (!inventory->checkInventory(item, quantity)) { std::cout << "Order failed: Item not in stock" << std::endl; return false; }
        if (!payment->processPayment(amount)) { std::cout << "Order failed: Payment declined" << std::endl; return false; }
        inventory->updateInventory(item, -quantity);
        shipping->scheduleShipping(address);
        notification->sendConfirmation(email);
        std::cout << "=== Order Placed Successfully ===" << std::endl;
        return true;
    }
    void cancelOrder(const std::string& item, int quantity, double amount, const std::string& email) {
        std::cout << "\n=== Cancelling Order ===" << std::endl;
        inventory->updateInventory(item, quantity);
        payment->refundPayment(amount);
        shipping->cancelShipping();
        notification->sendCancellation(email);
        std::cout << "=== Order Cancelled ===" << std::endl;
    }
};
