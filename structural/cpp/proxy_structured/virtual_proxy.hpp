#pragma once
#include <string>
#include <memory>

class Image {
public:
    virtual ~Image() = default;
    virtual void display() = 0;
};

class RealImage : public Image {
private:
    std::string filename;
    
    void loadFromDisk() {
        std::cout << "Loading " << filename << " from disk..." << std::endl;
    }
    
public:
    RealImage(const std::string& filename) : filename(filename) {
        loadFromDisk();
    }
    
    void display() override {
        std::cout << "Displaying " << filename << std::endl;
    }
};

class ProxyImage : public Image {
private:
    std::string filename;
    std::unique_ptr<RealImage> realImage;
    
public:
    ProxyImage(const std::string& filename) : filename(filename) {}
    
    void display() override {
        if (!realImage) {
            std::cout << "Creating real image on first access..." << std::endl;
            realImage = std::make_unique<RealImage>(filename);
        }
        realImage->display();
    }
};
