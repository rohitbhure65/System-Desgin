#pragma once
#include <string>
#include <unordered_map>
#include <memory>
#include <vector>

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
