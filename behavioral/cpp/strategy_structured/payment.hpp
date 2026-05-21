#pragma once
#include <string>
#include <memory>
#include <vector>

class PaymentStrategy {
public:
    virtual ~PaymentStrategy() = default;
    virtual void pay(double amount) = 0;
};

class CreditCardPayment : public PaymentStrategy {
private:
    std::string cardNumber;
    std::string expiryDate;
    std::string cvv;
    
public:
    CreditCardPayment(const std::string& card, const std::string& expiry, const std::string& cvv)
        : cardNumber(card), expiryDate(expiry), cvv(cvv) {}
    
    void pay(double amount) override {
        std::cout << "Paying $" << amount << " with Credit Card ending in " 
                  << cardNumber.substr(cardNumber.length() - 4) << std::endl;
        std::cout << "  Card: ****-****-****-" << cardNumber.substr(cardNumber.length() - 4) << std::endl;
        std::cout << "  Expiry: " << expiryDate << std::endl;
    }
};

class PayPalPayment : public PaymentStrategy {
private:
    std::string email;
    std::string password;
    
public:
    PayPalPayment(const std::string& email, const std::string& password)
        : email(email), password(password) {}
    
    void pay(double amount) override {
        std::cout << "Paying $" << amount << " with PayPal" << std::endl;
        std::cout << "  Account: " << email << std::endl;
    }
};

class CryptoPayment : public PaymentStrategy {
private:
    std::string walletAddress;
    std::string privateKey;
    
public:
    CryptoPayment(const std::string& wallet, const std::string& key)
        : walletAddress(wallet), privateKey(key) {}
    
    void pay(double amount) override {
        std::cout << "Paying $" << amount << " with Cryptocurrency" << std::endl;
        std::cout << "  Wallet: " << walletAddress.substr(0, 10) << "..." << std::endl;
    }
};

class ShoppingCart {
private:
    std::unique_ptr<PaymentStrategy> paymentStrategy;
    std::vector<std::string> items;
    std::vector<double> prices;
    
public:
    void setPaymentStrategy(std::unique_ptr<PaymentStrategy> strategy) {
        paymentStrategy = std::move(strategy);
    }
    
    void addItem(const std::string& item, double price) {
        items.push_back(item);
        prices.push_back(price);
    }
    
    double getTotal() const {
        double total = 0;
        for (double price : prices) {
            total += price;
        }
        return total;
    }
    
    void checkout() {
        std::cout << "\n=== Checkout ===" << std::endl;
        std::cout << "Items:" << std::endl;
        for (size_t i = 0; i < items.size(); i++) {
            std::cout << "  - " << items[i] << ": $" << prices[i] << std::endl;
        }
        std::cout << "Total: $" << getTotal() << std::endl;
        
        if (paymentStrategy) {
            paymentStrategy->pay(getTotal());
        } else {
            std::cout << "No payment method selected" << std::endl;
        }
    }
};
