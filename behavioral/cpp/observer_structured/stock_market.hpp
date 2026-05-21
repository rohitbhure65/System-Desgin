#pragma once
#include <string>
#include <vector>
#include <memory>
#include <map>
#include <algorithm>

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
