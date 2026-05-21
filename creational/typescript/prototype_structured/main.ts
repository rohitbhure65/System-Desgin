import { Rectangle, Circle, Employee, Document, GameCharacter } from './concrete_prototypes';
import { PrototypeRegistry } from './registry';

function demoPrototype(): void {
  console.log('=== Prototype Pattern Demo ===\n');
  
  console.log('--- Basic Prototype with Registry ---');
  const registry = new PrototypeRegistry();
  
  registry.registerPrototype('red_rectangle', new Rectangle(10, 5, 'red'));
  registry.registerPrototype('blue_circle', new Circle(7, 'blue'));
  
  console.log('\nCloning red rectangle:');
  const rect1 = registry.clone('red_rectangle');
  rect1?.display();
  
  console.log('\nCloning and modifying red rectangle:');
  const rect2 = registry.clone('red_rectangle');
  if (rect2 instanceof Rectangle) {
    rect2.setWidth(20);
    rect2.setColor('green');
    rect2.display();
  }
  
  console.log('\nCloning blue circle:');
  const circle1 = registry.clone('blue_circle');
  circle1?.display();
  
  console.log('\n--- Complex Object with Deep Copy ---');
  
  const originalEmployee = new Employee('John Doe', 'Engineering', 75000);
  originalEmployee.addSkill('TypeScript');
  originalEmployee.addSkill('Python');
  originalEmployee.addSkill('JavaScript');
  
  console.log('\nOriginal employee:');
  originalEmployee.display();
  
  console.log('\nCloned employee:');
  const clonedEmployee = originalEmployee.clone();
  clonedEmployee.setName('Jane Smith');
  clonedEmployee.setSalary(80000);
  clonedEmployee.addSkill('Go');
  clonedEmployee.display();
  
  console.log('\nOriginal employee (unchanged):');
  originalEmployee.display();
  
  console.log('\n--- Document with Deep Copy ---');
  
  const originalDoc = new Document('Project Plan', 'This document outlines the project plan.');
  console.log('\nOriginal document:');
  originalDoc.display();
  
  console.log('\nCloned document:');
  const clonedDoc = originalDoc.clone();
  clonedDoc.setTitle('Project Plan - Copy');
  clonedDoc.appendContent(' It includes milestones and deliverables.');
  clonedDoc.display();
  
  console.log('\nOriginal document (unchanged):');
  originalDoc.display();
  
  console.log('\n--- Game Character with Prototype ---');
  
  const warriorTemplate = new GameCharacter('Warrior', 100, 25, 15);
  warriorTemplate.addItem('Sword');
  warriorTemplate.addItem('Shield');
  
  console.log('\nCreating warrior from template:');
  const warrior1 = warriorTemplate.clone();
  warrior1.setName('Arthur');
  warrior1.display();
  
  console.log('\nCreating another warrior from template:');
  const warrior2 = warriorTemplate.clone();
  warrior2.setName('Lancelot');
  warrior2.takeDamage(20);
  warrior2.addItem('Potion');
  warrior2.display();
  
  console.log('\nTemplate (unchanged):');
  warriorTemplate.display();
}

demoPrototype();
