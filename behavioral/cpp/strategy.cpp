/*
 * STRATEGY DESIGN PATTERN
 * 
 * WHAT IS IT?
 * The Strategy pattern defines a family of algorithms, encapsulates each one, and makes them interchangeable.
 * It lets the algorithm vary independently from clients that use it.
 * 
 * WHY DOES IT EXIST?
 * - When you want to define a family of algorithms and make them interchangeable
 * - When you want to avoid conditional statements for selecting algorithms
 * - When you want to separate algorithm implementation from the code that uses it
 * 
 * WHEN TO USE IT?
 * - When you have multiple ways to do an operation and want to switch between them at runtime
 * - When you want to isolate the algorithm implementation from the client code
 * - When you have complex conditional logic that selects different algorithms
 * - Common use cases: sorting algorithms, payment processing, compression, route planning, validation
 * 
 * PROS:
 * - Open/Closed Principle (can add new strategies without changing existing code)
 * - Separates algorithm implementation from the code that uses it
 * - Eliminates conditional statements for selecting algorithms
 * - Allows runtime selection of algorithms
 * 
 * CONS:
 * - Clients must be aware of the differences between strategies
 * - Can increase the number of classes in the system
 * - May lead to performance overhead if strategies are complex
 * - Can make the code more complex for simple scenarios
 * 
 * REAL-WORLD ANALOGY:
 * Think of a GPS navigation app. It can use different route calculation strategies: fastest route, shortest distance, avoid highways, scenic route. You can switch between these strategies at runtime without changing the app itself. The app (context) delegates the route calculation to the selected strategy.
 */

#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <algorithm>

// Strategy interface - declares the algorithm method
class PaymentStrategy {
public:
    virtual ~PaymentStrategy() = default;
    virtual void pay(double amount) = 0;
};

// Concrete Strategy 1: Credit Card
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

// Concrete Strategy 2: PayPal
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

// Concrete Strategy 3: Crypto
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

// Context - uses the strategy
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

// Example 2: Sorting Strategies
// Shows how Strategy can be used for different algorithms

class SortingStrategy {
public:
    virtual ~SortingStrategy() = default;
    virtual void sort(std::vector<int>& data) = 0;
};

class BubbleSort : public SortingStrategy {
public:
    void sort(std::vector<int>& data) override {
        std::cout << "Using Bubble Sort..." << std::endl;
        int n = data.size();
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                if (data[j] > data[j + 1]) {
                    std::swap(data[j], data[j + 1]);
                }
            }
        }
    }
};

class QuickSort : public SortingStrategy {
public:
    void sort(std::vector<int>& data) override {
        std::cout << "Using Quick Sort..." << std::endl;
        quickSort(data, 0, data.size() - 1);
    }
    
private:
    void quickSort(std::vector<int>& data, int low, int high) {
        if (low < high) {
            int pi = partition(data, low, high);
            quickSort(data, low, pi - 1);
            quickSort(data, pi + 1, high);
        }
    }
    
    int partition(std::vector<int>& data, int low, int high) {
        int pivot = data[high];
        int i = low - 1;
        for (int j = low; j < high; j++) {
            if (data[j] < pivot) {
                i++;
                std::swap(data[i], data[j]);
            }
        }
        std::swap(data[i + 1], data[high]);
        return i + 1;
    }
};

class MergeSort : public SortingStrategy {
public:
    void sort(std::vector<int>& data) override {
        std::cout << "Using Merge Sort..." << std::endl;
        mergeSort(data, 0, data.size() - 1);
    }
    
private:
    void mergeSort(std::vector<int>& data, int left, int right) {
        if (left < right) {
            int mid = left + (right - left) / 2;
            mergeSort(data, left, mid);
            mergeSort(data, mid + 1, right);
            merge(data, left, mid, right);
        }
    }
    
    void merge(std::vector<int>& data, int left, int mid, int right) {
        int n1 = mid - left + 1;
        int n2 = right - mid;
        
        std::vector<int> L(n1), R(n2);
        
        for (int i = 0; i < n1; i++) L[i] = data[left + i];
        for (int j = 0; j < n2; j++) R[j] = data[mid + 1 + j];
        
        int i = 0, j = 0, k = left;
        while (i < n1 && j < n2) {
            if (L[i] <= R[j]) {
                data[k++] = L[i++];
            } else {
                data[k++] = R[j++];
            }
        }
        
        while (i < n1) data[k++] = L[i++];
        while (j < n2) data[k++] = R[j++];
    }
};

class Sorter {
private:
    std::unique_ptr<SortingStrategy> strategy;
    
public:
    void setSortingStrategy(std::unique_ptr<SortingStrategy> strat) {
        strategy = std::move(strat);
    }
    
