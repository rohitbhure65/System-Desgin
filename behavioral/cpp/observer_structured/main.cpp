#include "interfaces.hpp"
#include "youtube_channel.hpp"
#include "stock_market.hpp"
#include "weather_station.hpp"
#include <iostream>
#include <memory>

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
