/*
 * PROTOTYPE DESIGN PATTERN
 * 
 * WHAT IS IT?
 * The Prototype pattern specifies the kinds of objects to create using a prototypical instance, and creates new objects by copying this prototype.
 * It allows you to create new objects by cloning existing ones instead of creating them from scratch.
 * 
 * WHY DOES IT EXIST?
 * - When creating an object is expensive or complex
 * - When you want to avoid creating subclasses just to create objects
 * - When you want to hide the concrete classes from the client
 * - When you need to create objects at runtime that are similar to existing objects
 * 
 * WHEN TO USE IT?
 * - When the classes to instantiate are specified at runtime
 * - When you want to avoid building a class hierarchy of factories that parallels the class hierarchy of products
 * - When instances of a class can have one of only a few different combinations of state
 * - When creating an object is expensive (e.g., requires database access, network I/O, or complex initialization)
 * - Common use cases: game objects, document templates, graphic shapes, configuration objects
 * 
 * PROS:
 * - Allows you to clone objects without coupling to their concrete classes
 * - Can avoid repetitive initialization code
 * - Can be more efficient than creating objects from scratch
 * - Lets you add or remove products at runtime
 * - Works well with complex object graphs
 * 
 * CONS:
 * - Cloning complex objects with circular references can be tricky
 * - Shallow vs. deep copying must be carefully considered
 * - May be difficult to implement if the object's internal state is not easily accessible
 * - Can violate encapsulation if the clone method needs access to private fields
 * 
 * REAL-WORLD ANALOGY:
 * Think of a cell division in biology. A cell (prototype) divides to create an identical copy of itself. The new cell starts with the same DNA and characteristics as the original, but can then evolve independently. Similarly, in software, you can clone an object and then modify it as needed.
 */

#include <iostream>
#include <string>
#include <memory>
#include <unordered_map>

// Prototype interface - declares the clone method
class Prototype {
public:
    virtual ~Prototype() = default;
    virtual std::unique_ptr<Prototype> clone() const = 0;
    virtual void display() const = 0;
    virtual std::string getType() const = 0;
};

// Concrete Prototype 1: Rectangle
class Rectangle : public Prototype {
private:
    int width;
    int height;
    std::string color;
    
public:
    Rectangle(int w, int h, const std::string& c) 
        : width(w), height(h), color(c) {}
    
    // Copy constructor used for cloning
    Rectangle(const Rectangle& other) 
        : width(other.width), height(other.height), color(other.color) {}
    
    std::unique_ptr<Prototype> clone() const override {
        return std::make_unique<Rectangle>(*this);  // Use copy constructor
    }
    
    void display() const override {
        std::cout << "Rectangle: " << width << "x" << height 
                  << ", Color: " << color << std::endl;
    }
    
    std::string getType() const override {
        return "Rectangle";
    }
    
    // Methods to modify the cloned object
    void setWidth(int w) { width = w; }
    void setHeight(int h) { height = h; }
    void setColor(const std::string& c) { color = c; }
};

// Concrete Prototype 2: Circle
class Circle : public Prototype {
private:
    int radius;
    std::string color;
    
public:
    Circle(int r, const std::string& c) : radius(r), color(c) {}
    
    // Copy constructor used for cloning
    Circle(const Circle& other) : radius(other.radius), color(other.color) {}
    
    std::unique_ptr<Prototype> clone() const override {
        return std::make_unique<Circle>(*this);  // Use copy constructor
    }
    
    void display() const override {
        std::cout << "Circle: Radius " << radius 
                  << ", Color: " << color << std::endl;
    }
    
    std::string getType() const override {
        return "Circle";
    }
    
    void setRadius(int r) { radius = r; }
    void setColor(const std::string& c) { color = c; }
};

// Prototype Registry - manages a collection of prototypes
class PrototypeRegistry {
private:
    std::unordered_map<std::string, std::unique_ptr<Prototype>> prototypes;
    
public:
    void registerPrototype(const std::string& key, std::unique_ptr<Prototype> prototype) {
        prototypes[key] = std::move(prototype);
    }
    
    std::unique_ptr<Prototype> clone(const std::string& key) {
        auto it = prototypes.find(key);
        if (it != prototypes.end()) {
            return it->second->clone();
        }
        return nullptr;
    }
};

// Example: Complex object with deep copy
class Employee : public Prototype {
private:
    std::string name;
    std::string department;
    int salary;
    std::unique_ptr<std::string[]> skills;  // Dynamic array
    int skillCount;
    
public:
    Employee(const std::string& n, const std::string& d, int s)
        : name(n), department(d), salary(s), skillCount(0) {}
    
    // Deep copy constructor
    Employee(const Employee& other) 
        : name(other.name), department(other.department), salary(other.salary), 
          skillCount(other.skillCount) {
        if (other.skillCount > 0) {
            skills = std::make_unique<std::string[]>(other.skillCount);
            for (int i = 0; i < other.skillCount; i++) {
                skills[i] = other.skills[i];
            }
        }
    }
    
