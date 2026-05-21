#pragma once
#include <string>
#include <unordered_map>
#include <memory>
#include <vector>

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

class TreeFactory {
private:
    std::unordered_map<std::string, std::shared_ptr<TreeType>> treeTypes;
    
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
