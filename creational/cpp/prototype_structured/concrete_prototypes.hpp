#pragma once
#include "interfaces.hpp"

class Rectangle : public Prototype {
private:
    int width;
    int height;
    std::string color;
    
public:
    Rectangle(int w, int h, const std::string& c) : width(w), height(h), color(c) {}
    Rectangle(const Rectangle& other) : width(other.width), height(other.height), color(other.color) {}
    
    std::unique_ptr<Prototype> clone() const override { return std::make_unique<Rectangle>(*this); }
    void display() const override { std::cout << "Rectangle: " << width << "x" << height << ", Color: " << color << std::endl; }
    std::string getType() const override { return "Rectangle"; }
    
    void setWidth(int w) { width = w; }
    void setHeight(int h) { height = h; }
    void setColor(const std::string& c) { color = c; }
};

class Circle : public Prototype {
private:
    int radius;
    std::string color;
    
public:
    Circle(int r, const std::string& c) : radius(r), color(c) {}
    Circle(const Circle& other) : radius(other.radius), color(other.color) {}
    
    std::unique_ptr<Prototype> clone() const override { return std::make_unique<Circle>(*this); }
    void display() const override { std::cout << "Circle: Radius " << radius << ", Color: " << color << std::endl; }
    std::string getType() const override { return "Circle"; }
    
    void setRadius(int r) { radius = r; }
    void setColor(const std::string& c) { color = c; }
};

class Employee : public Prototype {
private:
    std::string name;
    std::string department;
    int salary;
    std::unique_ptr<std::string[]> skills;
    int skillCount;
    
public:
    Employee(const std::string& n, const std::string& d, int s) : name(n), department(d), salary(s), skillCount(0) {}
    Employee(const Employee& other) : name(other.name), department(other.department), salary(other.salary), skillCount(other.skillCount) {
        if (other.skillCount > 0) {
            skills = std::make_unique<std::string[]>(other.skillCount);
            for (int i = 0; i < other.skillCount; i++) {
                skills[i] = other.skills[i];
            }
        }
    }
    
    std::unique_ptr<Prototype> clone() const override { return std::make_unique<Employee>(*this); }
    void display() const override {
        std::cout << "Employee: " << name << ", Dept: " << department << ", Salary: $" << salary << std::endl;
        std::cout << "Skills: ";
        for (int i = 0; i < skillCount; i++) {
            std::cout << skills[i];
            if (i < skillCount - 1) std::cout << ", ";
        }
        std::cout << std::endl;
    }
    std::string getType() const override { return "Employee"; }
    
    void addSkill(const std::string& skill) {
        auto newSkills = std::make_unique<std::string[]>(skillCount + 1);
        for (int i = 0; i < skillCount; i++) { newSkills[i] = skills[i]; }
        newSkills[skillCount] = skill;
        skills = std::move(newSkills);
        skillCount++;
    }
    void setName(const std::string& n) { name = n; }
    void setSalary(int s) { salary = s; }
};

class Document : public Prototype {
private:
    std::string title;
    std::string* content;
    
public:
    Document(const std::string& t, const std::string& c) : title(t), content(new std::string(c)) {}
    Document(const Document& other) : title(other.title), content(new std::string(*other.content)) {}
    ~Document() { delete content; }
    
    std::unique_ptr<Prototype> clone() const override { return std::make_unique<Document>(*this); }
    void display() const override {
        std::cout << "Document: " << title << std::endl;
        std::cout << "Content: " << *content << std::endl;
    }
    std::string getType() const override { return "Document"; }
    
    void appendContent(const std::string& text) { *content += text; }
    void setTitle(const std::string& t) { title = t; }
};
