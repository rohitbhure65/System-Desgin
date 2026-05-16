/*
 * OBSERVER DESIGN PATTERN
 * 
 * WHAT IS IT?
 * The Observer pattern defines a subscription mechanism to notify multiple objects about any events that happen to the object they are observing.
 * It establishes a one-to-many dependency between objects so that when one object changes state, all its dependents are notified.
 * 
 * WHY DOES IT EXIST?
 * - When you need to notify multiple objects about changes to a single object
 * - When you want to decouple the subject from its observers
 * - When you want to broadcast changes to multiple subscribers dynamically
 * 
 * WHEN TO USE IT?
 * - When changes to one object require changing other objects
 * - When the set of objects that need to be notified is unknown or dynamic
 * - When you want to implement a publish-subscribe model
 * - Common use cases: GUI event handling, news feeds, social media notifications, stock price updates
 * 
 * PROS:
 * - Open/Closed Principle (can add new observers without changing the subject)
 * - Establishes loose coupling between subject and observers
 * - Can broadcast communications to multiple objects
 * - Supports dynamic subscription/unsubscription
 * 
 * CONS:
 * - Can lead to unexpected updates if observers are not careful
 * - Can cause performance issues with many observers
 * - Debugging can be difficult due to indirect calls
 * - May cause memory leaks if observers don't unsubscribe
 * 
 * REAL-WORLD ANALOGY:
 * Think of a YouTube channel (subject) and subscribers (observers). When the channel uploads a new video, all subscribers get notified. Subscribers can subscribe or unsubscribe at any time. The channel doesn't need to know who is subscribed - it just broadcasts notifications to all current subscribers.
 */

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <functional>

// Observer interface - declares the update method
class Observer {
public:
    virtual ~Observer() = default;
    virtual void update(const std::string& message) = 0;
};

// Subject interface - declares methods for attaching, detaching, and notifying observers
class Subject {
protected:
    std::vector<std::shared_ptr<Observer>> observers;
    
public:
    virtual ~Subject() = default;
    
    void attach(std::shared_ptr<Observer> observer) {
        observers.push_back(observer);
        std::cout << "Attached an observer" << std::endl;
    }
    
    void detach(std::shared_ptr<Observer> observer) {
        auto it = std::find(observers.begin(), observers.end(), observer);
        if (it != observers.end()) {
            observers.erase(it);
            std::cout << "Detached an observer" << std::endl;
        }
    }
    
    void notify(const std::string& message) {
        std::cout << "Notifying observers..." << std::endl;
        for (const auto& observer : observers) {
            observer->update(message);
        }
    }
};

// Concrete Subject
class YouTubeChannel : public Subject {
private:
    std::string channelName;
    
public:
    YouTubeChannel(const std::string& name) : channelName(name) {}
    
    void uploadVideo(const std::string& videoTitle) {
        std::cout << "\n" << channelName << " uploaded: " << videoTitle << std::endl;
        notify("New video: " + videoTitle);
    }
    
    void goLive(const std::string& streamTitle) {
        std::cout << "\n" << channelName << " is live: " << streamTitle << std::endl;
        notify("Live stream started: " + streamTitle);
    }
};

// Concrete Observer 1
class Subscriber : public Observer {
private:
    std::string name;
    
public:
    Subscriber(const std::string& name) : name(name) {}
    
    void update(const std::string& message) override {
        std::cout << "  " << name << " received notification: " << message << std::endl;
    }
};

// Concrete Observer 2
class NotificationService : public Observer {
public:
    void update(const std::string& message) override {
        std::cout << "  [NotificationService] Push notification sent: " << message << std::endl;
    }
};

// Example 2: Stock Market
// Shows how Observer can be used for real-time updates

class StockObserver {
public:
    virtual ~StockObserver() = default;
    virtual void onStockPriceChange(const std::string& symbol, double price) = 0;
};

class StockMarket {
private:
    std::vector<std::shared_ptr<StockObserver>> observers;
    std::map<std::string, double> stockPrices;
    
public:
    void addObserver(std::shared_ptr<StockObserver> observer) {
        observers.push_back(observer);
    }
    
