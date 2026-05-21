#pragma once
#include <string>
#include <vector>
#include <memory>

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
