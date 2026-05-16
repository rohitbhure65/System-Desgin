/*
 * ADAPTER DESIGN PATTERN
 * 
 * WHAT IS IT?
 * The Adapter pattern allows objects with incompatible interfaces to collaborate. It acts as a bridge between two incompatible interfaces.
 * 
 * WHY DOES IT EXIST?
 * - When you want to use an existing class whose interface doesn't match the one you need
 * - When you want to create a reusable class that cooperates with unrelated classes with incompatible interfaces
 * - When you need to use several existing subclasses, but adapting each to match your interface would be impractical
 * 
 * WHEN TO USE IT?
 * - When you want to use a third-party class but its interface doesn't match your system's interface
 * - When you need to integrate new components into an existing system without modifying existing code
 * - When you want to reuse existing classes that have similar functionality but different interfaces
 * - Common use cases: integrating third-party libraries, legacy code integration, data format conversion
 * 
 * PROS:
 * - Single Responsibility Principle (separates conversion logic from business logic)
 * - Open/Closed Principle (introduce new adapters without modifying existing code)
 * - Allows incompatible classes to work together
 * - Improves code reusability
 * 
 * CONS:
 * - Increases overall code complexity
 * - Can introduce additional layers of indirection
 * - May not be suitable for simple cases where direct modification is easier
 * - Can make the code harder to understand due to multiple layers
 * 
 * REAL-WORLD ANALOGY:
 * Think of a power adapter when traveling abroad. Your device (client) expects a certain plug shape (target interface), but the wall outlet (adaptee) has a different shape. The adapter converts between the two, allowing your device to work with the foreign outlet without modifying either the device or the wall.
 */

#include <iostream>
#include <string>
#include <memory>

// Target Interface - the interface that the client expects
class MediaPlayer {
public:
    virtual ~MediaPlayer() = default;
    virtual void play(const std::string& audioType, const std::string& fileName) = 0;
};

// Adaptee - the class with an incompatible interface
class AdvancedMediaPlayer {
public:
    virtual ~AdvancedMediaPlayer() = default;
    
    void playVlc(const std::string& fileName) {
        std::cout << "Playing vlc file: " << fileName << std::endl;
    }
    
    void playMp4(const std::string& fileName) {
        std::cout << "Playing mp4 file: " << fileName << std::endl;
    }
};

// Adapter - makes the Adaptee's interface compatible with the Target interface
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

// Client - uses the Target interface
class AudioPlayer : public MediaPlayer {
private:
    std::unique_ptr<MediaAdapter> mediaAdapter;
    
public:
    void play(const std::string& audioType, const std::string& fileName) override {
        // Built-in support for mp3
        if (audioType == "mp3") {
            std::cout << "Playing mp3 file: " << fileName << std::endl;
        }
        // MediaAdapter provides support for other formats
        else if (audioType == "vlc" || audioType == "mp4") {
            mediaAdapter = std::make_unique<MediaAdapter>();
            mediaAdapter->play(audioType, fileName);
        } else {
            std::cout << "Invalid media. " << audioType << " format not supported" << std::endl;
        }
    }
};

// Example 2: Object Adapter vs Class Adapter
// This example shows a different scenario: payment processing

// Target Interface
class PaymentProcessor {
public:
    virtual ~PaymentProcessor() = default;
    virtual void processPayment(double amount) = 0;
};

// Adaptee - incompatible payment system
class StripePaymentSystem {
public:
    void makeStripePayment(double amount) {
        std::cout << "Processing $" << amount << " via Stripe" << std::endl;
    }
};

// Adaptee - another incompatible payment system
class PayPalPaymentSystem {
public:
    void sendPayPalRequest(double amount) {
        std::cout << "Processing $" << amount << " via PayPal" << std::endl;
    }
};

// Adapter for Stripe
class StripeAdapter : public PaymentProcessor {
private:
    StripePaymentSystem stripeSystem;
    
public:
    void processPayment(double amount) override {
        stripeSystem.makeStripePayment(amount);
    }
};

// Adapter for PayPal
class PayPalAdapter : public PaymentProcessor {
private:
    PayPalPaymentSystem payPalSystem;
    
public:
    void processPayment(double amount) override {
        payPalSystem.sendPayPalRequest(amount);
    }
};

// Example 3: Two-way Adapter
// Allows both interfaces to work with each other

// Interface A
class CelsiusTemperature {
public:
    virtual ~CelsiusTemperature() = default;
    virtual double getTemperatureInCelsius() = 0;
    virtual void setTemperatureInCelsius(double temp) = 0;
};

// Interface B
class FahrenheitTemperature {
public:
    virtual ~FahrenheitTemperature() = default;
    virtual double getTemperatureInFahrenheit() = 0;
    virtual void setTemperatureInFahrenheit(double temp) = 0;
};

// Two-way adapter
class TemperatureAdapter : public CelsiusTemperature, public FahrenheitTemperature {
private:
    double temperatureInCelsius;
    
public:
    TemperatureAdapter(double temp = 0.0) : temperatureInCelsius(temp) {}
    
    // Celsius interface implementation
    double getTemperatureInCelsius() override {
        return temperatureInCelsius;
    }
    
    void setTemperatureInCelsius(double temp) override {
        temperatureInCelsius = temp;
    }
    
    // Fahrenheit interface implementation
    double getTemperatureInFahrenheit() override {
        return (temperatureInCelsius * 9.0 / 5.0) + 32.0;
    }
    
    void setTemperatureInFahrenheit(double temp) override {
        temperatureInCelsius = (temp - 32.0) * 5.0 / 9.0;
    }
};

int main() {
    std::cout << "=== Adapter Pattern Demo ===" << std::endl << std::endl;
    
    // Example 1: Media Player Adapter
    std::cout << "--- Media Player Adapter ---" << std::endl;
    
    AudioPlayer audioPlayer;
    
    audioPlayer.play("mp3", "beyond the horizon.mp3");
    audioPlayer.play("mp4", "alone again.mp4");
    audioPlayer.play("vlc", "far far away.vlc");
    audioPlayer.play("avi", "mind me.avi");
    
    std::cout << std::endl;
    
    // Example 2: Payment Processing Adapter
    std::cout << "--- Payment Processing Adapter ---" << std::endl;
    
    std::unique_ptr<PaymentProcessor> stripeAdapter = std::make_unique<StripeAdapter>();
    stripeAdapter->processPayment(100.50);
    
    std::unique_ptr<PaymentProcessor> payPalAdapter = std::make_unique<PayPalAdapter>();
    payPalAdapter->processPayment(75.25);
    
    std::cout << std::endl;
    
    // Example 3: Two-way Temperature Adapter
    std::cout << "--- Two-way Temperature Adapter ---" << std::endl;
    
    TemperatureAdapter tempAdapter;
    
    // Set using Celsius interface
    tempAdapter.setTemperatureInCelsius(25.0);
    std::cout << "Temperature in Celsius: " << tempAdapter.getTemperatureInCelsius() << "°C" << std::endl;
    std::cout << "Temperature in Fahrenheit: " << tempAdapter.getTemperatureInFahrenheit() << "°F" << std::endl;
    
    // Set using Fahrenheit interface
    tempAdapter.setTemperatureInFahrenheit(77.0);
    std::cout << "\nTemperature in Celsius: " << tempAdapter.getTemperatureInCelsius() << "°C" << std::endl;
    std::cout << "Temperature in Fahrenheit: " << tempAdapter.getTemperatureInFahrenheit() << "°F" << std::endl;
    
    return 0;
}