    void sortData(std::vector<int>& data) {
        std::cout << "\nOriginal data: ";
        for (int num : data) std::cout << num << " ";
        std::cout << std::endl;
        
        if (strategy) {
            strategy->sort(data);
        } else {
            std::cout << "No sorting strategy selected" << std::endl;
        }
        
        std::cout << "Sorted data: ";
        for (int num : data) std::cout << num << " ";
        std::cout << std::endl;
    }
};

// Example 3: Route Planning Strategies
// Shows how Strategy can be used for navigation

class RouteStrategy {
public:
    virtual ~RouteStrategy() = default;
    virtual void calculateRoute(const std::string& from, const std::string& to) = 0;
};

class FastestRoute : public RouteStrategy {
public:
    void calculateRoute(const std::string& from, const std::string& to) override {
        std::cout << "Calculating fastest route from " << from << " to " << to << std::endl;
        std::cout << "  Using highways and main roads to minimize time" << std::endl;
        std::cout << "  Estimated time: 25 minutes" << std::endl;
    }
};

class ShortestRoute : public RouteStrategy {
public:
    void calculateRoute(const std::string& from, const std::string& to) override {
        std::cout << "Calculating shortest route from " << from << " to " << to << std::endl;
        std::cout << "  Using direct path to minimize distance" << std::endl;
        std::cout << "  Estimated distance: 15 km" << std::endl;
    }
};

class ScenicRoute : public RouteStrategy {
public:
    void calculateRoute(const std::string& from, const std::string& to) override {
        std::cout << "Calculating scenic route from " << from << " to " << to << std::endl;
        std::cout << "  Using parks and landmarks for best views" << std::endl;
        std::cout << "  Estimated time: 45 minutes" << std::endl;
    }
};

class NavigationSystem {
private:
    std::unique_ptr<RouteStrategy> strategy;
    
public:
    void setRouteStrategy(std::unique_ptr<RouteStrategy> strat) {
        strategy = std::move(strat);
    }
    
    void navigate(const std::string& from, const std::string& to) {
        std::cout << "\n=== Navigation ===" << std::endl;
        std::cout << "From: " << from << std::endl;
        std::cout << "To: " << to << std::endl;
        
        if (strategy) {
            strategy->calculateRoute(from, to);
        } else {
            std::cout << "No route strategy selected" << std::endl;
        }
    }
};

int main() {
    std::cout << "=== Strategy Pattern Demo ===" << std::endl << std::endl;
    
    // Example 1: Payment Processing
    std::cout << "--- Payment Processing Example ---" << std::endl;
    
    ShoppingCart cart;
    cart.addItem("Laptop", 999.99);
    cart.addItem("Mouse", 29.99);
    cart.addItem("Keyboard", 79.99);
    
    std::cout << "\nPaying with Credit Card:" << std::endl;
    cart.setPaymentStrategy(std::make_unique<CreditCardPayment>("4111111111111111", "12/25", "123"));
    cart.checkout();
    
    std::cout << "\nPaying with PayPal:" << std::endl;
    cart.setPaymentStrategy(std::make_unique<PayPalPayment>("user@example.com", "password"));
    cart.checkout();
    
    std::cout << "\nPaying with Crypto:" << std::endl;
    cart.setPaymentStrategy(std::make_unique<CryptoPayment>("0x1234567890abcdef", "private_key"));
    cart.checkout();
    
    // Example 2: Sorting Algorithms
    std::cout << "\n--- Sorting Algorithms Example ---" << std::endl;
    
    Sorter sorter;
    std::vector<int> data = {64, 34, 25, 12, 22, 11, 90};
    
    sorter.setSortingStrategy(std::make_unique<BubbleSort>());
    sorter.sortData(data);
    
    std::vector<int> data2 = {64, 34, 25, 12, 22, 11, 90};
    sorter.setSortingStrategy(std::make_unique<QuickSort>());
    sorter.sortData(data2);
    
    std::vector<int> data3 = {64, 34, 25, 12, 22, 11, 90};
    sorter.setSortingStrategy(std::make_unique<MergeSort>());
    sorter.sortData(data3);
    
    // Example 3: Route Planning
    std::cout << "\n--- Route Planning Example ---" << std::endl;
    
    NavigationSystem nav;
    
    std::cout << "\nFastest route:" << std::endl;
    nav.setRouteStrategy(std::make_unique<FastestRoute>());
    nav.navigate("Home", "Office");
    
    std::cout << "\nShortest route:" << std::endl;
    nav.setRouteStrategy(std::make_unique<ShortestRoute>());
    nav.navigate("Home", "Office");
    
    std::cout << "\nScenic route:" << std::endl;
    nav.setRouteStrategy(std::make_unique<ScenicRoute>());
    nav.navigate("Home", "Office");
    
    return 0;
}
