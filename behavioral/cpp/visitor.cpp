/*
 * VISITOR DESIGN PATTERN
 * 
 * WHAT IS IT?
 * The Visitor pattern lets you define a new operation without changing the classes of the elements on which it operates.
 * It separates the algorithm from the object structure it operates on.
 * 
 * WHY DOES IT EXIST?
 * - When you need to add operations to a complex object structure without changing the structure
 * - When you want to perform operations across different object types
 * - When you want to centralize related operations in a single class
 * 
 * WHEN TO USE IT?
 * - When you have a complex object structure with different types of elements
 * - When you need to perform many unrelated operations on these elements
 * - When the object structure is stable but you want to add new operations frequently
 * - Common use cases: document processing, compiler AST traversal, file system operations, shopping cart calculations
 * 
 * PROS:
 * - Open/Closed Principle (can add new operations without changing element classes)
 * - Single Responsibility Principle (moves related operations to a single visitor)
 * - Can accumulate state while traversing the object structure
 * - Works well with Composite pattern
 * 
 * CONS:
 * - Adding new element classes requires updating all visitors
 * - Can violate encapsulation by exposing element internals
 * - Can lead to complex visitor hierarchies
 * - May make the code harder to understand
 * 
 * REAL-WORLD ANALOGY:
 * Think of a tax inspector visiting different types of businesses. The inspector (visitor) visits a restaurant, a retail store, and a factory (elements). Each business type calculates taxes differently. The inspector knows how to calculate taxes for each type but doesn't change how the businesses operate. You can add new types of inspections (health inspector, fire inspector) without changing the businesses.
 */

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <map>

// Visitor interface - declares visit methods for each concrete element
class Visitor {
public:
    virtual ~Visitor() = default;
    virtual void visit(class Book* book) = 0;
    virtual void visit(class Fruit* fruit) = 0;
    virtual void visit(class Electronic* electronic) = 0;
};

// Element interface - declares the accept method
class Item {
public:
    virtual ~Item() = default;
    virtual void accept(Visitor* visitor) = 0;
    virtual double getPrice() const = 0;
};

// Concrete Element 1: Book
class Book : public Item {
private:
    std::string title;
    std::string author;
    double price;
    
public:
    Book(const std::string& title, const std::string& author, double price)
        : title(title), author(author), price(price) {}
    
    void accept(Visitor* visitor) override {
        visitor->visit(this);
    }
    
    double getPrice() const override {
        return price;
    }
    
    std::string getTitle() const { return title; }
    std::string getAuthor() const { return author; }
};

// Concrete Element 2: Fruit
class Fruit : public Item {
private:
    std::string name;
    double price;
    double weight;
    
public:
    Fruit(const std::string& name, double price, double weight)
        : name(name), price(price), weight(weight) {}
    
    void accept(Visitor* visitor) override {
        visitor->visit(this);
    }
    
    double getPrice() const override {
        return price;
    }
    
    std::string getName() const { return name; }
    double getWeight() const { return weight; }
};

// Concrete Element 3: Electronic
class Electronic : public Item {
private:
    std::string model;
    std::string brand;
    double price;
    
public:
    Electronic(const std::string& brand, const std::string& model, double price)
        : model(model), brand(brand), price(price) {}
    
    void accept(Visitor* visitor) override {
        visitor->visit(this);
    }
    
    double getPrice() const override {
        return price;
    }
    
    std::string getModel() const { return model; }
    std::string getBrand() const { return brand; }
};

// Concrete Visitor 1: Price Calculator
class PriceCalculator : public Visitor {
private:
    double totalPrice;
    
public:
    PriceCalculator() : totalPrice(0) {}
    
    void visit(Book* book) override {
        totalPrice += book->getPrice();
        std::cout << "Book: " << book->getTitle() << " - $" << book->getPrice() << std::endl;
    }
    
    void visit(Fruit* fruit) override {
        totalPrice += fruit->getPrice();
        std::cout << "Fruit: " << fruit->getName() << " - $" << fruit->getPrice() << std::endl;
    }
    
    void visit(Electronic* electronic) override {
        totalPrice += electronic->getPrice();
        std::cout << "Electronic: " << electronic->getBrand() << " " << electronic->getModel() 
                  << " - $" << electronic->getPrice() << std::endl;
    }
    
    double getTotalPrice() const {
        return totalPrice;
    }
};

// Concrete Visitor 2: Description Generator
class DescriptionGenerator : public Visitor {
public:
    void visit(Book* book) override {
        std::cout << "Book: \"" << book->getTitle() << "\" by " << book->getAuthor() 
                  << " - A great read!" << std::endl;
    }
    
    void visit(Fruit* fruit) override {
        std::cout << "Fruit: " << fruit->getName() << " (" << fruit->getWeight() << "kg) - Fresh and healthy!" << std::endl;
    }
    
    void visit(Electronic* electronic) override {
        std::cout << "Electronic: " << electronic->getBrand() << " " << electronic->getModel() 
                  << " - High-tech gadget!" << std::endl;
    }
};

