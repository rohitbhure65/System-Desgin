#include "components.hpp"
#include "decorators.hpp"
#include <iostream>

int main() {
    std::cout << "=== Decorator Pattern Demo ===" << std::endl << std::endl;
    
    std::cout << "--- Coffee Shop Example ---" << std::endl;
    std::shared_ptr<Coffee> coffee = std::make_shared<SimpleCoffee>();
    std::cout << coffee->getDescription() << " $" << coffee->getCost() << std::endl;
    
    coffee = std::make_shared<MilkDecorator>(coffee);
    std::cout << coffee->getDescription() << " $" << coffee->getCost() << std::endl;
    coffee = std::make_shared<SugarDecorator>(coffee);
    std::cout << coffee->getDescription() << " $" << coffee->getCost() << std::endl;
    coffee = std::make_shared<WhippedCreamDecorator>(coffee);
    std::cout << coffee->getDescription() << " $" << coffee->getCost() << std::endl;
    std::cout << std::endl;
    
    std::cout << "--- Text Formatting Example ---" << std::endl;
    std::shared_ptr<TextComponent> text = std::make_shared<SimpleText>("Hello World");
    std::cout << "Original: " << text->getText() << std::endl;
    
    text = std::make_shared<BoldDecorator>(text);
    std::cout << "Bold: " << text->getText() << std::endl;
    text = std::make_shared<ItalicDecorator>(text);
    std::cout << "Bold + Italic: " << text->getText() << std::endl;
    text = std::make_shared<UnderlineDecorator>(text);
    std::cout << "Bold + Italic + Underline: " << text->getText() << std::endl;
    std::cout << std::endl;
    
    std::cout << "--- Data Stream Processing Example ---" << std::endl;
    std::shared_ptr<DataSource> dataSource = std::make_shared<FileDataSource>();
    std::cout << "\nWriting plain data:" << std::endl;
    dataSource->writeData("Important Data");
    std::cout << "Reading: " << dataSource->readData() << std::endl;
    
    std::cout << "\nWriting encrypted data:" << std::endl;
    dataSource = std::make_shared<EncryptionDecorator>(dataSource);
    dataSource->writeData("Secret Data");
    std::cout << "Reading: " << dataSource->readData() << std::endl;
    
    std::cout << "\nWriting encrypted and compressed data:" << std::endl;
    dataSource = std::make_shared<CompressionDecorator>(dataSource);
    dataSource->writeData("Very Secret Data");
    std::cout << "Reading: " << dataSource->readData() << std::endl;
    
    return 0;
}
