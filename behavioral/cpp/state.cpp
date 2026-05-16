/*
 * STATE DESIGN PATTERN
 * 
 * WHAT IS IT?
 * The State pattern allows an object to alter its behavior when its internal state changes.
 * The object appears to change its class by delegating state-specific behavior to different state objects.
 * 
 * WHY DOES IT EXIST?
 * - When an object's behavior depends on its state and must change at runtime
 * - When you have large conditional statements that switch between states
 * - When you want to avoid monolithic conditional logic
 * 
 * WHEN TO USE IT?
 * - When an object has many states and its behavior changes based on those states
 * - When you have large conditional operators that switch between states
 * - When you want to eliminate conditional logic from the main class
 * - Common use cases: game characters, vending machines, audio/video players, document editors
 * 
 * PROS:
 * - Single Responsibility Principle (each state is a separate class)
 * - Open/Closed Principle (can add new states without changing existing code)
 * - Eliminates conditional logic from the context
 * - Makes state transitions explicit
 * 
 * CONS:
 * - Can increase the number of classes in the system
 * - State transitions can be complex to manage
 * - May make the code more complex for simple scenarios
 * - Can lead to tight coupling between states
 * 
 * REAL-WORLD ANALOGY:
 * Think of a vending machine. It has different states: "No Coin", "Has Coin", "Dispensing", "Out of Stock". When you insert a coin, it transitions from "No Coin" to "Has Coin". When you press a button, it transitions to "Dispensing". The machine's behavior changes based on its current state, but the machine itself doesn't change - it just delegates to the appropriate state object.
 */

#include <iostream>
#include <string>
#include <memory>

// State interface - declares the state-specific methods
class State {
public:
    virtual ~State() = default;
    virtual void insertCoin() = 0;
    virtual void ejectCoin() = 0;
    virtual void pressButton() = 0;
    virtual void dispense() = 0;
};

// Context - maintains a reference to the current state
class VendingMachine {
private:
    std::unique_ptr<State> currentState;
    int coinCount;
    int stockCount;
    
public:
    VendingMachine(int initialStock) : coinCount(0), stockCount(initialStock) {
        // Initial state depends on stock
        if (initialStock > 0) {
            currentState = std::make_unique<NoCoinState>(this);
        } else {
            currentState = std::make_unique<SoldOutState>(this);
        }
    }
    
    void setState(std::unique_ptr<State> state) {
        currentState = std::move(state);
    }
    
    void insertCoin() {
        currentState->insertCoin();
    }
    
    void ejectCoin() {
        currentState->ejectCoin();
    }
    
    void pressButton() {
        currentState->pressButton();
    }
    
    void dispense() {
        currentState->dispense();
    }
    
    void addCoin() {
        coinCount++;
        std::cout << "Coin inserted. Total coins: " << coinCount << std::endl;
    }
    
    void returnCoin() {
        if (coinCount > 0) {
            coinCount--;
            std::cout << "Coin returned. Total coins: " << coinCount << std::endl;
        }
    }
    
    void releaseProduct() {
        if (stockCount > 0) {
            stockCount--;
            coinCount--;
            std::cout << "Product dispensed. Stock: " << stockCount << ", Coins: " << coinCount << std::endl;
        }
    }
    
    int getCoinCount() const {
        return coinCount;
    }
    
    int getStockCount() const {
        return stockCount;
    }
};

// Concrete State 1: No Coin
class NoCoinState : public State {
private:
    VendingMachine* machine;
    
public:
    NoCoinState(VendingMachine* machine) : machine(machine) {}
    
    void insertCoin() override {
        std::cout << "Coin inserted..." << std::endl;
        machine->addCoin();
        machine->setState(std::make_unique<HasCoinState>(machine));
    }
    
    void ejectCoin() override {
        std::cout << "No coin to eject" << std::endl;
    }
    
    void pressButton() override {
        std::cout << "Please insert a coin first" << std::endl;
    }
    
    void dispense() override {
        std::cout << "Please insert a coin first" << std::endl;
    }
};

// Concrete State 2: Has Coin
class HasCoinState : public State {
private:
    VendingMachine* machine;
    
public:
    HasCoinState(VendingMachine* machine) : machine(machine) {}
    
    void insertCoin() override {
        std::cout << "Coin already inserted" << std::endl;
    }
    
    void ejectCoin() override {
        std::cout << "Coin ejected" << std::endl;
        machine->returnCoin();
        machine->setState(std::make_unique<NoCoinState>(machine));
    }
    
    void pressButton() override {
        std::cout << "Button pressed..." << std::endl;
        if (machine->getStockCount() > 0) {
            machine->setState(std::make_unique<DispensingState>(machine));
            machine->dispense();
        } else {
            std::cout << "Out of stock" << std::endl;
            machine->setState(std::make_unique<SoldOutState>(machine));
        }
    }
    
