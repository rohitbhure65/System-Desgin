#pragma once
#include <string>
#include <iostream>

class Coffee {
public:
    virtual ~Coffee() = default;
    virtual double getCost() = 0;
    virtual std::string getDescription() = 0;
};

class SimpleCoffee : public Coffee {
public:
    double getCost() override { return 2.0; }
    std::string getDescription() override { return "Simple Coffee"; }
};

class TextComponent {
public:
    virtual ~TextComponent() = default;
    virtual std::string getText() = 0;
};

class SimpleText : public TextComponent {
private:
    std::string text;
public:
    SimpleText(const std::string& text) : text(text) {}
    std::string getText() override { return text; }
};

class DataSource {
public:
    virtual ~DataSource() = default;
    virtual void writeData(std::string data) = 0;
    virtual std::string readData() = 0;
};

class FileDataSource : public DataSource {
private:
    std::string data;
public:
    void writeData(std::string data) override {
        this->data = data;
        std::cout << "Writing data to file: " << data << std::endl;
    }
    std::string readData() override {
        std::cout << "Reading data from file: " << data << std::endl;
        return data;
    }
};
