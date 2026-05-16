/*
 * DECORATOR DESIGN PATTERN
 * 
 * WHAT IS IT?
 * The Decorator pattern lets you attach new behaviors to objects by placing these objects inside special wrapper objects that contain the behaviors.
 * It provides a flexible alternative to inheritance for extending functionality.
 * 
 * WHY DOES IT EXIST?
 * - When you want to add responsibilities to individual objects dynamically without affecting other objects
 * - When extending a class by subclassing is impractical (too many subclasses)
 * - When you want to add and remove responsibilities at runtime
 * 
 * WHEN TO USE IT?
 * - When you need to add responsibilities to individual objects without affecting other objects of the same class
 * - When the class definition may be hidden or otherwise unavailable for subclassing
 * - When you want to add functionality to objects in a transparent way (clients shouldn't know the difference)
 * - Common use cases: UI components (scrollbars, borders), data streams (compression, encryption), logging, caching
 * 
 * PROS:
 * - Single Responsibility Principle (divides functionality into small classes)
 * - Open/Closed Principle (can extend behavior without modifying existing code)
 * - Flexible alternative to subclassing
 * - Can add/remove responsibilities at runtime
 * 
 * CONS:
 * - Can result in many small classes (code complexity)
 * - Can make it hard to remove wrapped decorators
 * - Can make debugging difficult due to many layers
 * - Initial setup can be complex
 * 
 * REAL-WORLD ANALOGY:
 * Think of ordering coffee. You start with a basic coffee (component), then you can add decorators like milk, sugar, whipped cream, or syrup. Each decorator adds its own behavior (flavor, cost) while still being treated as coffee. You can combine multiple decorators in any order.
 */

// Component Interface - defines the interface for objects that can have responsibilities added
interface Coffee {
  getCost(): number;
  getDescription(): string;
}

// Concrete Component - the basic object that can have responsibilities added
class SimpleCoffee implements Coffee {
  getCost(): number {
    return 2.0;
  }
  
  getDescription(): string {
    return 'Simple Coffee';
  }
}

// Decorator - implements the Component interface and wraps a Component
abstract class CoffeeDecorator implements Coffee {
  protected decoratedCoffee: Coffee;
  
  constructor(coffee: Coffee) {
    this.decoratedCoffee = coffee;
  }
  
  getCost(): number {
    return this.decoratedCoffee.getCost();
  }
  
  getDescription(): string {
    return this.decoratedCoffee.getDescription();
  }
}

// Concrete Decorator 1: Milk
class MilkDecorator extends CoffeeDecorator {
  getCost(): number {
    return super.getCost() + 0.5;
  }
  
  getDescription(): string {
    return super.getDescription() + ', Milk';
  }
}

// Concrete Decorator 2: Sugar
class SugarDecorator extends CoffeeDecorator {
  getCost(): number {
    return super.getCost() + 0.2;
  }
  
  getDescription(): string {
    return super.getDescription() + ', Sugar';
  }
}

// Concrete Decorator 3: Whipped Cream
class WhippedCreamDecorator extends CoffeeDecorator {
  getCost(): number {
    return super.getCost() + 1.0;
  }
  
  getDescription(): string {
    return super.getDescription() + ', Whipped Cream';
  }
}

// Example 2: Text Formatting Decorator
// Shows how decorators can be used for text processing

interface TextComponent {
  getText(): string;
}

class SimpleText implements TextComponent {
  constructor(private text: string) {}
  
  getText(): string {
    return this.text;
  }
}

abstract class TextDecorator implements TextComponent {
  protected wrappedText: TextComponent;
  
  constructor(text: TextComponent) {
    this.wrappedText = text;
  }
  
  getText(): string {
    return this.wrappedText.getText();
  }
}

class BoldDecorator extends TextDecorator {
  getText(): string {
    return `<b>${super.getText()}</b>`;
  }
}

class ItalicDecorator extends TextDecorator {
  getText(): string {
    return `<i>${super.getText()}</i>`;
  }
}

