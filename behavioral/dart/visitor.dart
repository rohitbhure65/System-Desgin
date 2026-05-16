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
abstract class Visitor {
  void visitBook(Book book);
  void visitFruit(Fruit fruit);
  void visitElectronic(Electronic electronic);
}

// Element interface - declares the accept method
abstract class Item {
  void accept(Visitor visitor);
  double getPrice();
}

// Concrete Element 1: Book
class Book extends Item {
  final String _title;
  final String _author;
  final double _price;
  
  Book(this._title, this._author, this._price);
  
  @override
  void accept(Visitor visitor) {
    visitor.visitBook(this);
  }
  
  @override
  double getPrice() => _price;
  
  String get title => _title;
  String get author => _author;
}

// Concrete Element 2: Fruit
class Fruit extends Item {
  final String _name;
  final double _price;
  final double _weight;
  
  Fruit(this._name, this._price, this._weight);
  
  @override
  void accept(Visitor visitor) {
    visitor.visitFruit(this);
  }
  
  @override
  double getPrice() => _price;
  
  String get name => _name;
  double get weight => _weight;
}

// Concrete Element 3: Electronic
class Electronic extends Item {
  final String _model;
  final String _brand;
  final double _price;
  
  Electronic(this._brand, this._model, this._price);
  
  @override
  void accept(Visitor visitor) {
    visitor.visitElectronic(this);
  }
  
  @override
  double getPrice() => _price;
  
  String get model => _model;
  String get brand => _brand;
}

// Concrete Visitor 1: Price Calculator
class PriceCalculator implements Visitor {
  double _totalPrice = 0;
  
  @override
  void visitBook(Book book) {
    _totalPrice += book.getPrice();
    print('Book: ${book.title} - \$${book.getPrice()}');
  }
  
  @override
  void visitFruit(Fruit fruit) {
    _totalPrice += fruit.getPrice();
    print('Fruit: ${fruit.name} - \$${fruit.getPrice()}');
  }
  
  @override
  void visitElectronic(Electronic electronic) {
    _totalPrice += electronic.getPrice();
    print('Electronic: ${electronic.brand} ${electronic.model} - \$${electronic.getPrice()}');
  }
  
  double get totalPrice => _totalPrice;
}

// Concrete Visitor 2: Description Generator
class DescriptionGenerator implements Visitor {
  @override
  void visitBook(Book book) {
    print('Book: "${book.title}" by ${book.author} - A great read!');
  }
  
  @override
  void visitFruit(Fruit fruit) {
    print('Fruit: ${fruit.name} (${fruit.weight}kg) - Fresh and healthy!');
  }
  
  @override
  void visitElectronic(Electronic electronic) {
    print('Electronic: ${electronic.brand} ${electronic.model} - High-tech gadget!');
  }
}

// Concrete Visitor 3: Tax Calculator
class TaxCalculator implements Visitor {
  double _totalTax = 0;
  
  @override
  void visitBook(Book book) {
    final tax = book.getPrice() * 0.05;  // 5% tax on books
    _totalTax += tax;
    print('Book tax: \$${tax}');
  }
  
  @override
  void visitFruit(Fruit fruit) {
    final tax = fruit.getPrice() * 0.02;  // 2% tax on food
    _totalTax += tax;
    print('Fruit tax: \$${tax}');
  }
  
  @override
  void visitElectronic(Electronic electronic) {
    final tax = electronic.getPrice() * 0.10;  // 10% tax on electronics
    _totalTax += tax;
    print('Electronic tax: \$${tax}');
  }
  
  double get totalTax => _totalTax;
}

// Object Structure - manages the elements
class ShoppingCart {
  final List<Item> _items = [];
  
  void addItem(Item item) {
    _items.add(item);
  }
  
  void acceptVisitor(Visitor visitor) {
    for (final item in _items) {
      item.accept(visitor);
    }
  }
}

// Example 2: File System Visitor
// Shows how Visitor can be used for file system operations

abstract class FileSystemVisitor {
  void visitFile(File file);
  void visitDirectory(Directory directory);
}

abstract class FileSystemNode {
  void accept(FileSystemVisitor visitor);
  String getName();
  int getSize();
}

class File implements FileSystemNode {
  final String _name;
  final int _size;
  
  File(this._name, this._size);
  
  @override
  void accept(FileSystemVisitor visitor) {
    visitor.visitFile(this);
  }
  
  @override
  String getName() => _name;
  
  @override
  int getSize() => _size;
}

class Directory implements FileSystemNode {
  final String _name;
  final List<FileSystemNode> _children = [];
  
  Directory(this._name);
  
  void addChild(FileSystemNode child) {
    _children.add(child);
  }
  
  @override
  void accept(FileSystemVisitor visitor) {
    visitor.visitDirectory(this);
  }
  
  @override
  String getName() => _name;
  
  @override
  int getSize() {
    return _children.fold(0, (total, child) => total + child.getSize());
  }
}

class SizeCalculator implements FileSystemVisitor {
  int _totalSize = 0;
  
  @override
  void visitFile(File file) {
    _totalSize += file.getSize();
    print('File: ${file.getName()} - ${file.getSize()} bytes');
  }
  
  @override
  void visitDirectory(Directory directory) {
    print('Directory: ${directory.getName()} - ${directory.getSize()} bytes');
    _totalSize += directory.getSize();
  }
  
  int get totalSize => _totalSize;
}

class XMLExporter implements FileSystemVisitor {
  @override
  void visitFile(File file) {
    print('  <file name="${file.getName()}" size="${file.getSize()}"/>');
  }
  
  @override
  void visitDirectory(Directory directory) {
    print('  <directory name="${directory.getName()}" size="${directory.getSize()}">');
  }
}

