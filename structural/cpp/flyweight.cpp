/*
 * FLYWEIGHT DESIGN PATTERN
 * 
 * WHAT IS IT?
 * The Flyweight pattern lets you fit more objects into the available RAM by sharing common parts of state between multiple objects.
 * It separates intrinsic state (shared) from extrinsic state (unique).
 * 
 * WHY DOES IT EXIST?
 * - When you need to reduce memory usage by sharing objects
 * - When a large number of similar objects should be shared
 * - When most of an object's state can be made extrinsic
 * 
 * WHEN TO USE IT?
 * - When your application uses a large number of objects
 * - When storage costs are high because of the quantity of objects
 * - When most of the object's state can be made extrinsic
 * - When many groups of objects can be replaced by relatively few shared objects
 * - Common use cases: text editors (character formatting), game objects (trees, soldiers), GUI elements (icons, fonts)
 * 
 * PROS:
 * - Reduces memory consumption by sharing objects
 * - Improves performance when many similar objects are needed
 * - Centralized state management
 * - Can be combined with other patterns (Composite, Strategy)
 * 
 * CONS:
 * - May increase runtime complexity due to sharing
 * - Requires careful identification of intrinsic vs extrinsic state
 * - Can make code more complex
 * - May sacrifice some encapsulation (extrinsic state passed to flyweight)
 * 
 * REAL-WORLD ANALOGY:
 * Think of a coffee shop. They don't make a new cup for every customer - they reuse cups (intrinsic state: the cup itself). What changes is the coffee inside (extrinsic state: the type of coffee). The cup is shared (flyweight), while the coffee content varies per customer.
 */

#include <iostream>
#include <string>
#include <unordered_map>
#include <memory>
#include <vector>

// Flyweight Interface - defines the operations that can be performed on flyweight objects
class TreeType {
public:
    virtual ~TreeType() = default;
    virtual void draw(int x, int y) = 0;
    std::string getName() const { return name; }
    std::string getColor() const { return color; }
    
protected:
    std::string name;
    std::string color;
};

// Concrete Flyweight - implements the flyweight interface and stores intrinsic state
class ConcreteTreeType : public TreeType {
public:
    ConcreteTreeType(const std::string& name, const std::string& color, const std::string& texture)
        : name(name), color(color), texture(texture) {}
    
    void draw(int x, int y) override {
        std::cout << "Drawing " << name << " tree at (" << x << ", " << y 
                  << ") with color " << color << " and texture " << texture << std::endl;
    }
    
private:
    std::string texture;
};

// Flyweight Factory - creates and manages flyweight objects
class TreeFactory {
private:
    std::unordered_map<std::string, std::shared_ptr<TreeType>> treeTypes;
    
    // Helper function to create a unique key for the map
    std::string getKey(const std::string& name, const std::string& color, const std::string& texture) {
        return name + "|" + color + "|" + texture;
    }
    
public:
    std::shared_ptr<TreeType> getTreeType(const std::string& name, const std::string& color, const std::string& texture) {
        std::string key = getKey(name, color, texture);
        
        if (treeTypes.find(key) == treeTypes.end()) {
            std::cout << "Creating new tree type: " << name << std::endl;
            treeTypes[key] = std::make_shared<ConcreteTreeType>(name, color, texture);
        } else {
            std::cout << "Reusing existing tree type: " << name << std::endl;
        }
        
        return treeTypes[key];
    }
    
    int getTotalTreeTypes() const {
        return treeTypes.size();
    }
};

// Context - contains extrinsic state and uses flyweight objects
class Tree {
private:
    int x, y;
    std::shared_ptr<TreeType> treeType;
    
public:
    Tree(int x, int y, std::shared_ptr<TreeType> treeType)
        : x(x), y(y), treeType(treeType) {}
    
    void draw() {
        treeType->draw(x, y);
    }
};

// Example 2: Character Formatting in Text Editor
// Shows how Flyweight can be used for text rendering

class CharacterFormat {
public:
    virtual ~CharacterFormat() = default;
    virtual void apply(const std::string& text) = 0;
    
    std::string getFont() const { return font; }
    int getSize() const { return size; }
    std::string getColor() const { return color; }
    
protected:
    std::string font;
    int size;
    std::string color;
};

class ConcreteCharacterFormat : public CharacterFormat {
public:
    ConcreteCharacterFormat(const std::string& font, int size, const std::string& color, bool bold, bool italic)
        : font(font), size(size), color(color), bold(bold), italic(italic) {}
    
    void apply(const std::string& text) override {
        std::cout << "Rendering '" << text << "' with font: " << font 
                  << ", size: " << size << ", color: " << color;
        if (bold) std::cout << ", bold";
        if (italic) std::cout << ", italic";
        std::cout << std::endl;
    }
    
private:
    bool bold;
    bool italic;
};

class CharacterFormatFactory {
private:
    std::unordered_map<std::string, std::shared_ptr<CharacterFormat>> formats;
    