// Concrete Visitor 3: Tax Calculator
class TaxCalculator : public Visitor {
private:
    double totalTax;
    
public:
    TaxCalculator() : totalTax(0) {}
    
    void visit(Book* book) override {
        double tax = book->getPrice() * 0.05;  // 5% tax on books
        totalTax += tax;
        std::cout << "Book tax: $" << tax << std::endl;
    }
    
    void visit(Fruit* fruit) override {
        double tax = fruit->getPrice() * 0.02;  // 2% tax on food
        totalTax += tax;
        std::cout << "Fruit tax: $" << tax << std::endl;
    }
    
    void visit(Electronic* electronic) override {
        double tax = electronic->getPrice() * 0.10;  // 10% tax on electronics
        totalTax += tax;
        std::cout << "Electronic tax: $" << tax << std::endl;
    }
    
    double getTotalTax() const {
        return totalTax;
    }
};

// Object Structure - manages the elements
class ShoppingCart {
private:
    std::vector<std::unique_ptr<Item>> items;
    
public:
    void addItem(std::unique_ptr<Item> item) {
        items.push_back(std::move(item));
    }
    
    void acceptVisitor(Visitor* visitor) {
        for (const auto& item : items) {
            item->accept(visitor);
        }
    }
};

// Example 2: File System Visitor
// Shows how Visitor can be used for file system operations

class File;
class Directory;

class FileSystemVisitor {
public:
    virtual ~FileSystemVisitor() = default;
    virtual void visit(File* file) = 0;
    virtual void visit(Directory* directory) = 0;
};

class FileSystemNode {
public:
    virtual ~FileSystemNode() = default;
    virtual void accept(FileSystemVisitor* visitor) = 0;
    virtual std::string getName() const = 0;
    virtual int getSize() const = 0;
};

class File : public FileSystemNode {
private:
    std::string name;
    int size;
    
public:
    File(const std::string& name, int size) : name(name), size(size) {}
    
    void accept(FileSystemVisitor* visitor) override {
        visitor->visit(this);
    }
    
    std::string getName() const override { return name; }
    int getSize() const override { return size; }
};

class Directory : public FileSystemNode {
private:
    std::string name;
    std::vector<std::shared_ptr<FileSystemNode>> children;
    
public:
    Directory(const std::string& name) : name(name) {}
    
    void addChild(std::shared_ptr<FileSystemNode> child) {
        children.push_back(child);
    }
    
    void accept(FileSystemVisitor* visitor) override {
        visitor->visit(this);
    }
    
    std::string getName() const override { return name; }
    int getSize() const override {
        int total = 0;
        for (const auto& child : children) {
            total += child->getSize();
        }
        return total;
    }
};

class SizeCalculator : public FileSystemVisitor {
private:
    int totalSize;
    
public:
    SizeCalculator() : totalSize(0) {}
    
    void visit(File* file) override {
        totalSize += file->getSize();
        std::cout << "File: " << file->getName() << " - " << file->getSize() << " bytes" << std::endl;
    }
    
    void visit(Directory* directory) override {
        std::cout << "Directory: " << directory->getName() << " - " << directory->getSize() << " bytes" << std::endl;
        totalSize += directory->getSize();
    }
    
    int getTotalSize() const {
        return totalSize;
    }
};

class XMLExporter : public FileSystemVisitor {
public:
    void visit(File* file) override {
        std::cout << "  <file name=\"" << file->getName() << "\" size=\"" << file->getSize() << "\"/>" << std::endl;
    }
    
    void visit(Directory* directory) override {
        std::cout << "  <directory name=\"" << directory->getName() << "\" size=\"" << directory->getSize() << "\">" << std::endl;
    }
};

// Example 3: Employee Salary Calculator
// Shows how Visitor can be used for salary calculations

class Employee;
class Manager;
class Developer;
class Designer;

class SalaryVisitor {
public:
    virtual ~SalaryVisitor() = default;
    virtual void visit(Employee* employee) = 0;
    virtual void visit(Manager* manager) = 0;
    virtual void visit(Developer* developer) = 0;
    virtual void visit(Designer* designer) = 0;
};

class Employee {
public:
    virtual ~Employee() = default;
    virtual void accept(SalaryVisitor* visitor) = 0;
    virtual std::string getName() const = 0;
    virtual double getBaseSalary() const = 0;
};

class Manager : public Employee {
private:
    std::string name;
    double baseSalary;
    double bonus;
    
public:
    Manager(const std::string& name, double salary, double bonus)
        : name(name), baseSalary(salary), bonus(bonus) {}
    
    void accept(SalaryVisitor* visitor) override {
        visitor->visit(this);
    }
    
    std::string getName() const override { return name; }
    double getBaseSalary() const override { return baseSalary; }
    double getBonus() const { return bonus; }
};

class Developer : public Employee {
private:
    std::string name;
    double baseSalary;
    int overtimeHours;
    
public:
    Developer(const std::string& name, double salary, int overtime)
        : name(name), baseSalary(salary), overtimeHours(overtime) {}
    
    void accept(SalaryVisitor* visitor) override {
        visitor->visit(this);
    }
    