    void removeObserver(std::shared_ptr<StockObserver> observer) {
        auto it = std::find(observers.begin(), observers.end(), observer);
        if (it != observers.end()) {
            observers.erase(it);
        }
    }
    
    void updateStockPrice(const std::string& symbol, double price) {
        stockPrices[symbol] = price;
        std::cout << "\n" << symbol << " price updated to $" << price << std::endl;
        notifyObservers(symbol, price);
    }
    
private:
    void notifyObservers(const std::string& symbol, double price) {
        for (const auto& observer : observers) {
            observer->onStockPriceChange(symbol, price);
        }
    }
};

class Investor : public StockObserver {
private:
    std::string name;
    std::map<std::string, int> portfolio;
    
public:
    Investor(const std::string& name) : name(name) {}
    
    void buyStock(const std::string& symbol, int shares) {
        portfolio[symbol] += shares;
        std::cout << name << " bought " << shares << " shares of " << symbol << std::endl;
    }
    
    void onStockPriceChange(const std::string& symbol, double price) override {
        if (portfolio.find(symbol) != portfolio.end()) {
            std::cout << "  " << name << " owns " << portfolio[symbol] 
                      << " shares of " << symbol << " (current price: $" << price << ")" << std::endl;
        }
    }
};

class TradingBot : public StockObserver {
public:
    void onStockPriceChange(const std::string& symbol, double price) override {
        std::cout << "  [TradingBot] Analyzing " << symbol << " at $" << price << std::endl;
        if (price > 100) {
            std::cout << "  [TradingBot] Recommendation: SELL" << std::endl;
        } else if (price < 50) {
            std::cout << "  [TradingBot] Recommendation: BUY" << std::endl;
        }
    }
};

// Example 3: Weather Station
// Shows how Observer can be used for sensor data

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

int main() {
    std::cout << "=== Observer Pattern Demo ===" << std::endl << std::endl;
    
    // Example 1: YouTube Channel
    std::cout << "--- YouTube Channel Example ---" << std::endl;
    
    auto channel = std::make_shared<YouTubeChannel>("Tech Channel");
    
    auto subscriber1 = std::make_shared<Subscriber>("Alice");
    auto subscriber2 = std::make_shared<Subscriber>("Bob");
    auto notificationService = std::make_shared<NotificationService>();
    
    channel->attach(subscriber1);
    channel->attach(subscriber2);
    channel->attach(notificationService);
    
    channel->uploadVideo("Design Patterns Tutorial");
    
    channel->detach(subscriber2);
    
    channel->goLive("Live Q&A Session");
    
    std::cout << std::endl;
    
    // Example 2: Stock Market
    std::cout << "--- Stock Market Example ---" << std::endl;
    
    StockMarket market;
    
    auto investor1 = std::make_shared<Investor>("John");
    auto investor2 = std::make_shared<Investor>("Jane");
    auto tradingBot = std::make_shared<TradingBot>();
    
    market.addObserver(investor1);
    market.addObserver(investor2);
    market.addObserver(tradingBot);
    
    investor1->buyStock("AAPL", 100);
    investor2->buyStock("GOOGL", 50);
    
    market.updateStockPrice("AAPL", 150.50);
    market.updateStockPrice("GOOGL", 45.00);
    market.updateStockPrice("TSLA", 200.00);
    
    std::cout << std::endl;
    
    // Example 3: Weather Station
    std::cout << "--- Weather Station Example ---" << std::endl;
    
    WeatherStation station;
    
    auto phoneDisplay = std::make_shared<DisplayDevice>("Phone");
    auto watchDisplay = std::make_shared<DisplayDevice>("Smart Watch");
    auto alertSystem = std::make_shared<AlertSystem>();
    
    station.addObserver(phoneDisplay);
    station.addObserver(watchDisplay);
    station.addObserver(alertSystem);
    
    station.setMeasurements(25.0, 60.0, 1013.0);
    station.setMeasurements(38.0, 85.0, 975.0);
    station.setMeasurements(20.0, 50.0, 1020.0);
    
    return 0;
}
