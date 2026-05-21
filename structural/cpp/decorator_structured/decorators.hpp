#pragma once
#include "components.hpp"
#include <memory>
#include <iostream>

class CoffeeDecorator : public Coffee {
protected:
    std::shared_ptr<Coffee> decoratedCoffee;
public:
    CoffeeDecorator(std::shared_ptr<Coffee> coffee) : decoratedCoffee(coffee) {}
    virtual double getCost() override { return decoratedCoffee->getCost(); }
    virtual std::string getDescription() override { return decoratedCoffee->getDescription(); }
};

class MilkDecorator : public CoffeeDecorator {
public:
    MilkDecorator(std::shared_ptr<Coffee> coffee) : CoffeeDecorator(coffee) {}
    double getCost() override { return CoffeeDecorator::getCost() + 0.5; }
    std::string getDescription() override { return CoffeeDecorator::getDescription() + ", Milk"; }
};

class SugarDecorator : public CoffeeDecorator {
public:
    SugarDecorator(std::shared_ptr<Coffee> coffee) : CoffeeDecorator(coffee) {}
    double getCost() override { return CoffeeDecorator::getCost() + 0.2; }
    std::string getDescription() override { return CoffeeDecorator::getDescription() + ", Sugar"; }
};

class WhippedCreamDecorator : public CoffeeDecorator {
public:
    WhippedCreamDecorator(std::shared_ptr<Coffee> coffee) : CoffeeDecorator(coffee) {}
    double getCost() override { return CoffeeDecorator::getCost() + 1.0; }
    std::string getDescription() override { return CoffeeDecorator::getDescription() + ", Whipped Cream"; }
};

class TextDecorator : public TextComponent {
protected:
    std::shared_ptr<TextComponent> wrappedText;
public:
    TextDecorator(std::shared_ptr<TextComponent> text) : wrappedText(text) {}
    virtual std::string getText() override { return wrappedText->getText(); }
};

class BoldDecorator : public TextDecorator {
public:
    BoldDecorator(std::shared_ptr<TextComponent> text) : TextDecorator(text) {}
    std::string getText() override { return "<b>" + TextDecorator::getText() + "</b>"; }
};

class ItalicDecorator : public TextDecorator {
public:
    ItalicDecorator(std::shared_ptr<TextComponent> text) : TextDecorator(text) {}
    std::string getText() override { return "<i>" + TextDecorator::getText() + "</i>"; }
};

class UnderlineDecorator : public TextDecorator {
public:
    UnderlineDecorator(std::shared_ptr<TextComponent> text) : TextDecorator(text) {}
    std::string getText() override { return "<u>" + TextDecorator::getText() + "</u>"; }
};

class DataSourceDecorator : public DataSource {
protected:
    std::shared_ptr<DataSource> wrappedSource;
public:
    DataSourceDecorator(std::shared_ptr<DataSource> source) : wrappedSource(source) {}
    virtual void writeData(std::string data) override { wrappedSource->writeData(data); }
    virtual std::string readData() override { return wrappedSource->readData(); }
};

class EncryptionDecorator : public DataSourceDecorator {
public:
    EncryptionDecorator(std::shared_ptr<DataSource> source) : DataSourceDecorator(source) {}
    void writeData(std::string data) override {
        std::string encrypted = "[ENCRYPTED]" + data + "[ENCRYPTED]";
        std::cout << "Encrypting data..." << std::endl;
        wrappedSource->writeData(encrypted);
    }
    std::string readData() override {
        std::string data = wrappedSource->readData();
        std::cout << "Decrypting data..." << std::endl;
        if (data.find("[ENCRYPTED]") == 0) { data = data.substr(11, data.length() - 22); }
        return data;
    }
};

class CompressionDecorator : public DataSourceDecorator {
public:
    CompressionDecorator(std::shared_ptr<DataSource> source) : DataSourceDecorator(source) {}
    void writeData(std::string data) override {
        std::string compressed = "[COMPRESSED]" + data + "[COMPRESSED]";
        std::cout << "Compressing data..." << std::endl;
        wrappedSource->writeData(compressed);
    }
    std::string readData() override {
        std::string data = wrappedSource->readData();
        std::cout << "Decompressing data..." << std::endl;
        if (data.find("[COMPRESSED]") == 0) { data = data.substr(12, data.length() - 24); }
        return data;
    }
};
