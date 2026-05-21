#include "leaves.hpp"
#include "composites.hpp"
#include <iostream>

int main() {
    std::cout << "=== Composite Pattern Demo ===" << std::endl << std::endl;
    
    std::cout << "--- File System Example ---" << std::endl;
    auto file1 = std::make_shared<File>("file1.txt", 100);
    auto file2 = std::make_shared<File>("file2.txt", 200);
    auto file3 = std::make_shared<File>("file3.txt", 150);
    
    auto dir1 = std::make_shared<Directory>("Documents");
    auto dir2 = std::make_shared<Directory>("Pictures");
    auto rootDir = std::make_shared<Directory>("Root");
    
    dir1->add(file1); dir1->add(file2);
    dir2->add(file3);
    rootDir->add(dir1); rootDir->add(dir2);
    
    std::cout << "\nFile System Structure:" << std::endl;
    rootDir->display();
    std::cout << "\nTotal size of Root directory: " << rootDir->getSize() << " bytes" << std::endl << std::endl;
    
    std::cout << "--- Organization Structure Example ---" << std::endl;
    auto ceo = std::make_shared<Manager>("John Smith", "CEO");
    auto cto = std::make_shared<Manager>("Alice Johnson", "CTO");
    auto cfo = std::make_shared<Manager>("Bob Williams", "CFO");
    
    auto dev1 = std::make_shared<Worker>("Developer 1", "Senior Developer");
    auto dev2 = std::make_shared<Worker>("Developer 2", "Junior Developer");
    auto accountant = std::make_shared<Worker>("Accountant", "Senior Accountant");
    
    cto->add(dev1); cto->add(dev2); cfo->add(accountant);
    ceo->add(cto); ceo->add(cfo);
    
    std::cout << "\nOrganization Structure:" << std::endl;
    ceo->print();
    std::cout << std::endl;
    
    std::cout << "--- Graphic Shapes Example ---" << std::endl;
    auto circle1 = std::make_shared<Circle>("Red Circle");
    auto circle2 = std::make_shared<Circle>("Blue Circle");
    auto square1 = std::make_shared<Square>("Green Square");
    
    auto group1 = std::make_shared<GraphicGroup>("Shapes Group 1");
    auto group2 = std::make_shared<GraphicGroup>("Shapes Group 2");
    auto mainGroup = std::make_shared<GraphicGroup>("Main Group");
    
    group1->add(circle1); group1->add(square1);
    group2->add(circle2);
    mainGroup->add(group1); mainGroup->add(group2);
    
    std::cout << "\nGraphic Structure:" << std::endl;
    mainGroup->draw();
    
    return 0;
}
