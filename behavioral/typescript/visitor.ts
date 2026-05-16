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

// Visitor interface - declares visit methods for each concrete element
interface Visitor {
  visitBook(book: Book): void;
  visitFruit(fruit: Fruit): void;
  visitElectronic(electronic: Electronic): void;
}

// Element interface - declares the accept method
interface Item {
  accept(visitor: Visitor): void;
  getPrice(): number;
}

// Concrete Element 1: Book
class Book implements Item {
  private title: string;
  private author: string;
  private price: number;
  
  constructor(title: string, author: string, price: number) {
    this.title = title;
    this.author = author;
    this.price = price;
  }
  
  accept(visitor: Visitor): void {
    visitor.visitBook(this);
  }
  
  getPrice(): number {
    return this.price;
  }
  
  getTitle(): string { return this.title; }
  getAuthor(): string { return this.author; }
}

// Concrete Element 2: Fruit
class Fruit implements Item {
  private name: string;
  private price: number;
  private weight: number;
  
  constructor(name: string, price: number, weight: number) {
    this.name = name;
    this.price = price;
    this.weight = weight;
  }
  
  accept(visitor: Visitor): void {
    visitor.visitFruit(this);
  }
  
  getPrice(): number {
    return this.price;
  }
  
  getName(): string { return this.name; }
  getWeight(): number { return this.weight; }
}

// Concrete Element 3: Electronic
class Electronic implements Item {
  private model: string;
  private brand: string;
  private price: number;
  
  constructor(brand: string, model: string, price: number) {
    this.brand = brand;
    this.model = model;
    this.price = price;
  }
  
  accept(visitor: Visitor): void {
    visitor.visitElectronic(this);
  }
  
  getPrice(): number {
    return this.price;
  }
  
  getModel(): string { return this.model; }
  getBrand(): string { return this.brand; }
}

// Concrete Visitor 1: Price Calculator
class PriceCalculator implements Visitor {
  private totalPrice: number = 0;
  
  visitBook(book: Book): void {
    this.totalPrice += book.getPrice();
    console.log(`Book: ${book.getTitle()} - $${book.getPrice()}`);
  }
  
  visitFruit(fruit: Fruit): void {
    this.totalPrice += fruit.getPrice();
    console.log(`Fruit: ${fruit.getName()} - $${fruit.getPrice()}`);
  }
  
  visitElectronic(electronic: Electronic): void {
    this.totalPrice += electronic.getPrice();
    console.log(`Electronic: ${electronic.getBrand()} ${electronic.getModel()} - $${electronic.getPrice()}`);
  }
  
  getTotalPrice(): number {
    return this.totalPrice;
  }
}

// Concrete Visitor 2: Description Generator
class DescriptionGenerator implements Visitor {
  visitBook(book: Book): void {
    console.log(`Book: "${book.getTitle()}" by ${book.getAuthor()} - A great read!`);
  }
  
  visitFruit(fruit: Fruit): void {
    console.log(`Fruit: ${fruit.getName()} (${fruit.getWeight()}kg) - Fresh and healthy!`);
  }
  
  visitElectronic(electronic: Electronic): void {
    console.log(`Electronic: ${electronic.getBrand()} ${electronic.getModel()} - High-tech gadget!`);
  }
}

// Concrete Visitor 3: Tax Calculator
class TaxCalculator implements Visitor {
  private totalTax: number = 0;
  
  visitBook(book: Book): void {
    const tax = book.getPrice() * 0.05;  // 5% tax on books
    this.totalTax += tax;
    console.log(`Book tax: $${tax}`);
  }
  
  visitFruit(fruit: Fruit): void {
    const tax = fruit.getPrice() * 0.02;  // 2% tax on food
    this.totalTax += tax;
    console.log(`Fruit tax: $${tax}`);
  }
  
  visitElectronic(electronic: Electronic): void {
    const tax = electronic.getPrice() * 0.10;  // 10% tax on electronics
    this.totalTax += tax;
    console.log(`Electronic tax: $${tax}`);
  }
  
  getTotalTax(): number {
    return this.totalTax;
  }
}

// Object Structure - manages the elements
class ShoppingCart {
  private items: Item[] = [];
  
  addItem(item: Item): void {
    this.items.push(item);
  }
  
  acceptVisitor(visitor: Visitor): void {
    for (const item of this.items) {
      item.accept(visitor);
    }
  }
}

// Example 2: File System Visitor
// Shows how Visitor can be used for file system operations

interface FileSystemVisitor {
  visitFile(file: File): void;
  visitDirectory(directory: Directory): void;
}

interface FileSystemNode {
  accept(visitor: FileSystemVisitor): void;
  getName(): string;
  getSize(): number;
}

class File implements FileSystemNode {
  private name: string;
  private size: number;
  
  constructor(name: string, size: number) {
    this.name = name;
    this.size = size;
  }
  
  accept(visitor: FileSystemVisitor): void {
    visitor.visitFile(this);
  }
  
  getName(): string { return this.name; }
  getSize(): number { return this.size; }
}

class Directory implements FileSystemNode {
  private name: string;
  private children: FileSystemNode[] = [];
  
  constructor(name: string) {
    this.name = name;
  }
  
  addChild(child: FileSystemNode): void {
    this.children.push(child);
  }
  
