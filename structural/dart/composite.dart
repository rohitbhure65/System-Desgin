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

// Component Interface - declares the interface for objects in the composition
abstract class FileSystemComponent {
  void display([String indent = '']);
  int getSize();
  
  void add(FileSystemComponent component) {
    print('Cannot add to a file');
  }
  
  void remove(FileSystemComponent component) {
    print('Cannot remove from a file');
  }
  
  FileSystemComponent? getChild(int index) {
    return null;
  }
}

// Leaf - represents individual objects in the composition
class FileComponent extends FileSystemComponent {
  final String name;
  final int size;
  
  FileComponent(this.name, this.size);
  
  @override
  void display([String indent = '']) {
    print('$indent File: $name ($size bytes)');
  }
  
  @override
  int getSize() {
    return size;
  }
}

// Composite - represents groups of objects that can contain other composites
class Directory extends FileSystemComponent {
  final String name;
  final List<FileSystemComponent> _children = [];
  
  Directory(this.name);
  
  @override
  void add(FileSystemComponent component) {
    _children.add(component);
  }
  
  @override
  void remove(FileSystemComponent component) {
    _children.remove(component);
  }
  
  @override
  FileSystemComponent? getChild(int index) {
    if (index >= 0 && index < _children.length) {
      return _children[index];
    }
    return null;
  }
  
  @override
  void display([String indent = '']) {
    print('$indent Directory: $name (${getSize()} bytes)');
    for (var child in _children) {
      child.display(indent + '  ');
    }
  }
  
  @override
  int getSize() {
    int totalSize = 0;
    for (var child in _children) {
      totalSize += child.getSize();
    }
    return totalSize;
  }
}

// Example 2: Organization Structure
// Shows how Composite can be used for organizational hierarchies

abstract class Employee {
  void print([String indent = '']);
  
  void add(Employee employee) {
    print('Cannot add to a regular employee');
  }
  
  void remove(Employee employee) {
    print('Cannot remove from a regular employee');
  }
}

class Worker extends Employee {
  final String name;
  final String position;
  
  Worker(this.name, this.position);
  
  @override
  void print([String indent = '']) {
    print('$indent Employee: $name - $position');
  }
}

class Manager extends Employee {
  final String name;
  final String title;
  final List<Employee> _subordinates = [];
  
  Manager(this.name, this.title);
  
  @override
  void add(Employee employee) {
    _subordinates.add(employee);
  }
  
  @override
  void remove(Employee employee) {
    _subordinates.remove(employee);
  }
  
  @override
  void print([String indent = '']) {
    print('$indent Manager: $name - $title');
    for (var subordinate in _subordinates) {
      subordinate.print(indent + '  ');
    }
  }
}

// Example 3: Graphic Shapes Composite
// Shows how Composite can be used for graphics

abstract class Graphic {
  void draw([String indent = '']);
}

class CircleGraphic extends Graphic {
  final String name;
  
  CircleGraphic(this.name);
  
  @override
  void draw([String indent = '']) {
    print('$indent Drawing Circle: $name');
  }
}

class SquareGraphic extends Graphic {
  final String name;
  
  SquareGraphic(this.name);
  
  @override
  void draw([String indent = '']) {
    print('$indent Drawing Square: $name');
  }
}

class GraphicGroup extends Graphic {
  final String name;
  final List<Graphic> _graphics = [];
  
  GraphicGroup(this.name);
  
  void add(Graphic graphic) {
    _graphics.add(graphic);
  }
  
  void remove(Graphic graphic) {
    _graphics.remove(graphic);
  }
  
  @override
  void draw([String indent = '']) {
    print('$indent Group: $name');
    for (var graphic in _graphics) {
      graphic.draw(indent + '  ');
    }
  }
}

// Demo code
void main() {
  print('=== Composite Pattern Demo ===\n');
  
  // Example 1: File System
  print('--- File System Example ---');
  
  var file1 = FileComponent('file1.txt', 100);
  var file2 = FileComponent('file2.txt', 200);
  var file3 = FileComponent('file3.txt', 150);
  
  var dir1 = Directory('Documents');
  var dir2 = Directory('Pictures');
  var rootDir = Directory('Root');
  
  dir1.add(file1);
  dir1.add(file2);
  
  dir2.add(file3);
  
  rootDir.add(dir1);
  rootDir.add(dir2);
  
  print('\nFile System Structure:');
  rootDir.display();
  
  print('\nTotal size of Root directory: ${rootDir.getSize()} bytes');
  
  print('');
  
  // Example 2: Organization Structure
  print('--- Organization Structure Example ---');
  
  var ceo = Manager('John Smith', 'CEO');
  var cto = Manager('Alice Johnson', 'CTO');
  var cfo = Manager('Bob Williams', 'CFO');
  
  var dev1 = Worker('Developer 1', 'Senior Developer');
  var dev2 = Worker('Developer 2', 'Junior Developer');
  var accountant = Worker('Accountant', 'Senior Accountant');
  
  cto.add(dev1);
  cto.add(dev2);
  cfo.add(accountant);
  
  ceo.add(cto);
  ceo.add(cfo);
  
  print('\nOrganization Structure:');
  ceo.print();
  
  print('');
  
  // Example 3: Graphic Shapes
  print('--- Graphic Shapes Example ---');
  
  var circle1 = CircleGraphic('Red Circle');
  var circle2 = CircleGraphic('Blue Circle');
  var square1 = SquareGraphic('Green Square');
  
  var group1 = GraphicGroup('Shapes Group 1');
  var group2 = GraphicGroup('Shapes Group 2');
  var mainGroup = GraphicGroup('Main Group');
  
  group1.add(circle1);
  group1.add(square1);
  
  group2.add(circle2);
  
  mainGroup.add(group1);
  mainGroup.add(group2);
  
  print('\nGraphic Structure:');
  mainGroup.draw();
}
