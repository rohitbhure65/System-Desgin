/*
 * BRIDGE DESIGN PATTERN
 * 
 * WHAT IS IT?
 * The Bridge pattern separates abstraction from implementation so that both can vary independently.
 * It uses composition instead of inheritance to decouple the abstraction from its implementation.
 * 
 * WHY DOES IT EXIST?
 * - When you want to avoid a permanent binding between an abstraction and its implementation
 * - When both the abstraction and the implementation should be extensible by subclassing
 * - When changes in the implementation should not affect clients
 * - When you have a class hierarchy that explodes due to combining multiple dimensions
 * 
 * WHEN TO USE IT?
 * - When you want to split a monolithic class that has several variants of some functionality
 * - When you need to extend a class in several independent dimensions
 * - When you want to be able to switch implementations at runtime
 * - Common use cases: UI frameworks (different controls on different platforms), shape rendering, device drivers
 * 
 * PROS:
 * - Separates abstraction from implementation
 * - Improves extensibility (can extend abstractions and implementations independently)
 * - Hides implementation details from clients
 * - Reduces the number of subclasses needed (avoids combinatorial explosion)
 * 
 * CONS:
 * - Increases code complexity
 * - May require additional indirection
 * - Can make the code harder to understand initially
 * - Might be overkill for simple scenarios
 * 
 * REAL-WORLD ANALOGY:
 * Think of a TV remote control (abstraction) and the TV itself (implementation). The remote control doesn't need to know the internal workings of the TV. You can use the same remote with different TV brands, and different remotes with the same TV. The remote (abstraction) is bridged to the TV (implementation) through a standard interface (infrared signals).
 */

#include <iostream>
#include <string>
#include <memory>

// Implementation Interface - defines the operations for all concrete implementations
class DrawingAPI {
public:
    virtual ~DrawingAPI() = default;
    virtual void drawCircle(double x, double y, double radius) = 0;
    virtual void drawRectangle(double x, double y, double width, double height) = 0;
};

// Concrete Implementation 1: Red Circle API
class RedCircleAPI : public DrawingAPI {
public:
    void drawCircle(double x, double y, double radius) override {
        std::cout << "Drawing Circle [color: red, center: (" << x << ", " << y 
                  << "), radius: " << radius << "]" << std::endl;
    }
    
    void drawRectangle(double x, double y, double width, double height) override {
        std::cout << "Drawing Rectangle [color: red, top-left: (" << x << ", " << y 
                  << "), width: " << width << ", height: " << height << "]" << std::endl;
    }
};

// Concrete Implementation 2: Green Circle API
class GreenCircleAPI : public DrawingAPI {
public:
    void drawCircle(double x, double y, double radius) override {
        std::cout << "Drawing Circle [color: green, center: (" << x << ", " << y 
                  << "), radius: " << radius << "]" << std::endl;
    }
    
    void drawRectangle(double x, double y, double width, double height) override {
        std::cout << "Drawing Rectangle [color: green, top-left: (" << x << ", " << y 
                  << "), width: " << width << ", height: " << height << "]" << std::endl;
    }
};

// Abstraction - defines the abstraction's interface and maintains a reference to an implementation
class Shape {
protected:
    std::unique_ptr<DrawingAPI> drawingAPI;
    
public:
    Shape(std::unique_ptr<DrawingAPI> api) : drawingAPI(std::move(api)) {}
    virtual ~Shape() = default;
    virtual void draw() = 0;
    virtual void resize(double percentage) = 0;
};

// Refined Abstraction 1: Circle
class Circle : public Shape {
private:
    double x, y, radius;
    
public:
    Circle(double x, double y, double radius, std::unique_ptr<DrawingAPI> api)
        : Shape(std::move(api)), x(x), y(y), radius(radius) {}
    
    void draw() override {
        drawingAPI->drawCircle(x, y, radius);
    }
    
    void resize(double percentage) override {
        radius *= percentage / 100.0;
        std::cout << "Resizing circle to " << radius << " radius" << std::endl;
    }
};

// Refined Abstraction 2: Rectangle
class Rectangle : public Shape {
private:
    double x, y, width, height;
    
public:
    Rectangle(double x, double y, double width, double height, std::unique_ptr<DrawingAPI> api)
        : Shape(std::move(api)), x(x), y(y), width(width), height(height) {}
    
    void draw() override {
        drawingAPI->drawRectangle(x, y, width, height);
    }
    
    void resize(double percentage) override {
        width *= percentage / 100.0;
        height *= percentage / 100.0;
        std::cout << "Resizing rectangle to " << width << "x" << height << std::endl;
    }
};

