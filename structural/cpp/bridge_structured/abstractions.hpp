#pragma once
#include "interfaces.hpp"
#include <memory>
#include <iostream>

class Shape {
protected:
    std::unique_ptr<DrawingAPI> drawingAPI;
public:
    Shape(std::unique_ptr<DrawingAPI> api) : drawingAPI(std::move(api)) {}
    virtual ~Shape() = default;
    virtual void draw() = 0;
    virtual void resize(double percentage) = 0;
};

class Circle : public Shape {
private:
    double x, y, radius;
public:
    Circle(double x, double y, double radius, std::unique_ptr<DrawingAPI> api) : Shape(std::move(api)), x(x), y(y), radius(radius) {}
    void draw() override { drawingAPI->drawCircle(x, y, radius); }
    void resize(double percentage) override {
        radius *= percentage / 100.0;
        std::cout << "Resizing circle to " << radius << " radius" << std::endl;
    }
};

class Rectangle : public Shape {
private:
    double x, y, width, height;
public:
    Rectangle(double x, double y, double width, double height, std::unique_ptr<DrawingAPI> api) : Shape(std::move(api)), x(x), y(y), width(width), height(height) {}
    void draw() override { drawingAPI->drawRectangle(x, y, width, height); }
    void resize(double percentage) override {
        width *= percentage / 100.0;
        height *= percentage / 100.0;
        std::cout << "Resizing rectangle to " << width << "x" << height << std::endl;
    }
};

class RemoteControl {
protected:
    std::unique_ptr<Device> device;
public:
    RemoteControl(std::unique_ptr<Device> device) : device(std::move(device)) {}
    virtual ~RemoteControl() = default;
    virtual void togglePower() {
        if (device->getVolume() >= 0) { device->turnOff(); } else { device->turnOn(); }
    }
    virtual void volumeUp() { device->setVolume(device->getVolume() + 1); }
    virtual void volumeDown() { device->setVolume(device->getVolume() - 1); }
};

class AdvancedRemoteControl : public RemoteControl {
public:
    AdvancedRemoteControl(std::unique_ptr<Device> device) : RemoteControl(std::move(device)) {}
    void mute() {
        std::cout << "Muting device" << std::endl;
        device->setVolume(0);
    }
};
