#pragma once
#include <iostream>
#include <string>

class AdvancedMediaPlayer {
public:
    virtual ~AdvancedMediaPlayer() = default;
    void playVlc(const std::string& fileName) { std::cout << "Playing vlc file: " << fileName << std::endl; }
    void playMp4(const std::string& fileName) { std::cout << "Playing mp4 file: " << fileName << std::endl; }
};

class StripePaymentSystem {
public:
    void makeStripePayment(double amount) { std::cout << "Processing $" << amount << " via Stripe" << std::endl; }
};

class PayPalPaymentSystem {
public:
    void sendPayPalRequest(double amount) { std::cout << "Processing $" << amount << " via PayPal" << std::endl; }
};
