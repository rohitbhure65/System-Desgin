import { Prototype } from './interfaces';

export class Rectangle implements Prototype {
  constructor(private width: number, private height: number, private color: string) {}
  
  clone(): Rectangle { return new Rectangle(this.width, this.height, this.color); }
  display(): void { console.log(`Rectangle: ${this.width}x${this.height}, Color: ${this.color}`); }
  getType(): string { return 'Rectangle'; }
  
  setWidth(width: number): void { this.width = width; }
  setHeight(height: number): void { this.height = height; }
  setColor(color: string): void { this.color = color; }
}

export class Circle implements Prototype {
  constructor(private radius: number, private color: string) {}
  
  clone(): Circle { return new Circle(this.radius, this.color); }
  display(): void { console.log(`Circle: Radius ${this.radius}, Color: ${this.color}`); }
  getType(): string { return 'Circle'; }
  
  setRadius(radius: number): void { this.radius = radius; }
  setColor(color: string): void { this.color = color; }
}

export class Employee implements Prototype {
  constructor(private name: string, private department: string, private salary: number, private skills: string[] = []) {}
  
  clone(): Employee { return new Employee(this.name, this.department, this.salary, [...this.skills]); }
  display(): void {
    console.log(`Employee: ${this.name}, Dept: ${this.department}, Salary: $${this.salary}`);
    console.log(`Skills: ${this.skills.join(', ')}`);
  }
  getType(): string { return 'Employee'; }
  
  addSkill(skill: string): void { this.skills.push(skill); }
  setName(name: string): void { this.name = name; }
  setSalary(salary: number): void { this.salary = salary; }
}

export class Document implements Prototype {
  constructor(private title: string, private content: string) {}
  
  clone(): Document { return new Document(this.title, this.content); }
  display(): void {
    console.log(`Document: ${this.title}`);
    console.log(`Content: ${this.content}`);
  }
  getType(): string { return 'Document'; }
  
  appendContent(text: string): void { this.content += text; }
  setTitle(title: string): void { this.title = title; }
}

export class GameCharacter implements Prototype {
  constructor(private name: string, private health: number, private attack: number, private defense: number, private inventory: string[] = []) {}
  
  clone(): GameCharacter { return new GameCharacter(this.name, this.health, this.attack, this.defense, [...this.inventory]); }
  display(): void {
    console.log(`Character: ${this.name}`);
    console.log(`  Health: ${this.health}, Attack: ${this.attack}, Defense: ${this.defense}`);
    console.log(`  Inventory: ${this.inventory.join(', ')}`);
  }
  getType(): string { return 'GameCharacter'; }
  
  addItem(item: string): void { this.inventory.push(item); }
  setName(name: string): void { this.name = name; }
  takeDamage(amount: number): void { this.health = Math.max(0, this.health - amount); }
}
