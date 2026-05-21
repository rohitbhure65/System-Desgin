#include "payment.hpp"
#include "sorting.hpp"
#include "route_planning.hpp"
#include <iostream>
#include <memory>

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
