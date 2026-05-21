#pragma once
#include <iostream>

class GameCharacter {
public:
    virtual ~GameCharacter() = default;
    
    void createCharacter() {
        std::cout << "\n=== Creating Character ===" << std::endl;
        chooseName();
        selectRace();
        selectClass();
        assignStats();
        equipStartingItems();
        std::cout << "=== Character Created ===" << std::endl;
    }
    
protected:
    virtual void chooseName() = 0;
    virtual void selectRace() = 0;
    virtual void selectClass() = 0;
    virtual void assignStats() = 0;
    virtual void equipStartingItems() = 0;
    
    virtual void displayCharacter() {
        std::cout << "Character ready for adventure!" << std::endl;
    }
};

class Warrior : public GameCharacter {
protected:
    void chooseName() override {
        std::cout << "Name chosen: Thorin" << std::endl;
    }
    
    void selectRace() override {
        std::cout << "Race selected: Dwarf" << std::endl;
    }
    
    void selectClass() override {
        std::cout << "Class selected: Warrior" << std::endl;
    }
    
    void assignStats() override {
        std::cout << "Stats assigned: STR: 18, DEX: 12, CON: 16, INT: 8, WIS: 10" << std::endl;
    }
    
    void equipStartingItems() override {
        std::cout << "Equipped: Iron Sword, Steel Shield, Chain Mail" << std::endl;
    }
    
    void displayCharacter() override {
        GameCharacter::displayCharacter();
        std::cout << "Special ability: Battle Rage" << std::endl;
    }
};

class Mage : public GameCharacter {
protected:
    void chooseName() override {
        std::cout << "Name chosen: Gandalf" << std::endl;
    }
    
    void selectRace() override {
        std::cout << "Race selected: Human" << std::endl;
    }
    
    void selectClass() override {
        std::cout << "Class selected: Mage" << std::endl;
    }
    
    void assignStats() override {
        std::cout << "Stats assigned: STR: 8, DEX: 14, CON: 10, INT: 18, WIS: 16" << std::endl;
    }
    
    void equipStartingItems() override {
        std::cout << "Equipped: Wooden Staff, Robe, Spellbook" << std::endl;
    }
    
    void displayCharacter() override {
        GameCharacter::displayCharacter();
        std::cout << "Special ability: Fireball" << std::endl;
    }
};

class Rogue : public GameCharacter {
protected:
    void chooseName() override {
        std::cout << "Name chosen: Legolas" << std::endl;
    }
    
    void selectRace() override {
        std::cout << "Race selected: Elf" << std::endl;
    }
    
    void selectClass() override {
        std::cout << "Class selected: Rogue" << std::endl;
    }
    
    void assignStats() override {
        std::cout << "Stats assigned: STR: 12, DEX: 18, CON: 12, INT: 14, WIS: 12" << std::endl;
    }
    
    void equipStartingItems() override {
        std::cout << "Equipped: Dagger, Leather Armor, Lockpicks" << std::endl;
    }
    
    void displayCharacter() override {
        GameCharacter::displayCharacter();
        std::cout << "Special ability: Stealth" << std::endl;
    }
};