    void dispense() override {
        std::cout << "Press button to dispense" << std::endl;
    }
};

// Concrete State 3: Dispensing
class DispensingState : public State {
private:
    VendingMachine* machine;
    
public:
    DispensingState(VendingMachine* machine) : machine(machine) {}
    
    void insertCoin() override {
        std::cout << "Please wait, dispensing..." << std::endl;
    }
    
    void ejectCoin() override {
        std::cout << "Cannot eject during dispensing" << std::endl;
    }
    
    void pressButton() override {
        std::cout << "Already dispensing..." << std::endl;
    }
    
    void dispense() override {
        machine->releaseProduct();
        if (machine->getStockCount() > 0) {
            machine->setState(std::make_unique<NoCoinState>(machine));
        } else {
            machine->setState(std::make_unique<SoldOutState>(machine));
        }
    }
};

// Concrete State 4: Sold Out
class SoldOutState : public State {
private:
    VendingMachine* machine;
    
public:
    SoldOutState(VendingMachine* machine) : machine(machine) {}
    
    void insertCoin() override {
        std::cout << "Cannot insert coin, machine is sold out" << std::endl;
    }
    
    void ejectCoin() override {
        std::cout << "Cannot eject, no coin inserted" << std::endl;
    }
    
    void pressButton() override {
        std::cout << "Machine is sold out" << std::endl;
    }
    
    void dispense() override {
        std::cout << "Machine is sold out" << std::endl;
    }
};

// Example 2: Audio Player States
// Shows how State can be used for media players

class AudioPlayerState {
public:
    virtual ~AudioPlayerState() = default;
    virtual void clickPlay() = 0;
    virtual void clickStop() = 0;
    virtual void clickNext() = 0;
    virtual void clickPrevious() = 0;
};

class AudioPlayer {
private:
    std::unique_ptr<AudioPlayerState> currentState;
    bool isPlaying;
    int currentTrack;
    int totalTracks;
    
public:
    AudioPlayer(int tracks) : isPlaying(false), currentTrack(1), totalTracks(tracks) {
        currentState = std::make_unique<StoppedState>(this);
    }
    
    void setState(std::unique_ptr<AudioPlayerState> state) {
        currentState = std::move(state);
    }
    
    void clickPlay() {
        currentState->clickPlay();
    }
    
    void clickStop() {
        currentState->clickStop();
    }
    
    void clickNext() {
        currentState->clickNext();
    }
    
    void clickPrevious() {
        currentState->clickPrevious();
    }
    
    void startPlaying() {
        isPlaying = true;
        std::cout << "Started playing track " << currentTrack << std::endl;
    }
    
    void stopPlaying() {
        isPlaying = false;
        std::cout << "Stopped playing" << std::endl;
    }
    
    void nextTrack() {
        currentTrack = (currentTrack % totalTracks) + 1;
        std::cout << "Moved to track " << currentTrack << std::endl;
    }
    
    void previousTrack() {
        currentTrack = (currentTrack == 1) ? totalTracks : currentTrack - 1;
        std::cout << "Moved to track " << currentTrack << std::endl;
    }
    
    bool getIsPlaying() const {
        return isPlaying;
    }
};

class PlayingState : public AudioPlayerState {
private:
    AudioPlayer* player;
    
public:
    PlayingState(AudioPlayer* player) : player(player) {}
    
    void clickPlay() override {
        std::cout << "Already playing" << std::endl;
    }
    
    void clickStop() override {
        std::cout << "Stopping playback..." << std::endl;
        player->stopPlaying();
        player->setState(std::make_unique<StoppedState>(player));
    }
    
    void clickNext() override {
        std::cout << "Skipping to next track..." << std::endl;
        player->nextTrack();
    }
    
    void clickPrevious() override {
        std::cout << "Going to previous track..." << std::endl;
        player->previousTrack();
    }
};

class StoppedState : public AudioPlayerState {
private:
    AudioPlayer* player;
    
public:
    StoppedState(AudioPlayer* player) : player(player) {}
    
    void clickPlay() override {
        std::cout << "Starting playback..." << std::endl;
        player->startPlaying();
        player->setState(std::make_unique<PlayingState>(player));
    }
    
    void clickStop() override {
        std::cout << "Already stopped" << std::endl;
    }
    
    void clickNext() override {
        std::cout << "Skipping to next track..." << std::endl;
        player->nextTrack();
    }
    
    void clickPrevious() override {
        std::cout << "Going to previous track..." << std::endl;
        player->previousTrack();
    }
};

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
