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
  abstract display(indent: string): void;
  abstract getSize(): number;
  
  add(component: FileSystemComponent): void {
    console.log('Cannot add to a file');
  }
  
  remove(component: FileSystemComponent): void {
    console.log('Cannot remove from a file');
  }
  
  getChild(index: number): FileSystemComponent | null {
    return null;
  }
}

// Leaf - represents individual objects in the composition
class File extends FileSystemComponent {
  private name: string;
  private size: number;
  
  constructor(name: string, size: number) {
    super();
    this.name = name;
    this.size = size;
  }
  
  display(indent: string = ''): void {
    console.log(`${indent}File: ${this.name} (${this.size} bytes)`);
  }
  
  getSize(): number {
    return this.size;
  }
}

// Composite - represents groups of objects that can contain other composites
class Directory extends FileSystemComponent {
  private name: string;
  private children: FileSystemComponent[] = [];
  
  constructor(name: string) {
    super();
    this.name = name;
  }
  
  add(component: FileSystemComponent): void {
    this.children.push(component);
  }
  
  remove(component: FileSystemComponent): void {
    const index = this.children.indexOf(component);
    if (index > -1) {
      this.children.splice(index, 1);
    }
  }
  
  getChild(index: number): FileSystemComponent | null {
    if (index >= 0 && index < this.children.length) {
      return this.children[index];
    }
    return null;
  }
  
  display(indent: string = ''): void {
    console.log(`${indent}Directory: ${this.name} (${this.getSize()} bytes)`);
    for (const child of this.children) {
      child.display(indent + '  ');
    }
  }
  
  getSize(): number {
    let totalSize = 0;
    for (const child of this.children) {
      totalSize += child.getSize();
    }
    return totalSize;
  }
}

// Example 2: Organization Structure
// Shows how Composite can be used for organizational hierarchies

abstract class Employee {
  abstract print(indent: string): void;
  
  add(employee: Employee): void {
    console.log('Cannot add to a regular employee');
  }
  
  remove(employee: Employee): void {
    console.log('Cannot remove from a regular employee');
  }
}

class Worker extends Employee {
  private name: string;
  private position: string;
  
  constructor(name: string, position: string) {
    super();
    this.name = name;
    this.position = position;
  }
  
  print(indent: string = ''): void {
    console.log(`${indent}Employee: ${this.name} - ${this.position}`);
  }
}

class Manager extends Employee {
  private name: string;
  private title: string;
  private subordinates: Employee[] = [];
  
  constructor(name: string, title: string) {
    super();
    this.name = name;
    this.title = title;
  }
  
  add(employee: Employee): void {
    this.subordinates.push(employee);
  }
  
  remove(employee: Employee): void {
    const index = this.subordinates.indexOf(employee);
    if (index > -1) {
      this.subordinates.splice(index, 1);
    }
  }
  
  print(indent: string = ''): void {
    console.log(`${indent}Manager: ${this.name} - ${this.title}`);
    for (const subordinate of this.subordinates) {
      subordinate.print(indent + '  ');
    }
  }
}

// Example 3: Graphic Shapes Composite
// Shows how Composite can be used for graphics

abstract class Graphic {
  abstract draw(indent: string): void;
}

class Circle extends Graphic {
  private name: string;
  
  constructor(name: string) {
    super();
    this.name = name;
  }
  
  draw(indent: string = ''): void {
    console.log(`${indent}Drawing Circle: ${this.name}`);
  }
}

class Square extends Graphic {
  private name: string;
  
  constructor(name: string) {
    super();
    this.name = name;
  }
  
  draw(indent: string = ''): void {
    console.log(`${indent}Drawing Square: ${this.name}`);
  }
}

class GraphicGroup extends Graphic {
  private name: string;
  private graphics: Graphic[] = [];
  
  constructor(name: string) {
    super();
    this.name = name;
  }
  
  add(graphic: Graphic): void {
    this.graphics.push(graphic);
  }
  
  remove(graphic: Graphic): void {
    const index = this.graphics.indexOf(graphic);
    if (index > -1) {
      this.graphics.splice(index, 1);
    }
  }
  
  draw(indent: string = ''): void {
    console.log(`${indent}Group: ${this.name}`);
    for (const graphic of this.graphics) {
      graphic.draw(indent + '  ');
    }
  }
}

// Demo code
function demoComposite(): void {
  console.log('=== Composite Pattern Demo ===\n');
  
  // Example 1: File System
  console.log('--- File System Example ---');
  
  const file1 = new File('file1.txt', 100);
  const file2 = new File('file2.txt', 200);
  const file3 = new File('file3.txt', 150);
  
  const dir1 = new Directory('Documents');
  const dir2 = new Directory('Pictures');
  const rootDir = new Directory('Root');
  
  dir1.add(file1);
  dir1.add(file2);
  
  dir2.add(file3);
  
  rootDir.add(dir1);
  rootDir.add(dir2);
  
  console.log('\nFile System Structure:');
  rootDir.display();
  
  console.log(`\nTotal size of Root directory: ${rootDir.getSize()} bytes`);
  
  console.log();
  
  // Example 2: Organization Structure
  console.log('--- Organization Structure Example ---');
  
  const ceo = new Manager('John Smith', 'CEO');
  const cto = new Manager('Alice Johnson', 'CTO');
  const cfo = new Manager('Bob Williams', 'CFO');
  
  const dev1 = new Worker('Developer 1', 'Senior Developer');
  const dev2 = new Worker('Developer 2', 'Junior Developer');
  const accountant = new Worker('Accountant', 'Senior Accountant');
  
  cto.add(dev1);
  cto.add(dev2);
  cfo.add(accountant);
  
  ceo.add(cto);
  ceo.add(cfo);
  
  console.log('\nOrganization Structure:');
  ceo.print();
  
  console.log();
  
  // Example 3: Graphic Shapes
  console.log('--- Graphic Shapes Example ---');
  
  const circle1 = new Circle('Red Circle');
  const circle2 = new Circle('Blue Circle');
  const square1 = new Square('Green Square');
  
  const group1 = new GraphicGroup('Shapes Group 1');
  const group2 = new GraphicGroup('Shapes Group 2');
  const mainGroup = new GraphicGroup('Main Group');
  
  group1.add(circle1);
  group1.add(square1);
  
  group2.add(circle2);
  
  mainGroup.add(group1);
  mainGroup.add(group2);
  
  console.log('\nGraphic Structure:');
  mainGroup.draw();
}

// Run the demo
demoComposite();
