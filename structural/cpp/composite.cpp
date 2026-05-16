/*
 * COMPOSITE DESIGN PATTERN
 * 
 * WHAT IS IT?
 * The Composite pattern lets you compose objects into tree structures and work with these structures as if they were individual objects.
 * It treats individual objects and compositions of objects uniformly.
 * 
 * WHY DOES IT EXIST?
 * - When you want to represent part-whole hierarchies of objects
 * - When you want clients to ignore the difference between compositions of objects and individual objects
 * - When you want to treat individual objects and compositions uniformly
 * 
 * WHEN TO USE IT?
 * - When you have a tree structure of objects (e.g., file systems, organization charts, UI component hierarchies)
 * - When you want to simplify client code by treating individual and composite objects the same way
 * - When the structure of your objects forms a recursive hierarchy
 * - Common use cases: file systems, graphics scenes, UI component trees, organization structures
 * 
 * PROS:
 * - Simplifies client code (can treat complex and simple objects uniformly)
 * - Open/Closed Principle (easy to add new kinds of components)
 * - Flexible tree structure (can build complex structures from simple parts)
 * - Makes it easier to add new types of components
 * 
 * CONS:
 * - Can make the design overly general (hard to restrict components)
 * - May be difficult to restrict the types of components in a composite
 * - Can make the code harder to understand due to recursion
 * - Performance overhead for traversing large trees
 * 
 * REAL-WORLD ANALOGY:
 * Think of a file system. A file is a simple object (leaf), while a folder is a composite that can contain both files and other folders. When you delete a folder, you want to delete everything inside it recursively. The file system treats files and folders uniformly in many operations (like copying, moving, or calculating size).
 */

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>

// Component Interface - declares the interface for objects in the composition
class FileSystemComponent {
public:
    virtual ~FileSystemComponent() = default;
    virtual void display(const std::string& indent = "") = 0;
    virtual int getSize() = 0;
    virtual void add(std::shared_ptr<FileSystemComponent> component) {
        // Default implementation for leaf nodes
        std::cout << "Cannot add to a file" << std::endl;
    }
    virtual void remove(std::shared_ptr<FileSystemComponent> component) {
        // Default implementation for leaf nodes
        std::cout << "Cannot remove from a file" << std::endl;
    }
    virtual std::shared_ptr<FileSystemComponent> getChild(int index) {
        // Default implementation for leaf nodes
        return nullptr;
    }
};

// Leaf - represents individual objects in the composition
class File : public FileSystemComponent {
private:
    std::string name;
    int size;
    
public:
    File(const std::string& name, int size) : name(name), size(size) {}
    
    void display(const std::string& indent = "") override {
        std::cout << indent << "File: " << name << " (" << size << " bytes)" << std::endl;
    }
    
    int getSize() override {
        return size;
    }
};

// Composite - represents groups of objects that can contain other composites
class Directory : public FileSystemComponent {
private:
    std::string name;
    std::vector<std::shared_ptr<FileSystemComponent>> children;
    
public:
    Directory(const std::string& name) : name(name) {}
    
    void add(std::shared_ptr<FileSystemComponent> component) override {
        children.push_back(component);
    }
    
    void remove(std::shared_ptr<FileSystemComponent> component) override {
        children.erase(
            std::remove(children.begin(), children.end(), component),
            children.end()
        );
    }
    
    std::shared_ptr<FileSystemComponent> getChild(int index) override {
        if (index >= 0 && index < children.size()) {
            return children[index];
        }
        return nullptr;
    }
    
    void display(const std::string& indent = "") override {
        std::cout << indent << "Directory: " << name << " (" << getSize() << " bytes)" << std::endl;
        for (const auto& child : children) {
            child->display(indent + "  ");
        }
    }
    
    int getSize() override {
        int totalSize = 0;
        for (const auto& child : children) {
            totalSize += child->getSize();
        }
        return totalSize;
    }
};

// Example 2: Organization Structure
// Shows how Composite can be used for organizational hierarchies

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

class Worker : public Employee {
private:
    std::string name;
    std::string position;
    
public:
    Worker(const std::string& name, const std::string& position)
        : name(name), position(position) {}
    
    void print(const std::string& indent = "") override {
        std::cout << indent << "Employee: " << name << " - " << position << std::endl;
    }
};

