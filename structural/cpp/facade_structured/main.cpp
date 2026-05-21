#include "facades.hpp"
#include <iostream>

int main() {
    std::cout << "=== Facade Pattern Demo ===" << std::endl << std::endl;
    
    std::cout << "--- Computer Boot Example ---" << std::endl;
    ComputerFacade computer;
    computer.start();
    std::cout << std::endl;
    computer.shutdown();
    std::cout << std::endl;
    
    std::cout << "--- Home Theater Example ---" << std::endl;
    HomeTheaterFacade homeTheater;
    homeTheater.watchMovie("The Matrix");
    homeTheater.endMovie();
    homeTheater.listenToRadio(98.7);
    homeTheater.turnOffRadio();
    std::cout << std::endl;
    
    std::cout << "--- Order Processing Example ---" << std::endl;
    OrderFacade orderSystem;
    orderSystem.placeOrder("Laptop", 1, 999.99, "123 Main St", "customer@email.com");
    orderSystem.cancelOrder("Laptop", 1, 999.99, "customer@email.com");
    
    return 0;
}
