#pragma once
#include <string>
#include <vector>
#include <memory>
#include <algorithm>

class WeatherObserver {
public:
    virtual ~WeatherObserver() = default;
    virtual void onWeatherUpdate(float temperature, float humidity, float pressure) = 0;
};

class WeatherStation {
private:
    std::vector<std::shared_ptr<WeatherObserver>> observers;
    float temperature;
    float humidity;
    float pressure;
    
public:
    WeatherStation() : temperature(0), humidity(0), pressure(0) {}
    
    void addObserver(std::shared_ptr<WeatherObserver> observer) {
        observers.push_back(observer);
    }
    
    void removeObserver(std::shared_ptr<WeatherObserver> observer) {
        auto it = std::find(observers.begin(), observers.end(), observer);
        if (it != observers.end()) {
            observers.erase(it);
        }
    }
    
    void setMeasurements(float temp, float hum, float press) {
        temperature = temp;
        humidity = hum;
        pressure = press;
        std::cout << "\nWeather updated: " << temperature << "°C, " 
                  << humidity << "% humidity, " << pressure << " hPa" << std::endl;
        notifyObservers();
    }
    
private:
    void notifyObservers() {
        for (const auto& observer : observers) {
            observer->onWeatherUpdate(temperature, humidity, pressure);
        }
    }
};

class DisplayDevice : public WeatherObserver {
private:
    std::string deviceName;
    
public:
    DisplayDevice(const std::string& name) : deviceName(name) {}
    
    void onWeatherUpdate(float temperature, float humidity, float pressure) override {
        std::cout << "  [" << deviceName << "] Displaying: " << temperature << "°C, " 
                  << humidity << "%, " << pressure << " hPa" << std::endl;
    }
};

class AlertSystem : public WeatherObserver {
public:
    void onWeatherUpdate(float temperature, float humidity, float pressure) override {
        std::cout << "  [AlertSystem] Checking conditions..." << std::endl;
        if (temperature > 35) {
            std::cout << "  [AlertSystem] WARNING: High temperature!" << std::endl;
        }
        if (humidity > 80) {
            std::cout << "  [AlertSystem] WARNING: High humidity!" << std::endl;
        }
        if (pressure < 980) {
            std::cout << "  [AlertSystem] WARNING: Low pressure (storm coming)!" << std::endl;
        }
    }
};
