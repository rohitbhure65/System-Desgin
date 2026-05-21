#pragma once
#include "components.hpp"
#include <iostream>

class File : public FileSystemComponent {
private:
    std::string name;
    int size;
public:
    File(const std::string& name, int size) : name(name), size(size) {}
    void display(const std::string& indent = "") override {
        std::cout << indent << "File: " << name << " (" << size << " bytes)" << std::endl;
    }
    int getSize() override { return size; }
};

class Worker : public Employee {
private:
    std::string name;
    std::string position;
public:
    Worker(const std::string& name, const std::string& position) : name(name), position(position) {}
    void print(const std::string& indent = "") override {
        std::cout << indent << "Employee: " << name << " - " << position << std::endl;
    }
};

class Circle : public Graphic {
private:
    std::string name;
public:
    Circle(const std::string& name) : name(name) {}
    void draw(const std::string& indent = "") override {
        std::cout << indent << "Drawing Circle: " << name << std::endl;
    }
};

class Square : public Graphic {
private:
    std::string name;
public:
    Square(const std::string& name) : name(name) {}
    void draw(const std::string& indent = "") override {
        std::cout << indent << "Drawing Square: " << name << std::endl;
    }
};
