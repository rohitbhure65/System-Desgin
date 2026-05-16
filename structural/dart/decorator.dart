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
abstract class Coffee {
  double getCost();
  String getDescription();
}

// Concrete Component - the basic object that can have responsibilities added
class SimpleCoffee extends Coffee {
  @override
  double getCost() {
    return 2.0;
  }
  
  @override
  String getDescription() {
    return 'Simple Coffee';
  }
}

// Decorator - implements the Component interface and wraps a Component
abstract class CoffeeDecorator extends Coffee {
  final Coffee decoratedCoffee;
  
  CoffeeDecorator(this.decoratedCoffee);
  
  @override
  double getCost() {
    return decoratedCoffee.getCost();
  }
  
  @override
  String getDescription() {
    return decoratedCoffee.getDescription();
  }
}

// Concrete Decorator 1: Milk
class MilkDecorator extends CoffeeDecorator {
  MilkDecorator(super.coffee);
  
  @override
  double getCost() {
    return super.getCost() + 0.5;
  }
  
  @override
  String getDescription() {
    return '${super.getDescription()}, Milk';
  }
}

// Concrete Decorator 2: Sugar
class SugarDecorator extends CoffeeDecorator {
  SugarDecorator(super.coffee);
  
  @override
  double getCost() {
    return super.getCost() + 0.2;
  }
  
  @override
  String getDescription() {
    return '${super.getDescription()}, Sugar';
  }
}

// Concrete Decorator 3: Whipped Cream
class WhippedCreamDecorator extends CoffeeDecorator {
  WhippedCreamDecorator(super.coffee);
  
  @override
  double getCost() {
    return super.getCost() + 1.0;
  }
  
  @override
  String getDescription() {
    return '${super.getDescription()}, Whipped Cream';
  }
}

// Example 2: Text Formatting Decorator
// Shows how decorators can be used for text processing

abstract class TextComponent {
  String getText();
}

class SimpleText extends TextComponent {
  final String text;
  
  SimpleText(this.text);
  
  @override
  String getText() {
    return text;
  }
}

abstract class TextDecorator extends TextComponent {
  final TextComponent wrappedText;
  
  TextDecorator(this.wrappedText);
  
  @override
  String getText() {
    return wrappedText.getText();
  }
}

class BoldDecorator extends TextDecorator {
  BoldDecorator(super.text);
  
  @override
  String getText() {
    return '<b>${super.getText()}</b>';
  }
}

class ItalicDecorator extends TextDecorator {
  ItalicDecorator(super.text);
  
  @override
  String getText() {
    return '<i>${super.getText()}</i>';
  }
}

class UnderlineDecorator extends TextDecorator {
  UnderlineDecorator(super.text);
  
  @override
  String getText() {
    return '<u>${super.getText()}</u>';
  }
}

// Example 3: Data Stream Decorator
// Shows how decorators can be used for data processing

abstract class DataSource {
  void writeData(String data);
  String readData();
}

class FileDataSource extends DataSource {
  String _data = '';
  
  @override
  void writeData(String data) {
    _data = data;
    print('Writing data to file: $data');
  }
  
  @override
  String readData() {
    print('Reading data from file: $_data');
    return _data;
  }
}

abstract class DataSourceDecorator extends DataSource {
  final DataSource wrappedSource;
  
  DataSourceDecorator(this.wrappedSource);
  
  @override
  void writeData(String data) {
    wrappedSource.writeData(data);
  }
  
  @override
  String readData() {
    return wrappedSource.readData();
  }
}

class EncryptionDecorator extends DataSourceDecorator {
  EncryptionDecorator(super.source);
  
  @override
  void writeData(String data) {
    var encrypted = '[ENCRYPTED]$data[ENCRYPTED]';
    print('Encrypting data...');
    wrappedSource.writeData(encrypted);
  }
  
  @override
  String readData() {
    var data = wrappedSource.readData();
    print('Decrypting data...');
    // Remove encryption markers for demo
    if (data.startsWith('[ENCRYPTED]')) {
      return data.substring(11, data.length - 11);
    }
    return data;
  }
}

class CompressionDecorator extends DataSourceDecorator {
  CompressionDecorator(super.source);
  
  @override
  void writeData(String data) {
    var compressed = '[COMPRESSED]$data[COMPRESSED]';
    print('Compressing data...');
    wrappedSource.writeData(compressed);
  }
  
  @override
  String readData() {
    var data = wrappedSource.readData();
    print('Decompressing data...');
    // Remove compression markers for demo
    if (data.startsWith('[COMPRESSED]')) {
      return data.substring(12, data.length - 12);
    }
    return data;
  }
}

// Demo code
void main() {
  print('=== Decorator Pattern Demo ===\n');
  
  // Example 1: Coffee Shop
  print('--- Coffee Shop Example ---');
  
  Coffee coffee = SimpleCoffee();
  print('${coffee.getDescription()} \$${coffee.getCost()}');
  
  coffee = MilkDecorator(coffee);
  print('${coffee.getDescription()} \$${coffee.getCost()}');
  
  coffee = SugarDecorator(coffee);
  print('${coffee.getDescription()} \$${coffee.getCost()}');
  
  coffee = WhippedCreamDecorator(coffee);
  print('${coffee.getDescription()} \$${coffee.getCost()}');
  
  print('');
  
  // Example 2: Text Formatting
  print('--- Text Formatting Example ---');
  
  TextComponent text = SimpleText('Hello World');
  print('Original: ${text.getText()}');
  
  text = BoldDecorator(text);
  print('Bold: ${text.getText()}');
  
  text = ItalicDecorator(text);
  print('Bold + Italic: ${text.getText()}');
  
  text = UnderlineDecorator(text);
  print('Bold + Italic + Underline: ${text.getText()}');
  
  print('');
  
  // Example 3: Data Stream Processing
  print('--- Data Stream Processing Example ---');
  
  DataSource dataSource = FileDataSource();
  print('\nWriting plain data:');
  dataSource.writeData('Important Data');
  print('Reading: ${dataSource.readData()}');
  
  print('\nWriting encrypted data:');
  dataSource = EncryptionDecorator(dataSource);
  dataSource.writeData('Secret Data');
  print('Reading: ${dataSource.readData()}');
  
  print('\nWriting encrypted and compressed data:');
  dataSource = CompressionDecorator(dataSource);
  dataSource.writeData('Very Secret Data');
  print('Reading: ${dataSource.readData()}');
}
