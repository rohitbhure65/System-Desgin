import { SalaryVisitor, Employee } from './interfaces';

export class Manager implements Employee {
  private name: string;
  private baseSalary: number;
  private bonus: number;
  
  constructor(name: string, salary: number, bonus: number) {
    this.name = name;
    this.baseSalary = salary;
    this.bonus = bonus;
  }
  
  accept(visitor: SalaryVisitor): void {
    visitor.visitManager(this);
  }
  
  getName(): string { return this.name; }
  getBaseSalary(): number { return this.baseSalary; }
  getBonus(): number { return this.bonus; }
}

export class Developer implements Employee {
  private name: string;
  private baseSalary: number;
  private overtimeHours: number;
  
  constructor(name: string, salary: number, overtime: number) {
    this.name = name;
    this.baseSalary = salary;
    this.overtimeHours = overtime;
  }
  
  accept(visitor: SalaryVisitor): void {
    visitor.visitDeveloper(this);
  }
  
  getName(): string { return this.name; }
  getBaseSalary(): number { return this.baseSalary; }
  getOvertimeHours(): number { return this.overtimeHours; }
}

export class Designer implements Employee {
  private name: string;
  private baseSalary: number;
  private projectsCompleted: number;
  
  constructor(name: string, salary: number, projects: number) {
    this.name = name;
    this.baseSalary = salary;
    this.projectsCompleted = projects;
  }
  
  accept(visitor: SalaryVisitor): void {
    visitor.visitDesigner(this);
  }
  
  getName(): string { return this.name; }
  getBaseSalary(): number { return this.baseSalary; }
  getProjectsCompleted(): number { return this.projectsCompleted; }
}

export class BaseEmployee implements Employee {
  private name: string;
  private baseSalary: number;
  
  constructor(name: string, salary: number) {
    this.name = name;
    this.baseSalary = salary;
  }
  
  accept(visitor: SalaryVisitor): void {
    visitor.visitEmployee(this);
  }
  
  getName(): string { return this.name; }
  getBaseSalary(): number { return this.baseSalary; }
}

export class SalaryCalculator implements SalaryVisitor {
  private totalSalary: number = 0;
  
  visitEmployee(employee: any): void {
    const salary = employee.getBaseSalary();
    this.totalSalary += salary;
    console.log(`Employee: ${employee.getName()} - $${salary}`);
  }
  
  visitManager(manager: any): void {
    const salary = manager.getBaseSalary() + manager.getBonus();
    this.totalSalary += salary;
    console.log(`Manager: ${manager.getName()} - $${salary} (base: $${manager.getBaseSalary()} + bonus: $${manager.getBonus()})`);
  }
  
  visitDeveloper(developer: any): void {
    const overtimePay = developer.getOvertimeHours() * 50.0;
    const salary = developer.getBaseSalary() + overtimePay;
    this.totalSalary += salary;
    console.log(`Developer: ${developer.getName()} - $${salary} (base: $${developer.getBaseSalary()} + overtime: $${overtimePay})`);
  }
  
  visitDesigner(designer: any): void {
    const projectBonus = designer.getProjectsCompleted() * 500.0;
    const salary = designer.getBaseSalary() + projectBonus;
    this.totalSalary += salary;
    console.log(`Designer: ${designer.getName()} - $${salary} (base: $${designer.getBaseSalary()} + project bonus: $${projectBonus})`);
  }
  
  getTotalSalary(): number {
    return this.totalSalary;
  }
}
