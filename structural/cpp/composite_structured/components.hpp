#pragma once
#include <string>
#include <memory>
#include <iostream>

class FileSystemComponent {
public:
    virtual ~FileSystemComponent() = default;
    virtual void display(const std::string& indent = "") = 0;
    virtual int getSize() = 0;
    virtual void add(std::shared_ptr<FileSystemComponent> component) {
        std::cout << "Cannot add to a file" << std::endl;
    }
    virtual void remove(std::shared_ptr<FileSystemComponent> component) {
        std::cout << "Cannot remove from a file" << std::endl;
    }
    virtual std::shared_ptr<FileSystemComponent> getChild(int index) {
        return nullptr;
    }
};

class Employee {
public:
    virtual ~Employee() = default;
    virtual void print(const std::string& indent = "") = 0;
    virtual void add(std::shared_ptr<Employee> employee) {
        std::cout << "Cannot add to a regular employee" << std::endl;
    }
    virtual void remove(std::shared_ptr<Employee> employee) {
        std::cout << "Cannot remove from a regular employee" << std::endl;
    }
};

class Graphic {
public:
    virtual ~Graphic() = default;
    virtual void draw(const std::string& indent = "") = 0;
};
