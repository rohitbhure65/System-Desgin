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
interface Prototype {
  clone(): Prototype;
  display(): void;
  getType(): string;
}

// Concrete Prototype 1: Rectangle
class Rectangle implements Prototype {
  constructor(
    private width: number,
    private height: number,
    private color: string
  ) {}
  
  // Clone method using Object.assign for shallow copy
  clone(): Prototype {
    return new Rectangle(this.width, this.height, this.color);
  }
  
  display(): void {
    console.log(`Rectangle: ${this.width}x${this.height}, Color: ${this.color}`);
  }
  
  getType(): string {
    return 'Rectangle';
  }
  
  // Methods to modify the cloned object
  public setWidth(width: number): void {
    this.width = width;
  }
  
  public setHeight(height: number): void {
    this.height = height;
  }
  
  public setColor(color: string): void {
    this.color = color;
  }
}

// Concrete Prototype 2: Circle
class Circle implements Prototype {
  constructor(
    private radius: number,
    private color: string
  ) {}
  
  clone(): Prototype {
    return new Circle(this.radius, this.color);
  }
  
  display(): void {
    console.log(`Circle: Radius ${this.radius}, Color: ${this.color}`);
  }
  
  getType(): string {
    return 'Circle';
  }
  
  public setRadius(radius: number): void {
    this.radius = radius;
  }
  
  public setColor(color: string): void {
    this.color = color;
  }
}

// Prototype Registry - manages a collection of prototypes
class PrototypeRegistry {
  private prototypes: Map<string, Prototype> = new Map();
  
  public registerPrototype(key: string, prototype: Prototype): void {
    this.prototypes.set(key, prototype);
  }
  
  public clone(key: string): Prototype | null {
    const prototype = this.prototypes.get(key);
    return prototype ? prototype.clone() : null;
  }
}

// Example: Complex object with deep copy
class Employee implements Prototype {
  constructor(
    private name: string,
    private department: string,
    private salary: number,
    private skills: string[] = []
  ) {}
  
  // Deep copy constructor
  clone(): Prototype {
    // Create a deep copy of the skills array
    const skillsCopy = [...this.skills];
    return new Employee(this.name, this.department, this.salary, skillsCopy);
  }
  
  display(): void {
    console.log(`Employee: ${this.name}, Dept: ${this.department}, Salary: $${this.salary}`);
    console.log(`Skills: ${this.skills.join(', ')}`);
  }
  
  getType(): string {
    return 'Employee';
  }
  
  public addSkill(skill: string): void {
    this.skills.push(skill);
  }
  
  public setName(name: string): void {
    this.name = name;
  }
  
  public setSalary(salary: number): void {
    this.salary = salary;
  }
}

// Example: Document with shallow vs deep copy
class Document implements Prototype {
  constructor(
    private title: string,
    private content: string
  ) {}
  
  clone(): Prototype {
    // For strings, this is effectively a deep copy since strings are immutable in TypeScript
    return new Document(this.title, this.content);
  }
  
  display(): void {
    console.log(`Document: ${this.title}`);
    console.log(`Content: ${this.content}`);
  }
  
  getType(): string {
    return 'Document';
  }
  
  public appendContent(text: string): void {
    this.content += text;
  }
  
  public setTitle(title: string): void {
    this.title = title;
  }
}

// Example: Game Character with prototype
class GameCharacter implements Prototype {
  constructor(
    private name: string,
    private health: number,
    private attack: number,
    private defense: number,
    private inventory: string[] = []
  ) {}
  
  clone(): Prototype {
    return new GameCharacter(
      this.name,
      this.health,
      this.attack,
      this.defense,
      [...this.inventory]
    );
  }
  
  display(): void {
    console.log(`Character: ${this.name}`);
    console.log(`  Health: ${this.health}, Attack: ${this.attack}, Defense: ${this.defense}`);
    console.log(`  Inventory: ${this.inventory.join(', ')}`);
  }
  
  getType(): string {
    return 'GameCharacter';
  }
  
  public addItem(item: string): void {
    this.inventory.push(item);
  }
  
  public setName(name: string): void {
    this.name = name;
  }
  
  public takeDamage(amount: number): void {
    this.health = Math.max(0, this.health - amount);
  }
}

// Demo code
function demoPrototype(): void {
  console.log('=== Prototype Pattern Demo ===\n');
  
  // Example 1: Basic Prototype with Registry
  console.log('--- Basic Prototype with Registry ---');
  
  const registry = new PrototypeRegistry();
  
  // Register prototypes
  registry.registerPrototype('red_rectangle', new Rectangle(10, 5, 'red'));
  registry.registerPrototype('blue_circle', new Circle(7, 'blue'));
  
  // Clone and modify prototypes
  console.log('\nCloning red rectangle:');
  const rect1 = registry.clone('red_rectangle');
  if (rect1) rect1.display();
  
  console.log('\nCloning and modifying red rectangle:');
  const rect2 = registry.clone('red_rectangle');
  if (rect2) {
    const rect2Typed = rect2 as Rectangle;
    rect2Typed.setWidth(20);
    rect2Typed.setColor('green');
    rect2Typed.display();
  }
  
  console.log('\nCloning blue circle:');
  const circle1 = registry.clone('blue_circle');
  if (circle1) circle1.display();
  
  // Example 2: Complex object with deep copy
  console.log('\n--- Complex Object with Deep Copy ---');
  
  const originalEmployee = new Employee('John Doe', 'Engineering', 75000);
  originalEmployee.addSkill('TypeScript');
  originalEmployee.addSkill('Python');
  originalEmployee.addSkill('JavaScript');
  
  console.log('\nOriginal employee:');
  originalEmployee.display();
  
  console.log('\nCloned employee:');
  const clonedEmployee = originalEmployee.clone() as Employee;
  clonedEmployee.setName('Jane Smith');
  clonedEmployee.setSalary(80000);
  clonedEmployee.addSkill('Go');
  clonedEmployee.display();
  
  console.log('\nOriginal employee (unchanged):');
  originalEmployee.display();
  
  // Example 3: Document with deep copy
  console.log('\n--- Document with Deep Copy ---');
  
  const originalDoc = new Document('Project Plan', 'This document outlines the project plan.');
  console.log('\nOriginal document:');
  originalDoc.display();
  
  console.log('\nCloned document:');
  const clonedDoc = originalDoc.clone() as Document;
  clonedDoc.setTitle('Project Plan - Copy');
  clonedDoc.appendContent(' It includes milestones and deliverables.');
  clonedDoc.display();
  
  console.log('\nOriginal document (unchanged):');
  originalDoc.display();
  
  // Example 4: Game Character with prototype
  console.log('\n--- Game Character with Prototype ---');
  
  const warriorTemplate = new GameCharacter('Warrior', 100, 25, 15);
  warriorTemplate.addItem('Sword');
  warriorTemplate.addItem('Shield');
  
  console.log('\nCreating warrior from template:');
  const warrior1 = warriorTemplate.clone() as GameCharacter;
  warrior1.setName('Arthur');
  warrior1.display();
  
  console.log('\nCreating another warrior from template:');
  const warrior2 = warriorTemplate.clone() as GameCharacter;
  warrior2.setName('Lancelot');
  warrior2.takeDamage(20);
  warrior2.addItem('Potion');
  warrior2.display();
  
  console.log('\nTemplate (unchanged):');
  warriorTemplate.display();
}

// Run the demo
demoPrototype();
