#pragma once
#include "components.hpp"
#include <vector>
#include <algorithm>
#include <iostream>

class Directory : public FileSystemComponent {
private:
    std::string name;
    std::vector<std::shared_ptr<FileSystemComponent>> children;
public:
    Directory(const std::string& name) : name(name) {}
    void add(std::shared_ptr<FileSystemComponent> component) override { children.push_back(component); }
    void remove(std::shared_ptr<FileSystemComponent> component) override {
        children.erase(std::remove(children.begin(), children.end(), component), children.end());
    }
    std::shared_ptr<FileSystemComponent> getChild(int index) override {
        if (index >= 0 && index < children.size()) return children[index];
        return nullptr;
    }
    void display(const std::string& indent = "") override {
        std::cout << indent << "Directory: " << name << " (" << getSize() << " bytes)" << std::endl;
        for (const auto& child : children) child->display(indent + "  ");
    }
    int getSize() override {
        int totalSize = 0;
        for (const auto& child : children) totalSize += child->getSize();
        return totalSize;
    }
};

class Manager : public Employee {
private:
    std::string name;
    std::string title;
    std::vector<std::shared_ptr<Employee>> subordinates;
public:
    Manager(const std::string& name, const std::string& title) : name(name), title(title) {}
    void add(std::shared_ptr<Employee> employee) override { subordinates.push_back(employee); }
    void remove(std::shared_ptr<Employee> employee) override {
        subordinates.erase(std::remove(subordinates.begin(), subordinates.end(), employee), subordinates.end());
    }
    void print(const std::string& indent = "") override {
        std::cout << indent << "Manager: " << name << " - " << title << std::endl;
        for (const auto& subordinate : subordinates) subordinate->print(indent + "  ");
    }
};

class GraphicGroup : public Graphic {
private:
    std::string name;
    std::vector<std::shared_ptr<Graphic>> graphics;
public:
    GraphicGroup(const std::string& name) : name(name) {}
    void add(std::shared_ptr<Graphic> graphic) { graphics.push_back(graphic); }
    void remove(std::shared_ptr<Graphic> graphic) {
        graphics.erase(std::remove(graphics.begin(), graphics.end(), graphic), graphics.end());
    }
    void draw(const std::string& indent = "") override {
        std::cout << indent << "Group: " << name << std::endl;
        for (const auto& graphic : graphics) graphic->draw(indent + "  ");
    }
};
