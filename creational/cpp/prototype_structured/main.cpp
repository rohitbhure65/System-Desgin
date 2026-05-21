#include "interfaces.hpp"
#include "concrete_prototypes.hpp"
#include "registry.hpp"

int main() {
    std::cout << "=== Prototype Pattern Demo ===" << std::endl << std::endl;
    
    std::cout << "--- Basic Prototype with Registry ---" << std::endl;
    
    PrototypeRegistry registry;
    
    registry.registerPrototype("red_rectangle", std::make_unique<Rectangle>(10, 5, "red"));
    registry.registerPrototype("blue_circle", std::make_unique<Circle>(7, "blue"));
    
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
    
    std::cout << "\n--- Complex Object with Deep Copy ---" << std::endl;
    
    Employee originalEmployee("John Doe", "Engineering", 75000);
    originalEmployee.addSkill("C++");
    originalEmployee.addSkill("Python");
    originalEmployee.addSkill("JavaScript");
    
    std::cout << "\nOriginal employee:" << std::endl;
    originalEmployee.display();
    
    std::cout << "\nCloned employee:" << std::endl;
    auto clonedEmployee = std::unique_ptr<Employee>(dynamic_cast<Employee*>(originalEmployee.clone().release()));
    clonedEmployee->setName("Jane Smith");
    clonedEmployee->setSalary(80000);
    clonedEmployee->addSkill("Go");
    clonedEmployee->display();
    
    std::cout << "\nOriginal employee (unchanged):" << std::endl;
    originalEmployee.display();
    
    std::cout << "\n--- Document with Deep Copy ---" << std::endl;
    
    Document originalDoc("Project Plan", "This document outlines the project plan.");
    std::cout << "\nOriginal document:" << std::endl;
    originalDoc.display();
    
    std::cout << "\nCloned document:" << std::endl;
    auto clonedDoc = std::unique_ptr<Document>(dynamic_cast<Document*>(originalDoc.clone().release()));
    clonedDoc->setTitle("Project Plan - Copy");
    clonedDoc->appendContent(" It includes milestones and deliverables.");
    clonedDoc->display();
    
    std::cout << "\nOriginal document (unchanged):" << std::endl;
    originalDoc.display();
    
    return 0;
}
