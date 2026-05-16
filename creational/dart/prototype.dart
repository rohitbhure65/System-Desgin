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

// Prototype interface - declares the clone method
abstract class Prototype {
  Prototype clone();
  void display();
  String get type;
}

// Concrete Prototype 1: Rectangle
class Rectangle extends Prototype {
  int _width;
  int _height;
  String _color;
  
  Rectangle(this._width, this._height, this._color);
  
  // Clone method using named constructor for copying
  @override
  Rectangle clone() {
    return Rectangle(_width, _height, _color);
  }
  
  @override
  void display() {
    print('Rectangle: ${_width}x$_height, Color: $_color');
  }
  
  @override
  String get type => 'Rectangle';
  
  // Methods to modify the cloned object
  void setWidth(int width) {
    _width = width;
  }
  
  void setHeight(int height) {
    _height = height;
  }
  
  void setColor(String color) {
    _color = color;
  }
}

// Concrete Prototype 2: Circle
class Circle extends Prototype {
  int _radius;
  String _color;
  
  Circle(this._radius, this._color);
  
  @override
  Circle clone() {
    return Circle(_radius, _color);
  }
  
  @override
  void display() {
    print('Circle: Radius $_radius, Color: $_color');
  }
  
  @override
  String get type => 'Circle';
  
  void setRadius(int radius) {
    _radius = radius;
  }
  
  void setColor(String color) {
    _color = color;
  }
}

// Prototype Registry - manages a collection of prototypes
class PrototypeRegistry {
  final Map<String, Prototype> _prototypes = {};
  
  void registerPrototype(String key, Prototype prototype) {
    _prototypes[key] = prototype;
  }
  
  Prototype? clone(String key) {
    var prototype = _prototypes[key];
    return prototype?.clone();
  }
}

// Example: Complex object with deep copy
class Employee extends Prototype {
  String _name;
  String _department;
  int _salary;
  List<String> _skills;
  
  Employee(this._name, this._department, this._salary, [List<String>? skills])
      : _skills = skills ?? [];
  
  // Deep copy constructor
  @override
  Employee clone() {
    // Create a deep copy of the skills list
    var skillsCopy = List<String>.from(_skills);
    return Employee(_name, _department, _salary, skillsCopy);
  }
  
  @override
  void display() {
    print('Employee: $_name, Dept: $_department, Salary: \$$_salary');
    print('Skills: ${_skills.join(', ')}');
  }
  
  @override
  String get type => 'Employee';
  
  void addSkill(String skill) {
    _skills.add(skill);
  }
  
  void setName(String name) {
    _name = name;
  }
  
  void setSalary(int salary) {
    _salary = salary;
  }
}

// Example: Document with shallow vs deep copy
class Document extends Prototype {
  String _title;
  String _content;
  
  Document(this._title, this._content);
  
  @override
  Document clone() {
    // For strings, this is effectively a deep copy since strings are immutable in Dart
    return Document(_title, _content);
  }
  
  @override
  void display() {
    print('Document: $_title');
    print('Content: $_content');
  }
  
  @override
  String get type => 'Document';
  
  void appendContent(String text) {
    _content += text;
  }
  
  void setTitle(String title) {
    _title = title;
  }
}

// Example: Game Character with prototype
class GameCharacter extends Prototype {
  String _name;
  int _health;
  int _attack;
  int _defense;
  List<String> _inventory;
  
  GameCharacter(this._name, this._health, this._attack, this._defense,
      [List<String>? inventory])
      : _inventory = inventory ?? [];
  
  @override
  GameCharacter clone() {
    return GameCharacter(
        _name, _health, _attack, _defense, List<String>.from(_inventory));
  }
  
  @override
  void display() {
    print('Character: $_name');
    print('  Health: $_health, Attack: $_attack, Defense: $_defense');
    print('  Inventory: ${_inventory.join(', ')}');
  }
  
  @override
  String get type => 'GameCharacter';
  
  void addItem(String item) {
    _inventory.add(item);
  }
  
  void setName(String name) {
    _name = name;
  }
  
  void takeDamage(int amount) {
    _health = (_health - amount).clamp(0, double.infinity).toInt();
  }
}

// Demo code
void main() {
  print('=== Prototype Pattern Demo ===\n');
  
  // Example 1: Basic Prototype with Registry
  print('--- Basic Prototype with Registry ---');
  
  var registry = PrototypeRegistry();
  
  // Register prototypes
  registry.registerPrototype('red_rectangle', Rectangle(10, 5, 'red'));
  registry.registerPrototype('blue_circle', Circle(7, 'blue'));
  
  // Clone and modify prototypes
  print('\nCloning red rectangle:');
  var rect1 = registry.clone('red_rectangle');
  rect1?.display();
  
  print('\nCloning and modifying red rectangle:');
  var rect2 = registry.clone('red_rectangle');
  if (rect2 is Rectangle) {
    rect2.setWidth(20);
    rect2.setColor('green');
    rect2.display();
  }
  
  print('\nCloning blue circle:');
  var circle1 = registry.clone('blue_circle');
  circle1?.display();
  
  // Example 2: Complex object with deep copy
  print('\n--- Complex Object with Deep Copy ---');
  
  var originalEmployee = Employee('John Doe', 'Engineering', 75000);
  originalEmployee.addSkill('Dart');
  originalEmployee.addSkill('Python');
  originalEmployee.addSkill('JavaScript');
  
  print('\nOriginal employee:');
  originalEmployee.display();
  
  print('\nCloned employee:');
  var clonedEmployee = originalEmployee.clone();
  clonedEmployee.setName('Jane Smith');
  clonedEmployee.setSalary(80000);
  clonedEmployee.addSkill('Go');
  clonedEmployee.display();
  
  print('\nOriginal employee (unchanged):');
  originalEmployee.display();
  
  // Example 3: Document with deep copy
  print('\n--- Document with Deep Copy ---');
  
  var originalDoc = Document('Project Plan', 'This document outlines the project plan.');
  print('\nOriginal document:');
  originalDoc.display();
  
  print('\nCloned document:');
  var clonedDoc = originalDoc.clone();
  clonedDoc.setTitle('Project Plan - Copy');
  clonedDoc.appendContent(' It includes milestones and deliverables.');
  clonedDoc.display();
  
  print('\nOriginal document (unchanged):');
  originalDoc.display();
  
  // Example 4: Game Character with prototype
  print('\n--- Game Character with Prototype ---');
  
  var warriorTemplate = GameCharacter('Warrior', 100, 25, 15);
  warriorTemplate.addItem('Sword');
  warriorTemplate.addItem('Shield');
  
  print('\nCreating warrior from template:');
  var warrior1 = warriorTemplate.clone();
  warrior1.setName('Arthur');
  warrior1.display();
  
  print('\nCreating another warrior from template:');
  var warrior2 = warriorTemplate.clone();
  warrior2.setName('Lancelot');
  warrior2.takeDamage(20);
  warrior2.addItem('Potion');
  warrior2.display();
  
  print('\nTemplate (unchanged):');
  warriorTemplate.display();
}