    std::string getKey(const std::string& font, int size, const std::string& color, bool bold, bool italic) {
        return font + "|" + std::to_string(size) + "|" + color + "|" + 
               (bold ? "B" : "") + "|" + (italic ? "I" : "");
    }
    
public:
    std::shared_ptr<CharacterFormat> getFormat(const std::string& font, int size, 
                                              const std::string& color, bool bold, bool italic) {
        std::string key = getKey(font, size, color, bold, italic);
        
        if (formats.find(key) == formats.end()) {
            std::cout << "Creating new format: " << font << " " << size << "pt" << std::endl;
            formats[key] = std::make_shared<ConcreteCharacterFormat>(font, size, color, bold, italic);
        } else {
            std::cout << "Reusing existing format: " << font << " " << size << "pt" << std::endl;
        }
        
        return formats[key];
    }
    
    int getTotalFormats() const {
        return formats.size();
    }
};

class Character {
private:
    char symbol;
    std::shared_ptr<CharacterFormat> format;
    
public:
    Character(char symbol, std::shared_ptr<CharacterFormat> format)
        : symbol(symbol), format(format) {}
    
    void render() {
        std::string text(1, symbol);
        format->apply(text);
    }
};

// Example 3: Game Units
// Shows how Flyweight can be used for game objects

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

int main() {
    std::cout << "=== Flyweight Pattern Demo ===" << std::endl << std::endl;
    
    // Example 1: Forest Trees
    std::cout << "--- Forest Trees Example ---" << std::endl;
    
    TreeFactory treeFactory;
    
    // Create trees with shared types
    std::vector<Tree> forest;
    
    forest.emplace_back(10, 20, treeFactory.getTreeType("Oak", "Green", "Rough"));
    forest.emplace_back(30, 40, treeFactory.getTreeType("Oak", "Green", "Rough"));
    forest.emplace_back(50, 60, treeFactory.getTreeType("Oak", "Green", "Rough"));
    
    forest.emplace_back(15, 25, treeFactory.getTreeType("Pine", "Dark Green", "Smooth"));
    forest.emplace_back(35, 45, treeFactory.getTreeType("Pine", "Dark Green", "Smooth"));
    
    forest.emplace_back(20, 30, treeFactory.getTreeType("Oak", "Green", "Rough"));  // Reusing Oak
    
    std::cout << "\nDrawing forest:" << std::endl;
    for (const auto& tree : forest) {
        tree.draw();
    }
    
    std::cout << "\nTotal unique tree types: " << treeFactory.getTotalTreeTypes() << std::endl;
    std::cout << "Total trees in forest: " << forest.size() << std::endl;
    
    std::cout << std::endl;
    
    // Example 2: Text Editor Characters
    std::cout << "--- Text Editor Characters Example ---" << std::endl;
    
    CharacterFormatFactory formatFactory;
    
    std::vector<Character> document;
    
    document.emplace_back('H', formatFactory.getFormat("Arial", 12, "Black", true, false));
    document.emplace_back('e', formatFactory.getFormat("Arial", 12, "Black", false, false));
    document.emplace_back('l', formatFactory.getFormat("Arial", 12, "Black", false, false));
    document.emplace_back('l', formatFactory.getFormat("Arial", 12, "Black", false, false));
    document.emplace_back('o', formatFactory.getFormat("Arial", 12, "Black", false, false));
    
    document.emplace_back(' ', formatFactory.getFormat("Arial", 12, "Black", false, false));
    
    document.emplace_back('W', formatFactory.getFormat("Times New Roman", 14, "Blue", true, true));
    document.emplace_back('o', formatFactory.getFormat("Times New Roman", 14, "Blue", false, true));
    document.emplace_back('r', formatFactory.getFormat("Times New Roman", 14, "Blue", false, true));
    document.emplace_back('l', formatFactory.getFormat("Times New Roman", 14, "Blue", false, true));
    document.emplace_back('d', formatFactory.getFormat("Times New Roman", 14, "Blue", false, true));
    
    std::cout << "\nRendering document:" << std::endl;
    for (const auto& character : document) {
        character.render();
    }
    
    std::cout << "\nTotal unique formats: " << formatFactory.getTotalFormats() << std::endl;
    std::cout << "Total characters: " << document.size() << std::endl;
    
    std::cout << std::endl;
    
    // Example 3: Game Soldiers
    std::cout << "--- Game Soldiers Example ---" << std::endl;
    
    SoldierTypeFactory soldierFactory;
    
    std::vector<Soldier> army;
    
    army.emplace_back(10, 10, "Rifle", soldierFactory.getSoldierType("Camouflage", 5, "Private"));
    army.emplace_back(20, 20, "Rifle", soldierFactory.getSoldierType("Camouflage", 5, "Private"));
    army.emplace_back(30, 30, "Rifle", soldierFactory.getSoldierType("Camouflage", 5, "Private"));
    
    army.emplace_back(15, 15, "Sniper", soldierFactory.getSoldierType("Desert", 4, "Sergeant"));
    army.emplace_back(25, 25, "Sniper", soldierFactory.getSoldierType("Desert", 4, "Sergeant"));
    
    army.emplace_back(40, 40, "Machine Gun", soldierFactory.getSoldierType("Camouflage", 5, "Private"));  // Reusing
    
    std::cout << "\nRendering army:" << std::endl;
    for (const auto& soldier : army) {
        soldier.render();
    }
    
    std::cout << "\nTotal unique soldier types: " << soldierFactory.getTotalSoldierTypes() << std::endl;
    std::cout << "Total soldiers: " << army.size() << std::endl;
    
    return 0;
}
