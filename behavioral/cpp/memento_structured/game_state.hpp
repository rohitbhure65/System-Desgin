#pragma once
#include <string>
#include <memory>
#include <vector>

class GameStateMemento {
private:
    int level;
    int health;
    int score;
    std::string position;
    
public:
    GameStateMemento(int level, int health, int score, const std::string& position)
        : level(level), health(health), score(score), position(position) {}
    
    int getLevel() const { return level; }
    int getHealth() const { return health; }
    int getScore() const { return score; }
    std::string getPosition() const { return position; }
};

class GameCharacter {
private:
    int level;
    int health;
    int score;
    std::string position;
    
public:
    GameCharacter() : level(1), health(100), score(0), position("Start") {}
    
    void moveTo(const std::string& newPosition) {
        position = newPosition;
        std::cout << "Moved to " << position << std::endl;
    }
    
    void takeDamage(int damage) {
        health -= damage;
        if (health < 0) health = 0;
        std::cout << "Took " << damage << " damage. Health: " << health << std::endl;
    }
    
    void gainScore(int points) {
        score += points;
        std::cout << "Gained " << points << " points. Score: " << score << std::endl;
    }
    
    void levelUp() {
        level++;
        health = 100;
        std::cout << "Level up! Now at level " << level << std::endl;
    }
    
    void displayStatus() const {
        std::cout << "=== Character Status ===" << std::endl;
        std::cout << "Level: " << level << std::endl;
        std::cout << "Health: " << health << std::endl;
        std::cout << "Score: " << score << std::endl;
        std::cout << "Position: " << position << std::endl;
        std::cout << "=====================" << std::endl;
    }
    
    std::unique_ptr<GameStateMemento> saveState() {
        std::cout << "Saving game state..." << std::endl;
        return std::make_unique<GameStateMemento>(level, health, score, position);
    }
    
    void restoreState(const GameStateMemento& memento) {
        level = memento.getLevel();
        health = memento.getHealth();
        score = memento.getScore();
        position = memento.getPosition();
        std::cout << "Game state restored!" << std::endl;
        displayStatus();
    }
};

class GameSaveManager {
private:
    std::vector<std::unique_ptr<GameStateMemento>> saves;
    
public:
    void createSave(std::unique_ptr<GameStateMemento> save) {
        saves.push_back(std::move(save));
        std::cout << "Save created. Total saves: " << saves.size() << std::endl;
    }
    
    std::unique_ptr<GameStateMemento> loadSave(int index) {
        if (index >= 0 && index < saves.size()) {
            std::cout << "Loading save " << (index + 1) << "..." << std::endl;
            return std::move(saves[index]);
        }
        return nullptr;
    }
    
    int getSaveCount() const {
        return saves.size();
    }
};
