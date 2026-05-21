#pragma once
#include <string>
#include <unordered_map>
#include <memory>
#include <vector>

class SoldierType {
public:
    virtual ~SoldierType() = default;
    virtual void render(int x, int y, const std::string& weapon) = 0;
    
    std::string getUniform() const { return uniform; }
    int getSpeed() const { return speed; }
    
protected:
    std::string uniform;
    int speed;
};

class ConcreteSoldierType : public SoldierType {
public:
    ConcreteSoldierType(const std::string& uniform, int speed, const std::string& rank)
        : uniform(uniform), speed(speed), rank(rank) {}
    
    void render(int x, int y, const std::string& weapon) override {
        std::cout << "Rendering " << rank << " soldier at (" << x << ", " << y 
                  << ") with " << uniform << " uniform, speed " << speed 
                  << ", holding " << weapon << std::endl;
    }
    
private:
    std::string rank;
};

class SoldierTypeFactory {
private:
    std::unordered_map<std::string, std::shared_ptr<SoldierType>> soldierTypes;
    
    std::string getKey(const std::string& uniform, int speed, const std::string& rank) {
        return uniform + "|" + std::to_string(speed) + "|" + rank;
    }
    
public:
    std::shared_ptr<SoldierType> getSoldierType(const std::string& uniform, int speed, const std::string& rank) {
        std::string key = getKey(uniform, speed, rank);
        
        if (soldierTypes.find(key) == soldierTypes.end()) {
            std::cout << "Creating new soldier type: " << rank << std::endl;
            soldierTypes[key] = std::make_shared<ConcreteSoldierType>(uniform, speed, rank);
        } else {
            std::cout << "Reusing existing soldier type: " << rank << std::endl;
        }
        
        return soldierTypes[key];
    }
    
    int getTotalSoldierTypes() const {
        return soldierTypes.size();
    }
};

class Soldier {
private:
    int x, y;
    std::string weapon;
    std::shared_ptr<SoldierType> soldierType;
    
public:
    Soldier(int x, int y, const std::string& weapon, std::shared_ptr<SoldierType> soldierType)
        : x(x), y(y), weapon(weapon), soldierType(soldierType) {}
    
    void render() {
        soldierType->render(x, y, weapon);
    }
    
    void move(int newX, int newY) {
        x = newX;
        y = newY;
    }
};
