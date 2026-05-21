#include "interfaces.hpp"
#include "adapters.hpp"
#include "client.hpp"
#include <iostream>

int main() {
    std::cout << "=== Adapter Pattern Demo ===" << std::endl << std::endl;
    
    std::cout << "--- Media Player Adapter ---" << std::endl;
    AudioPlayer audioPlayer;
    audioPlayer.play("mp3", "beyond the horizon.mp3");
    audioPlayer.play("mp4", "alone again.mp4");
    audioPlayer.play("vlc", "far far away.vlc");
    audioPlayer.play("avi", "mind me.avi");
    std::cout << std::endl;
    
    std::cout << "--- Payment Processing Adapter ---" << std::endl;
    std::unique_ptr<PaymentProcessor> stripeAdapter = std::make_unique<StripeAdapter>();
    stripeAdapter->processPayment(100.50);
    std::unique_ptr<PaymentProcessor> payPalAdapter = std::make_unique<PayPalAdapter>();
    payPalAdapter->processPayment(75.25);
    std::cout << std::endl;
    
    std::cout << "--- Two-way Temperature Adapter ---" << std::endl;
    TemperatureAdapter tempAdapter;
    tempAdapter.setTemperatureInCelsius(25.0);
    std::cout << "Temperature in Celsius: " << tempAdapter.getTemperatureInCelsius() << "°C" << std::endl;
    std::cout << "Temperature in Fahrenheit: " << tempAdapter.getTemperatureInFahrenheit() << "°F" << std::endl;
    
    tempAdapter.setTemperatureInFahrenheit(77.0);
    std::cout << "\nTemperature in Celsius: " << tempAdapter.getTemperatureInCelsius() << "°C" << std::endl;
    std::cout << "Temperature in Fahrenheit: " << tempAdapter.getTemperatureInFahrenheit() << "°F" << std::endl;
    
    return 0;
}
