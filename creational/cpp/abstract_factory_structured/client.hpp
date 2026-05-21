#pragma once
#include "interfaces.hpp"

class Application {
private:
    std::unique_ptr<Button> button;
    std::unique_ptr<Checkbox> checkbox;
    
public:
    Application(std::unique_ptr<GUIFactory> factory) {
        button = factory->createButton();
        checkbox = factory->createCheckbox();
    }
    
    void renderUI() {
        std::cout << "Rendering UI components..." << std::endl;
        std::cout << "Button: " << button->getName() << std::endl;
        std::cout << "Checkbox: " << checkbox->getName() << std::endl;
        
        button->render();
        checkbox->render();
    }
    
    void interact() {
        std::cout << "\nUser interaction..." << std::endl;
        button->click();
        checkbox->check();
    }
};
