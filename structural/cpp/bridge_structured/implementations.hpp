#pragma once
#include "interfaces.hpp"
#include <iostream>

class RedCircleAPI : public DrawingAPI {
public:
    void drawCircle(double x, double y, double radius) override {
        std::cout << "Drawing Circle [color: red, center: (" << x << ", " << y << "), radius: " << radius << "]" << std::endl;
    }
    void drawRectangle(double x, double y, double width, double height) override {
        std::cout << "Drawing Rectangle [color: red, top-left: (" << x << ", " << y << "), width: " << width << ", height: " << height << "]" << std::endl;
    }
};

class GreenCircleAPI : public DrawingAPI {
public:
    void drawCircle(double x, double y, double radius) override {
        std::cout << "Drawing Circle [color: green, center: (" << x << ", " << y << "), radius: " << radius << "]" << std::endl;
    }
    void drawRectangle(double x, double y, double width, double height) override {
        std::cout << "Drawing Rectangle [color: green, top-left: (" << x << ", " << y << "), width: " << width << ", height: " << height << "]" << std::endl;
    }
};

class Television : public Device {
private:
    bool on = false;
    int volume = 10;
public:
    void turnOn() override { on = true; std::cout << "TV is now ON" << std::endl; }
    void turnOff() override { on = false; std::cout << "TV is now OFF" << std::endl; }
    void setVolume(int volume) override {
        if (on) {
            this->volume = volume;
            std::cout << "TV volume set to " << volume << std::endl;
        } else {
            std::cout << "Cannot set volume: TV is OFF" << std::endl;
        }
    }
    int getVolume() override { return volume; }
};

class Radio : public Device {
private:
    bool on = false;
    int volume = 5;
public:
    void turnOn() override { on = true; std::cout << "Radio is now ON" << std::endl; }
    void turnOff() override { on = false; std::cout << "Radio is now OFF" << std::endl; }
    void setVolume(int volume) override {
        if (on) {
            this->volume = volume;
            std::cout << "Radio volume set to " << volume << std::endl;
        } else {
            std::cout << "Cannot set volume: Radio is OFF" << std::endl;
        }
    }
    int getVolume() override { return volume; }
};
