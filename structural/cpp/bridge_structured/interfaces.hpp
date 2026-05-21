#pragma once

class DrawingAPI {
public:
    virtual ~DrawingAPI() = default;
    virtual void drawCircle(double x, double y, double radius) = 0;
    virtual void drawRectangle(double x, double y, double width, double height) = 0;
};

class Device {
public:
    virtual ~Device() = default;
    virtual void turnOn() = 0;
    virtual void turnOff() = 0;
    virtual void setVolume(int volume) = 0;
    virtual int getVolume() = 0;
};
