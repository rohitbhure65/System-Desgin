#pragma once
#include <string>

class MediaPlayer {
public:
    virtual ~MediaPlayer() = default;
    virtual void play(const std::string& audioType, const std::string& fileName) = 0;
};

class PaymentProcessor {
public:
    virtual ~PaymentProcessor() = default;
    virtual void processPayment(double amount) = 0;
};

class CelsiusTemperature {
public:
    virtual ~CelsiusTemperature() = default;
    virtual double getTemperatureInCelsius() = 0;
    virtual void setTemperatureInCelsius(double temp) = 0;
};

class FahrenheitTemperature {
public:
    virtual ~FahrenheitTemperature() = default;
    virtual double getTemperatureInFahrenheit() = 0;
    virtual void setTemperatureInFahrenheit(double temp) = 0;
};
