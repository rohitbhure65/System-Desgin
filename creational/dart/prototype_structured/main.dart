import 'concrete_prototypes.dart';
import 'registry.dart';

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
