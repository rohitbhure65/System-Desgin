#include "shopping_cart.hpp"
#include "file_system.hpp"
#include "employee_salary.hpp"
#include <iostream>
#include <memory>

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