    std::string getName() const override { return name; }
    double getBaseSalary() const override { return baseSalary; }
    int getOvertimeHours() const { return overtimeHours; }
};

class Designer : public Employee {
private:
    std::string name;
    double baseSalary;
    int projectsCompleted;
    
public:
    Designer(const std::string& name, double salary, int projects)
        : name(name), baseSalary(salary), projectsCompleted(projects) {}
    
    void accept(SalaryVisitor* visitor) override {
        visitor->visit(this);
    }
    
    std::string getName() const override { return name; }
    double getBaseSalary() const override { return baseSalary; }
    int getProjectsCompleted() const { return projectsCompleted; }
};

class SalaryCalculator : public SalaryVisitor {
private:
    double totalSalary;
    
public:
    SalaryCalculator() : totalSalary(0) {}
    
    void visit(Employee* employee) override {
        double salary = employee->getBaseSalary();
        totalSalary += salary;
        std::cout << "Employee: " << employee->getName() << " - $" << salary << std::endl;
    }
    
    void visit(Manager* manager) override {
        double salary = manager->getBaseSalary() + manager->getBonus();
        totalSalary += salary;
        std::cout << "Manager: " << manager->getName() << " - $" << salary << " (base: $" 
                  << manager->getBaseSalary() << " + bonus: $" << manager->getBonus() << ")" << std::endl;
    }
    
    void visit(Developer* developer) override {
        double overtimePay = developer->getOvertimeHours() * 50.0;
        double salary = developer->getBaseSalary() + overtimePay;
        totalSalary += salary;
        std::cout << "Developer: " << developer->getName() << " - $" << salary 
                  << " (base: $" << developer->getBaseSalary() << " + overtime: $" << overtimePay << ")" << std::endl;
    }
    
    void visit(Designer* designer) override {
        double projectBonus = designer->getProjectsCompleted() * 500.0;
        double salary = designer->getBaseSalary() + projectBonus;
        totalSalary += salary;
        std::cout << "Designer: " << designer->getName() << " - $" << salary 
                  << " (base: $" << designer->getBaseSalary() << " + project bonus: $" << projectBonus << ")" << std::endl;
    }
    
    double getTotalSalary() const {
        return totalSalary;
    }
};

int main() {
    std::cout << "=== Visitor Pattern Demo ===" << std::endl << std::endl;
    
    // Example 1: Shopping Cart
    std::cout << "--- Shopping Cart Example ---" << std::endl;
    
    ShoppingCart cart;
    cart.addItem(std::make_unique<Book>("Design Patterns", "Erich Gamma", 49.99));
    cart.addItem(std::make_unique<Fruit>("Apple", 1.99, 0.5));
    cart.addItem(std::make_unique<Electronic>("Apple", "iPhone 15", 999.99));
    
    std::cout << "\nCalculating total price:" << std::endl;
    PriceCalculator priceCalc;
    cart.acceptVisitor(&priceCalc);
    std::cout << "Total: $" << priceCalc.getTotalPrice() << std::endl;
    
    std::cout << "\nGenerating descriptions:" << std::endl;
    DescriptionGenerator descGen;
    cart.acceptVisitor(&descGen);
    
    std::cout << "\nCalculating tax:" << std::endl;
    TaxCalculator taxCalc;
    cart.acceptVisitor(&taxCalc);
    std::cout << "Total tax: $" << taxCalc.getTotalTax() << std::endl;
    
    // Example 2: File System
    std::cout << "\n--- File System Example ---" << std::endl;
    
    auto root = std::make_shared<Directory>("root");
    auto file1 = std::make_shared<File>("document.txt", 1024);
    auto file2 = std::make_shared<File>("image.jpg", 2048);
    auto subdir = std::make_shared<Directory>("subdir");
    auto file3 = std::make_shared<File>("data.csv", 512);
    
    subdir->addChild(file3);
    root->addChild(file1);
    root->addChild(file2);
    root->addChild(subdir);
    
    std::cout << "\nCalculating sizes:" << std::endl;
    SizeCalculator sizeCalc;
    root->accept(&sizeCalc);
    std::cout << "Total size: " << sizeCalc.getTotalSize() << " bytes" << std::endl;
    
    std::cout << "\nExporting to XML:" << std::endl;
    std::cout << "<filesystem>" << std::endl;
    XMLExporter xmlExporter;
    root->accept(&xmlExporter);
    std::cout << "</filesystem>" << std::endl;
    
    // Example 3: Employee Salary
    std::cout << "\n--- Employee Salary Example ---" << std::endl;
    
    std::vector<std::unique_ptr<Employee>> employees;
    employees.push_back(std::make_unique<Manager>("Alice", 80000, 20000));
    employees.push_back(std::make_unique<Developer>("Bob", 70000, 10));
    employees.push_back(std::make_unique<Designer>("Charlie", 65000, 5));
    
    std::cout << "\nCalculating total salary:" << std::endl;
    SalaryCalculator salaryCalc;
    for (const auto& emp : employees) {
        emp->accept(&salaryCalc);
    }
    std::cout << "Total salary: $" << salaryCalc.getTotalSalary() << std::endl;
    
    return 0;
}
