#include "interfaces.hpp"
#include "vending_machine.hpp"
#include "audio_player.hpp"
#include <iostream>

int main() {
    std::cout << "=== State Pattern Demo ===" << std::endl << std::endl;
    
    // Example 1: Vending Machine
    std::cout << "--- Vending Machine Example ---" << std::endl;
    
    VendingMachine machine(5);  // 5 items in stock
    
    std::cout << "\nAttempt to press button without coin:" << std::endl;
    machine.pressButton();
    
    std::cout << "\nInsert coin:" << std::endl;
    machine.insertCoin();
    
    std::cout << "\nPress button:" << std::endl;
    machine.pressButton();
    
    std::cout << "\nInsert another coin:" << std::endl;
    machine.insertCoin();
    
    std::cout << "\nPress button:" << std::endl;
    machine.pressButton();
    
    std::cout << "\nEject coin:" << std::endl;
    machine.ejectCoin();
    
    std::cout << std::endl;
    
    // Example 2: Audio Player
    std::cout << "--- Audio Player Example ---" << std::endl;
    
    AudioPlayer player(10);  // 10 tracks
    
    std::cout << "\nClick play (stopped state):" << std::endl;
    player.clickPlay();
    
    std::cout << "\nClick next:" << std::endl;
    player.clickNext();
    
    std::cout << "\nClick stop:" << std::endl;
    player.clickStop();
    
    std::cout << "\nClick previous:" << std::endl;
    player.clickPrevious();
    
    std::cout << "\nClick play again:" << std::endl;
    player.clickPlay();
    
    return 0;
}