    std::unique_ptr<Prototype> clone() const override {
        return std::make_unique<Employee>(*this);
    }
    
    void display() const override {
        std::cout << "Employee: " << name << ", Dept: " << department 
                  << ", Salary: $" << salary << std::endl;
        std::cout << "Skills: ";
        for (int i = 0; i < skillCount; i++) {
            std::cout << skills[i];
            if (i < skillCount - 1) std::cout << ", ";
        }
        std::cout << std::endl;
    }
    
    std::string getType() const override {
        return "Employee";
    }
    
    void addSkill(const std::string& skill) {
        auto newSkills = std::make_unique<std::string[]>(skillCount + 1);
        for (int i = 0; i < skillCount; i++) {
            newSkills[i] = skills[i];
        }
        newSkills[skillCount] = skill;
        skills = std::move(newSkills);
        skillCount++;
    }
    
    void setName(const std::string& n) { name = n; }
    void setSalary(int s) { salary = s; }
};

// Example: Document with shallow vs deep copy
class Document : public Prototype {
private:
    std::string title;
    std::string* content;  // Pointer to demonstrate shallow vs deep copy
    
public:
    Document(const std::string& t, const std::string& c) 
        : title(t), content(new std::string(c)) {}
    
    // Deep copy constructor
    Document(const Document& other) 
        : title(other.title), content(new std::string(*other.content)) {}
    
    ~Document() {
        delete content;
    }
    
    std::unique_ptr<Prototype> clone() const override {
        return std::make_unique<Document>(*this);
    }
    
    void display() const override {
        std::cout << "Document: " << title << std::endl;
        std::cout << "Content: " << *content << std::endl;
    }
    
    std::string getType() const override {
        return "Document";
    }
    
    void appendContent(const std::string& text) {
        *content += text;
    }
    
    void setTitle(const std::string& t) { title = t; }
};

int main() {
    std::cout << "=== Prototype Pattern Demo ===" << std::endl << std::endl;
    
    // Example 1: Basic Prototype with Registry
    std::cout << "--- Basic Prototype with Registry ---" << std::endl;
    
    PrototypeRegistry registry;
    
    // Register prototypes
    registry.registerPrototype("red_rectangle", 
        std::make_unique<Rectangle>(10, 5, "red"));
    registry.registerPrototype("blue_circle", 
        std::make_unique<Circle>(7, "blue"));
    
    // Clone and modify prototypes
    std::cout << "\nCloning red rectangle:" << std::endl;
    auto rect1 = registry.clone("red_rectangle");
    rect1->display();
    
    std::cout << "\nCloning and modifying red rectangle:" << std::endl;
    auto rect2 = registry.clone("red_rectangle");
    auto* rect2Ptr = dynamic_cast<Rectangle*>(rect2.get());
    if (rect2Ptr) {
        rect2Ptr->setWidth(20);
        rect2Ptr->setColor("green");
    }
    rect2->display();
    
    std::cout << "\nCloning blue circle:" << std::endl;
    auto circle1 = registry.clone("blue_circle");
    circle1->display();
    
    // Example 2: Complex object with deep copy
    std::cout << "\n--- Complex Object with Deep Copy ---" << std::endl;
    
    Employee originalEmployee("John Doe", "Engineering", 75000);
    originalEmployee.addSkill("C++");
    originalEmployee.addSkill("Python");
    originalEmployee.addSkill("JavaScript");
    
    std::cout << "\nOriginal employee:" << std::endl;
    originalEmployee.display();
    
    std::cout << "\nCloned employee:" << std::endl;
    auto clonedEmployee = std::unique_ptr<Employee>(
        dynamic_cast<Employee*>(originalEmployee.clone().release())
    );
    clonedEmployee->setName("Jane Smith");
    clonedEmployee->setSalary(80000);
    clonedEmployee->addSkill("Go");
    clonedEmployee->display();
    
    std::cout << "\nOriginal employee (unchanged):" << std::endl;
    originalEmployee.display();
    
    // Example 3: Document with deep copy
    std::cout << "\n--- Document with Deep Copy ---" << std::endl;
    
    Document originalDoc("Project Plan", "This document outlines the project plan.");
    std::cout << "\nOriginal document:" << std::endl;
    originalDoc.display();
    
    std::cout << "\nCloned document:" << std::endl;
    auto clonedDoc = std::unique_ptr<Document>(
        dynamic_cast<Document*>(originalDoc.clone().release())
    );
    clonedDoc->setTitle("Project Plan - Copy");
    clonedDoc->appendContent(" It includes milestones and deliverables.");
    clonedDoc->display();
    
    std::cout << "\nOriginal document (unchanged):" << std::endl;
    originalDoc.display();
    
    return 0;
}