class UnderlineDecorator extends TextDecorator {
  getText(): string {
    return `<u>${super.getText()}</u>`;
  }
}

// Example 3: Data Stream Decorator
// Shows how decorators can be used for data processing

interface DataSource {
  writeData(data: string): void;
  readData(): string;
}

class FileDataSource implements DataSource {
  private data: string = '';
  
  writeData(data: string): void {
    this.data = data;
    console.log(`Writing data to file: ${data}`);
  }
  
  readData(): string {
    console.log(`Reading data from file: ${this.data}`);
    return this.data;
  }
}

abstract class DataSourceDecorator implements DataSource {
  protected wrappedSource: DataSource;
  
  constructor(source: DataSource) {
    this.wrappedSource = source;
  }
  
  writeData(data: string): void {
    this.wrappedSource.writeData(data);
  }
  
  readData(): string {
    return this.wrappedSource.readData();
  }
}

class EncryptionDecorator extends DataSourceDecorator {
  writeData(data: string): void {
    const encrypted = `[ENCRYPTED]${data}[ENCRYPTED]`;
    console.log('Encrypting data...');
    this.wrappedSource.writeData(encrypted);
  }
  
  readData(): string {
    const data = this.wrappedSource.readData();
    console.log('Decrypting data...');
    // Remove encryption markers for demo
    if (data.startsWith('[ENCRYPTED]')) {
      return data.substring(11, data.length - 11);
    }
    return data;
  }
}

class CompressionDecorator extends DataSourceDecorator {
  writeData(data: string): void {
    const compressed = `[COMPRESSED]${data}[COMPRESSED]`;
    console.log('Compressing data...');
    this.wrappedSource.writeData(compressed);
  }
  
  readData(): string {
    const data = this.wrappedSource.readData();
    console.log('Decompressing data...');
    // Remove compression markers for demo
    if (data.startsWith('[COMPRESSED]')) {
      return data.substring(12, data.length - 12);
    }
    return data;
  }
}

// Demo code
function demoDecorator(): void {
  console.log('=== Decorator Pattern Demo ===\n');
  
  // Example 1: Coffee Shop
  console.log('--- Coffee Shop Example ---');
  
  let coffee: Coffee = new SimpleCoffee();
  console.log(`${coffee.getDescription()} $${coffee.getCost()}`);
  
  coffee = new MilkDecorator(coffee);
  console.log(`${coffee.getDescription()} $${coffee.getCost()}`);
  
  coffee = new SugarDecorator(coffee);
  console.log(`${coffee.getDescription()} $${coffee.getCost()}`);
  
  coffee = new WhippedCreamDecorator(coffee);
  console.log(`${coffee.getDescription()} $${coffee.getCost()}`);
  
  console.log();
  
  // Example 2: Text Formatting
  console.log('--- Text Formatting Example ---');
  
  let text: TextComponent = new SimpleText('Hello World');
  console.log(`Original: ${text.getText()}`);
  
  text = new BoldDecorator(text);
  console.log(`Bold: ${text.getText()}`);
  
  text = new ItalicDecorator(text);
  console.log(`Bold + Italic: ${text.getText()}`);
  
  text = new UnderlineDecorator(text);
  console.log(`Bold + Italic + Underline: ${text.getText()}`);
  
  console.log();
  
  // Example 3: Data Stream Processing
  console.log('--- Data Stream Processing Example ---');
  
  let dataSource: DataSource = new FileDataSource();
  console.log('\nWriting plain data:');
  dataSource.writeData('Important Data');
  console.log(`Reading: ${dataSource.readData()}`);
  
  console.log('\nWriting encrypted data:');
  dataSource = new EncryptionDecorator(dataSource);
  dataSource.writeData('Secret Data');
  console.log(`Reading: ${dataSource.readData()}`);
  
  console.log('\nWriting encrypted and compressed data:');
  dataSource = new CompressionDecorator(dataSource);
  dataSource.writeData('Very Secret Data');
  console.log(`Reading: ${dataSource.readData()}`);
}

// Run the demo
demoDecorator();
