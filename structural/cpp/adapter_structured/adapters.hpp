#pragma once
#include "interfaces.hpp"
#include "adaptees.hpp"
#include <memory>
#include <iostream>

class MediaAdapter : public MediaPlayer {
private:
    std::unique_ptr<AdvancedMediaPlayer> advancedMusicPlayer;
public:
    MediaAdapter() : advancedMusicPlayer(std::make_unique<AdvancedMediaPlayer>()) {}
    void play(const std::string& audioType, const std::string& fileName) override {
        if (audioType == "vlc") {
            advancedMusicPlayer->playVlc(fileName);
        } else if (audioType == "mp4") {
            advancedMusicPlayer->playMp4(fileName);
        } else {
            std::cout << "Invalid media. " << audioType << " format not supported" << std::endl;
        }
    }
};

class StripeAdapter : public PaymentProcessor {
private:
    StripePaymentSystem stripeSystem;
public:
    void processPayment(double amount) override { stripeSystem.makeStripePayment(amount); }
};

class PayPalAdapter : public PaymentProcessor {
private:
    PayPalPaymentSystem payPalSystem;
public:
    void processPayment(double amount) override { payPalSystem.sendPayPalRequest(amount); }
};

class TemperatureAdapter : public CelsiusTemperature, public FahrenheitTemperature {
private:
    double temperatureInCelsius;
public:
    TemperatureAdapter(double temp = 0.0) : temperatureInCelsius(temp) {}
    double getTemperatureInCelsius() override { return temperatureInCelsius; }
    void setTemperatureInCelsius(double temp) override { temperatureInCelsius = temp; }
    double getTemperatureInFahrenheit() override { return (temperatureInCelsius * 9.0 / 5.0) + 32.0; }
    void setTemperatureInFahrenheit(double temp) override { temperatureInCelsius = (temp - 32.0) * 5.0 / 9.0; }
};