// Example 3: Employee Salary Calculator
// Shows how Visitor can be used for salary calculations

abstract class SalaryVisitor {
  void visitEmployee(Employee employee);
  void visitManager(Manager manager);
  void visitDeveloper(Developer developer);
  void visitDesigner(Designer designer);
}

abstract class Employee {
  void accept(SalaryVisitor visitor);
  String getName();
  double getBaseSalary();
}

class Manager extends Employee {
  final String _name;
  final double _baseSalary;
  final double _bonus;
  
  Manager(this._name, this._baseSalary, this._bonus);
  
  @override
  void accept(SalaryVisitor visitor) {
    visitor.visitManager(this);
  }
  
  @override
  String getName() => _name;
  
  @override
  double getBaseSalary() => _baseSalary;
  
  double get bonus => _bonus;
}

class Developer extends Employee {
  final String _name;
  final double _baseSalary;
  final int _overtimeHours;
  
  Developer(this._name, this._baseSalary, this._overtimeHours);
  
  @override
  void accept(SalaryVisitor visitor) {
    visitor.visitDeveloper(this);
  }
  
  @override
  String getName() => _name;
  
  @override
  double getBaseSalary() => _baseSalary;
  
  int get overtimeHours => _overtimeHours;
}

class Designer extends Employee {
  final String _name;
  final double _baseSalary;
  final int _projectsCompleted;
  
  Designer(this._name, this._baseSalary, this._projectsCompleted);
  
  @override
  void accept(SalaryVisitor visitor) {
    visitor.visitDesigner(this);
  }
  
  @override
  String getName() => _name;
  
  @override
  double getBaseSalary() => _baseSalary;
  
  int get projectsCompleted => _projectsCompleted;
}

class BaseEmployee extends Employee {
  final String _name;
  final double _baseSalary;
  
  BaseEmployee(this._name, this._baseSalary);
  
  @override
  void accept(SalaryVisitor visitor) {
    visitor.visitEmployee(this);
  }
  
  @override
  String getName() => _name;
  
  @override
  double getBaseSalary() => _baseSalary;
}

class SalaryCalculator implements SalaryVisitor {
  double _totalSalary = 0;
  
  @override
  void visitEmployee(Employee employee) {
    final salary = employee.getBaseSalary();
    _totalSalary += salary;
    print('Employee: ${employee.getName()} - \$$salary');
  }
  
  @override
  void visitManager(Manager manager) {
    final salary = manager.getBaseSalary() + manager.bonus;
    _totalSalary += salary;
    print('Manager: ${manager.getName()} - \$$salary (base: \$${manager.getBaseSalary()} + bonus: \$${manager.bonus})');
  }
  
  @override
  void visitDeveloper(Developer developer) {
    final overtimePay = developer.overtimeHours * 50.0;
    final salary = developer.getBaseSalary() + overtimePay;
    _totalSalary += salary;
    print('Developer: ${developer.getName()} - \$$salary (base: \$${developer.getBaseSalary()} + overtime: \$$overtimePay)');
  }
  
  @override
  void visitDesigner(Designer designer) {
    final projectBonus = designer.projectsCompleted * 500.0;
    final salary = designer.getBaseSalary() + projectBonus;
    _totalSalary += salary;
    print('Designer: ${designer.getName()} - \$$salary (base: \$${designer.getBaseSalary()} + project bonus: \$$projectBonus)');
  }
  
  double get totalSalary => _totalSalary;
}

// Demo code
void main() {
  print('=== Visitor Pattern Demo ===\n');
  
  // Example 1: Shopping Cart
  print('--- Shopping Cart Example ---');
  
  final cart = ShoppingCart();
  cart.addItem(Book('Design Patterns', 'Erich Gamma', 49.99));
  cart.addItem(Fruit('Apple', 1.99, 0.5));
  cart.addItem(Electronic('Apple', 'iPhone 15', 999.99));
  
  print('\nCalculating total price:');
  final priceCalc = PriceCalculator();
  cart.acceptVisitor(priceCalc);
  print('Total: \$${priceCalc.totalPrice}');
  
  print('\nGenerating descriptions:');
  final descGen = DescriptionGenerator();
  cart.acceptVisitor(descGen);
  
  print('\nCalculating tax:');
  final taxCalc = TaxCalculator();
  cart.acceptVisitor(taxCalc);
  print('Total tax: \$${taxCalc.totalTax}');
  
  // Example 2: File System
  print('\n--- File System Example ---');
  
  final root = Directory('root');
  final file1 = File('document.txt', 1024);
  final file2 = File('image.jpg', 2048);
  final subdir = Directory('subdir');
  final file3 = File('data.csv', 512);
  
  subdir.addChild(file3);
  root.addChild(file1);
  root.addChild(file2);
  root.addChild(subdir);
  
  print('\nCalculating sizes:');
  final sizeCalc = SizeCalculator();
  root.accept(sizeCalc);
  print('Total size: ${sizeCalc.totalSize} bytes');
  
  print('\nExporting to XML:');
  print('<filesystem>');
  final xmlExporter = XMLExporter();
  root.accept(xmlExporter);
  print('</filesystem>');
  
  // Example 3: Employee Salary
  print('\n--- Employee Salary Example ---');
  
  final employees = <Employee>[
    Manager('Alice', 80000, 20000),
    Developer('Bob', 70000, 10),
    Designer('Charlie', 65000, 5)
  ];
  
  print('\nCalculating total salary:');
  final salaryCalc = SalaryCalculator();
  for (final emp in employees) {
    emp.accept(salaryCalc);
  }
  print('Total salary: \$${salaryCalc.totalSalary}');
}
