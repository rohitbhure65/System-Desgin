/*
 * FACADE DESIGN PATTERN
 * 
 * WHAT IS IT?
 * The Facade pattern provides a simplified interface to a library, a framework, or any other complex set of classes.
 * It hides the complexities of the larger system and provides a simpler interface to the client.
 * 
 * WHY DOES IT EXIST?
 * - When you need to provide a simple interface to a complex subsystem
 * - When you want to reduce dependencies between clients and the implementation of an abstraction
 * - When you want to layer your subsystems (use facade to define entry points)
 * 
 * WHEN TO USE IT?
 * - When you have a complex system with many interacting classes
 * - When you want to provide a simple interface for clients to interact with the system
 * - When you want to decouple the client from the subsystem implementation
 * - Common use cases: API libraries, database operations, complex UI systems, payment processing
 * 
 * PROS:
 * - Simplifies the interface to a complex subsystem
 * - Decouples clients from the subsystem (reduces coupling)
 * - Makes the system easier to use and understand
 * - Promotes loose coupling between subsystems and clients
 * 
 * CONS:
 * - Can become a "god object" if not carefully designed
 * - May limit the flexibility of the subsystem
 * - Can hide useful functionality from advanced users
 * - Adds an extra layer of indirection
 * 
 * REAL-WORLD ANALOGY:
 * Think of a car dashboard. The dashboard (facade) provides a simple interface to the complex car systems (engine, transmission, brakes, etc.). You don't need to know how the engine works to drive the car - you just use the steering wheel, pedals, and dashboard controls. The dashboard hides the complexity while giving you access to the essential functions.
 */

#include <iostream>
#include <string>
#include <memory>

// Subsystem Class 1: CPU
class CPU {
public:
    void freeze() {
        std::cout << "CPU: Freezing..." << std::endl;
    }
    
    void jump(long position) {
        std::cout << "CPU: Jumping to position " << position << std::endl;
    }
    
    void execute() {
        std::cout << "CPU: Executing instructions..." << std::endl;
    }
};

// Subsystem Class 2: Memory
class Memory {
public:
    void load(long position, std::string data) {
        std::cout << "Memory: Loading data '" << data << "' at position " << position << std::endl;
    }
};

// Subsystem Class 3: Hard Drive
class HardDrive {
public:
    std::string read(long lba, int size) {
        std::cout << "HardDrive: Reading " << size << " bytes from LBA " << lba << std::endl;
        return "Boot Data";
    }
};

// Facade - provides a simplified interface to the complex subsystem
class ComputerFacade {
private:
    std::unique_ptr<CPU> cpu;
    std::unique_ptr<Memory> memory;
    std::unique_ptr<HardDrive> hardDrive;
    
public:
    ComputerFacade() 
        : cpu(std::make_unique<CPU>()),
          memory(std::make_unique<Memory>()),
          hardDrive(std::make_unique<HardDrive>()) {}
    
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

// Example 2: Home Theater System
// Shows how Facade can simplify controlling multiple devices

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

// Facade for Home Theater
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
    HomeTheaterFacade()
        : amp(std::make_unique<Amplifier>()),
          tuner(std::make_unique<Tuner>()),
          dvd(std::make_unique<DVDPlayer>()),
          projector(std::make_unique<Projector>()),
          lights(std::make_unique<TheaterLights>()),
          screen(std::make_unique<Screen>()),
          popper(std::make_unique<PopcornPopper>()) {}
    
    void watchMovie(const std::string& movie) {
        std::cout << "\n=== Get ready to watch a movie ===" << std::endl;
        popper->on();
        popper->pop();
        lights->dim(10);
        screen->down();
        projector->on();
        projector->setInput("DVD");
        amp->on();
        amp->setVolume(5);
        dvd->on();
        dvd->play(movie);
        std::cout << "=== Movie is playing ===" << std::endl;
    }
    