class Manager : public Employee {
private:
    std::string name;
    std::string title;
    std::vector<std::shared_ptr<Employee>> subordinates;
    
public:
    Manager(const std::string& name, const std::string& title)
        : name(name), title(title) {}
    
    void add(std::shared_ptr<Employee> employee) override {
        subordinates.push_back(employee);
    }
    
    void remove(std::shared_ptr<Employee> employee) override {
        subordinates.erase(
            std::remove(subordinates.begin(), subordinates.end(), employee),
            subordinates.end()
        );
    }
    
    void print(const std::string& indent = "") override {
        std::cout << indent << "Manager: " << name << " - " << title << std::endl;
        for (const auto& subordinate : subordinates) {
            subordinate->print(indent + "  ");
        }
    }
};

// Example 3: Graphic Shapes Composite
// Shows how Composite can be used for graphics

class Graphic {
public:
    virtual ~Graphic() = default;
    virtual void draw(const std::string& indent = "") = 0;
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

class GraphicGroup : public Graphic {
private:
    std::string name;
    std::vector<std::shared_ptr<Graphic>> graphics;
    
public:
    GraphicGroup(const std::string& name) : name(name) {}
    
    void add(std::shared_ptr<Graphic> graphic) {
        graphics.push_back(graphic);
    }
    
    void remove(std::shared_ptr<Graphic> graphic) {
        graphics.erase(
            std::remove(graphics.begin(), graphics.end(), graphic),
            graphics.end()
        );
    }
    
    void draw(const std::string& indent = "") override {
        std::cout << indent << "Group: " << name << std::endl;
        for (const auto& graphic : graphics) {
            graphic->draw(indent + "  ");
        }
    }
};

int main() {
    std::cout << "=== Composite Pattern Demo ===" << std::endl << std::endl;
    
    // Example 1: File System
    std::cout << "--- File System Example ---" << std::endl;
    
    auto file1 = std::make_shared<File>("file1.txt", 100);
    auto file2 = std::make_shared<File>("file2.txt", 200);
    auto file3 = std::make_shared<File>("file3.txt", 150);
    
    auto dir1 = std::make_shared<Directory>("Documents");
    auto dir2 = std::make_shared<Directory>("Pictures");
    auto rootDir = std::make_shared<Directory>("Root");
    
    dir1->add(file1);
    dir1->add(file2);
    
    dir2->add(file3);
    
    rootDir->add(dir1);
    rootDir->add(dir2);
    
    std::cout << "\nFile System Structure:" << std::endl;
    rootDir->display();
    
    std::cout << "\nTotal size of Root directory: " << rootDir->getSize() << " bytes" << std::endl;
    
    std::cout << std::endl;
    
    // Example 2: Organization Structure
    std::cout << "--- Organization Structure Example ---" << std::endl;
    
    auto ceo = std::make_shared<Manager>("John Smith", "CEO");
    auto cto = std::make_shared<Manager>("Alice Johnson", "CTO");
    auto cfo = std::make_shared<Manager>("Bob Williams", "CFO");
    
    auto dev1 = std::make_shared<Worker>("Developer 1", "Senior Developer");
    auto dev2 = std::make_shared<Worker>("Developer 2", "Junior Developer");
    auto accountant = std::make_shared<Worker>("Accountant", "Senior Accountant");
    
    cto->add(dev1);
    cto->add(dev2);
    cfo->add(accountant);
    
    ceo->add(cto);
    ceo->add(cfo);
    
    std::cout << "\nOrganization Structure:" << std::endl;
    ceo->print();
    
    std::cout << std::endl;
    
    // Example 3: Graphic Shapes
    std::cout << "--- Graphic Shapes Example ---" << std::endl;
    
    auto circle1 = std::make_shared<Circle>("Red Circle");
    auto circle2 = std::make_shared<Circle>("Blue Circle");
    auto square1 = std::make_shared<Square>("Green Square");
    
    auto group1 = std::make_shared<GraphicGroup>("Shapes Group 1");
    auto group2 = std::make_shared<GraphicGroup>("Shapes Group 2");
    auto mainGroup = std::make_shared<GraphicGroup>("Main Group");
    
    group1->add(circle1);
    group1->add(square1);
    
    group2->add(circle2);
    
    mainGroup->add(group1);
    mainGroup->add(group2);
    
    std::cout << "\nGraphic Structure:" << std::endl;
    mainGroup->draw();
    
    return 0;
}