  accept(visitor: FileSystemVisitor): void {
    visitor.visitDirectory(this);
  }
  
  getName(): string { return this.name; }
  getSize(): number {
    return this.children.reduce((total, child) => total + child.getSize(), 0);
  }
}

class SizeCalculator implements FileSystemVisitor {
  private totalSize: number = 0;
  
  visitFile(file: File): void {
    this.totalSize += file.getSize();
    console.log(`File: ${file.getName()} - ${file.getSize()} bytes`);
  }
  
  visitDirectory(directory: Directory): void {
    console.log(`Directory: ${directory.getName()} - ${directory.getSize()} bytes`);
    this.totalSize += directory.getSize();
  }
  
  getTotalSize(): number {
    return this.totalSize;
  }
}

class XMLExporter implements FileSystemVisitor {
  visitFile(file: File): void {
    console.log(`  <file name="${file.getName()}" size="${file.getSize()}"/>`);
  }
  
  visitDirectory(directory: Directory): void {
    console.log(`  <directory name="${directory.getName()}" size="${directory.getSize()}">`);
  }
}

// Example 3: Employee Salary Calculator
// Shows how Visitor can be used for salary calculations

interface SalaryVisitor {
  visitEmployee(employee: Employee): void;
  visitManager(manager: Manager): void;
  visitDeveloper(developer: Developer): void;
  visitDesigner(designer: Designer): void;
}

interface Employee {
  accept(visitor: SalaryVisitor): void;
  getName(): string;
  getBaseSalary(): number;
}

class Manager implements Employee {
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

class Developer implements Employee {
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

class Designer implements Employee {
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

class BaseEmployee implements Employee {
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

class SalaryCalculator implements SalaryVisitor {
  private totalSalary: number = 0;
  
  visitEmployee(employee: Employee): void {
    const salary = employee.getBaseSalary();
    this.totalSalary += salary;
    console.log(`Employee: ${employee.getName()} - $${salary}`);
  }
  
  visitManager(manager: Manager): void {
    const salary = manager.getBaseSalary() + manager.getBonus();
    this.totalSalary += salary;
    console.log(`Manager: ${manager.getName()} - $${salary} (base: $${manager.getBaseSalary()} + bonus: $${manager.getBonus()})`);
  }
  
  visitDeveloper(developer: Developer): void {
    const overtimePay = developer.getOvertimeHours() * 50.0;
    const salary = developer.getBaseSalary() + overtimePay;
    this.totalSalary += salary;
    console.log(`Developer: ${developer.getName()} - $${salary} (base: $${developer.getBaseSalary()} + overtime: $${overtimePay})`);
  }
  
  visitDesigner(designer: Designer): void {
    const projectBonus = designer.getProjectsCompleted() * 500.0;
    const salary = designer.getBaseSalary() + projectBonus;
    this.totalSalary += salary;
    console.log(`Designer: ${designer.getName()} - $${salary} (base: $${designer.getBaseSalary()} + project bonus: $${projectBonus})`);
  }
  
  getTotalSalary(): number {
    return this.totalSalary;
  }
}

// Demo code
console.log('=== Visitor Pattern Demo ===\n');

// Example 1: Shopping Cart
console.log('--- Shopping Cart Example ---');

const cart = new ShoppingCart();
cart.addItem(new Book('Design Patterns', 'Erich Gamma', 49.99));
cart.addItem(new Fruit('Apple', 1.99, 0.5));
cart.addItem(new Electronic('Apple', 'iPhone 15', 999.99));

console.log('\nCalculating total price:');
const priceCalc = new PriceCalculator();
cart.acceptVisitor(priceCalc);
console.log(`Total: $${priceCalc.getTotalPrice()}`);

console.log('\nGenerating descriptions:');
const descGen = new DescriptionGenerator();
cart.acceptVisitor(descGen);

console.log('\nCalculating tax:');
const taxCalc = new TaxCalculator();
cart.acceptVisitor(taxCalc);
console.log(`Total tax: $${taxCalc.getTotalTax()}`);

// Example 2: File System
console.log('\n--- File System Example ---');

const root = new Directory('root');
const file1 = new File('document.txt', 1024);
const file2 = new File('image.jpg', 2048);
const subdir = new Directory('subdir');
const file3 = new File('data.csv', 512);

subdir.addChild(file3);
root.addChild(file1);
root.addChild(file2);
root.addChild(subdir);

console.log('\nCalculating sizes:');
const sizeCalc = new SizeCalculator();
root.accept(sizeCalc);
console.log(`Total size: ${sizeCalc.getTotalSize()} bytes`);

console.log('\nExporting to XML:');
console.log('<filesystem>');
const xmlExporter = new XMLExporter();
root.accept(xmlExporter);
console.log('</filesystem>');

// Example 3: Employee Salary
console.log('\n--- Employee Salary Example ---');

const employees: Employee[] = [
  new Manager('Alice', 80000, 20000),
  new Developer('Bob', 70000, 10),
  new Designer('Charlie', 65000, 5)
];

console.log('\nCalculating total salary:');
const salaryCalc = new SalaryCalculator();
for (const emp of employees) {
  emp.accept(salaryCalc);
}
console.log(`Total salary: $${salaryCalc.getTotalSalary()}`);