    void endMovie() {
        std::cout << "\n=== Shutting movie theater down ===" << std::endl;
        popper->off();
        lights->on();
        screen->up();
        projector->off();
        amp->off();
        dvd->off();
        std::cout << "=== Movie theater shut down ===" << std::endl;
    }
    
    void listenToRadio(double frequency) {
        std::cout << "\n=== Tuning in to radio ===" << std::endl;
        amp->on();
        amp->setVolume(5);
        tuner->on();
        tuner->setFrequency(frequency);
        std::cout << "=== Radio is playing ===" << std::endl;
    }
    
    void turnOffRadio() {
        std::cout << "\n=== Shutting down radio ===" << std::endl;
        tuner->off();
        amp->off();
        std::cout << "=== Radio turned off ===" << std::endl;
    }
};

// Example 3: Order Processing System
// Shows how Facade can simplify complex business logic

class InventorySystem {
public:
    bool checkInventory(const std::string& item, int quantity) {
        std::cout << "Inventory: Checking " << quantity << " units of " << item << std::endl;
        return true;  // Simplified for demo
    }
    
    void updateInventory(const std::string& item, int quantity) {
        std::cout << "Inventory: Updating " << quantity << " units of " << item << std::endl;
    }
};

class PaymentSystem {
public:
    bool processPayment(double amount) {
        std::cout << "Payment: Processing payment of $" << amount << std::endl;
        return true;  // Simplified for demo
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

// Facade for Order Processing
class OrderFacade {
private:
    std::unique_ptr<InventorySystem> inventory;
    std::unique_ptr<PaymentSystem> payment;
    std::unique_ptr<ShippingSystem> shipping;
    std::unique_ptr<NotificationSystem> notification;
    
public:
    OrderFacade()
        : inventory(std::make_unique<InventorySystem>()),
          payment(std::make_unique<PaymentSystem>()),
          shipping(std::make_unique<ShippingSystem>()),
          notification(std::make_unique<NotificationSystem>()) {}
    
    bool placeOrder(const std::string& item, int quantity, double amount, 
                   const std::string& address, const std::string& email) {
        std::cout << "\n=== Processing Order ===" << std::endl;
        
        if (!inventory->checkInventory(item, quantity)) {
            std::cout << "Order failed: Item not in stock" << std::endl;
            return false;
        }
        
        if (!payment->processPayment(amount)) {
            std::cout << "Order failed: Payment declined" << std::endl;
            return false;
        }
        
        inventory->updateInventory(item, -quantity);
        shipping->scheduleShipping(address);
        notification->sendConfirmation(email);
        
        std::cout << "=== Order Placed Successfully ===" << std::endl;
        return true;
    }
    
    void cancelOrder(const std::string& item, int quantity, double amount,
                    const std::string& email) {
        std::cout << "\n=== Cancelling Order ===" << std::endl;
        inventory->updateInventory(item, quantity);
        payment->refundPayment(amount);
        shipping->cancelShipping();
        notification->sendCancellation(email);
        std::cout << "=== Order Cancelled ===" << std::endl;
    }
};

int main() {
    std::cout << "=== Facade Pattern Demo ===" << std::endl << std::endl;
    
    // Example 1: Computer Boot
    std::cout << "--- Computer Boot Example ---" << std::endl;
    
    ComputerFacade computer;
    computer.start();
    std::cout << std::endl;
    computer.shutdown();
    
    std::cout << std::endl;
    
    // Example 2: Home Theater
    std::cout << "--- Home Theater Example ---" << std::endl;
    
    HomeTheaterFacade homeTheater;
    homeTheater.watchMovie("The Matrix");
    homeTheater.endMovie();
    homeTheater.listenToRadio(98.7);
    homeTheater.turnOffRadio();
    
    std::cout << std::endl;
    
    // Example 3: Order Processing
    std::cout << "--- Order Processing Example ---" << std::endl;
    
    OrderFacade orderSystem;
    orderSystem.placeOrder("Laptop", 1, 999.99, "123 Main St", "customer@email.com");
    orderSystem.cancelOrder("Laptop", 1, 999.99, "customer@email.com");
    
    return 0;
}