// Example 2: Device and Remote Control Bridge
// This shows how the Bridge pattern can be used for device control

// Implementation Interface
class Device {
public:
    virtual ~Device() = default;
    virtual void turnOn() = 0;
    virtual void turnOff() = 0;
    virtual void setVolume(int volume) = 0;
    virtual int getVolume() = 0;
};

// Concrete Implementation 1: TV
class Television : public Device {
private:
    bool on = false;
    int volume = 10;
    
public:
    void turnOn() override {
        on = true;
        std::cout << "TV is now ON" << std::endl;
    }
    
    void turnOff() override {
        on = false;
        std::cout << "TV is now OFF" << std::endl;
    }
    
    void setVolume(int volume) override {
        if (on) {
            this->volume = volume;
            std::cout << "TV volume set to " << volume << std::endl;
        } else {
            std::cout << "Cannot set volume: TV is OFF" << std::endl;
        }
    }
    
    int getVolume() override {
        return volume;
    }
};

// Concrete Implementation 2: Radio
class Radio : public Device {
private:
    bool on = false;
    int volume = 5;
    
public:
    void turnOn() override {
        on = true;
        std::cout << "Radio is now ON" << std::endl;
    }
    
    void turnOff() override {
        on = false;
        std::cout << "Radio is now OFF" << std::endl;
    }
    
    void setVolume(int volume) override {
        if (on) {
            this->volume = volume;
            std::cout << "Radio volume set to " << volume << std::endl;
        } else {
            std::cout << "Cannot set volume: Radio is OFF" << std::endl;
        }
    }
    
    int getVolume() override {
        return volume;
    }
};

// Abstraction: Remote Control
class RemoteControl {
protected:
    std::unique_ptr<Device> device;
    
public:
    RemoteControl(std::unique_ptr<Device> device) : device(std::move(device)) {}
    virtual ~RemoteControl() = default;
    
    virtual void togglePower() {
        if (device->getVolume() >= 0) {  // Simple check if device is "on"
            device->turnOff();
        } else {
            device->turnOn();
        }
    }
    
    virtual void volumeUp() {
        int currentVolume = device->getVolume();
        device->setVolume(currentVolume + 1);
    }
    
    virtual void volumeDown() {
        int currentVolume = device->getVolume();
        device->setVolume(currentVolume - 1);
    }
};

// Refined Abstraction: Advanced Remote Control
class AdvancedRemoteControl : public RemoteControl {
public:
    AdvancedRemoteControl(std::unique_ptr<Device> device) : RemoteControl(std::move(device)) {}
    
    void mute() {
        std::cout << "Muting device" << std::endl;
        device->setVolume(0);
    }
};

int main() {
    std::cout << "=== Bridge Pattern Demo ===" << std::endl << std::endl;
    
    // Example 1: Shape Drawing Bridge
    std::cout << "--- Shape Drawing Bridge ---" << std::endl;
    
    auto redCircle = std::make_unique<Circle>(100, 100, 10, std::make_unique<RedCircleAPI>());
    auto greenCircle = std::make_unique<Circle>(100, 100, 10, std::make_unique<GreenCircleAPI>());
    
    redCircle->draw();
    greenCircle->draw();
    
    auto redRectangle = std::make_unique<Rectangle>(50, 50, 20, 30, std::make_unique<RedCircleAPI>());
    auto greenRectangle = std::make_unique<Rectangle>(50, 50, 20, 30, std::make_unique<GreenCircleAPI>());
    
    redRectangle->draw();
    greenRectangle->draw();
    
    std::cout << "\nResizing shapes:" << std::endl;
    redCircle->resize(150);
    redCircle->draw();
    
    std::cout << std::endl;
    
    // Example 2: Device and Remote Control Bridge
    std::cout << "--- Device and Remote Control Bridge ---" << std::endl;
    
    auto tv = std::make_unique<Television>();
    auto tvRemote = std::make_unique<RemoteControl>(std::move(tv));
    
    std::cout << "\nControlling TV with basic remote:" << std::endl;
    tvRemote->togglePower();
    tvRemote->volumeUp();
    tvRemote->volumeUp();
    tvRemote->volumeDown();
    tvRemote->togglePower();
    
    auto radio = std::make_unique<Radio>();
    auto advancedRemote = std::make_unique<AdvancedRemoteControl>(std::move(radio));
    
    std::cout << "\nControlling Radio with advanced remote:" << std::endl;
    advancedRemote->togglePower();
    advancedRemote->volumeUp();
    advancedRemote->mute();
    advancedRemote->togglePower();
    
    return 0;
}
