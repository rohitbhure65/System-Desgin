/*
 * FACTORY METHOD DESIGN PATTERN
 * 
 * WHAT IS IT?
 * The Factory Method pattern defines an interface for creating an object but lets subclasses decide which class to instantiate.
 * It delegates the instantiation logic to child classes.
 * 
 * WHY DOES IT EXIST?
 * - Decouples the creation of objects from their usage
 * - Allows a class to defer instantiation to subclasses
 * - Provides a way to extend the creation logic without modifying existing code (Open/Closed Principle)
 * - Eliminates the need to bind application-specific classes into your code
 * 
 * WHEN TO USE IT?
 * - When a class can't anticipate the class of objects it must create
 * - When a class wants its subclasses to specify the objects it creates
 * - When classes delegate responsibility to one of several helper subclasses, and you want to localize the knowledge of which helper subclass is the delegate
 * - Common use cases: document creation, UI components, payment processing, logging frameworks
 * 
 * PROS:
 * - Avoids tight coupling between the creator and the concrete products
 * - Follows Open/Closed Principle (easy to introduce new products without changing existing code)
 * - Single Responsibility Principle (product creation code is in one place)
 * - Can be combined with other patterns (e.g., Singleton, Prototype)
 * 
 * CONS:
 * - Can make the code more complex by introducing many subclasses
 * - May require creating a parallel inheritance hierarchy for creators and products
 * - Can lead to excessive use of inheritance
 * 
 * REAL-WORLD ANALOGY:
 * Think of a car manufacturing plant. The plant (factory) knows how to build cars, but it doesn't know what specific type of car to build until an order comes in. The plant has a method to build cars, but the specific car model (sedan, SUV, truck) is determined by the order or by specialized assembly lines (subclasses).
 */

// Product interface - defines the common interface for all products
abstract class Document {
  void open();
  void close();
  void save();
  String get type;
}

// Concrete Product 1: Text Document
class TextDocument extends Document {
  @override
  void open() {
    print('Opening Text Document in text editor...');
  }
  
  @override
  void close() {
    print('Closing Text Document...');
  }
  
  @override
  void save() {
    print('Saving Text Document as .txt file...');
  }
  
  @override
  String get type => 'Text Document';
}

// Concrete Product 2: PDF Document
class PDFDocument extends Document {
  @override
  void open() {
    print('Opening PDF Document in PDF viewer...');
  }
  
  @override
  void close() {
    print('Closing PDF Document...');
  }
  
  @override
  void save() {
    print('Saving PDF Document as .pdf file...');
  }
  
  @override
  String get type => 'PDF Document';
}

// Concrete Product 3: HTML Document
class HtmlDocument extends Document {
  @override
  void open() {
    print('Opening HTML Document in web browser...');
  }
  
  @override
  void close() {
    print('Closing HTML Document...');
  }
  
  @override
  void save() {
    print('Saving HTML Document as .html file...');
  }
  
  @override
  String get type => 'HTML Document';
}

// Creator abstract class - declares the factory method
abstract class DocumentApplication {
  // Factory method - to be implemented by subclasses
  // This is the core of the pattern: subclasses decide what to create
  Document createDocument();
  
  // Business logic that uses the product
  // This method doesn't need to know which specific document is created
  void newDocument() {
    var doc = createDocument();
    print('Created: ${doc.type}');
    doc.open();
    doc.save();
    doc.close();
  }
}

// Concrete Creator 1: Text Editor Application
class TextEditor extends DocumentApplication {
  @override
  Document createDocument() {
    return TextDocument();
  }
}

// Concrete Creator 2: PDF Viewer Application
class PDFViewer extends DocumentApplication {
  @override
  Document createDocument() {
    return PDFDocument();
  }
}

// Concrete Creator 3: Web Browser Application
class WebBrowser extends DocumentApplication {
  @override
  Document createDocument() {
    return HtmlDocument();
  }
}

// Alternative implementation: Parameterized Factory Method
// This allows a single creator to create multiple types of products
enum DocType { text, pdf, html }

class DocumentFactory {
  static Document createDocument(DocType type) {
    switch (type) {
      case DocType.text:
        return TextDocument();
      case DocType.pdf:
        return PDFDocument();
      case DocType.html:
        return HtmlDocument();
    }
  }
}

// Example: Payment Processing Factory
abstract class PaymentProcessor {
  void processPayment(int amount);
  void refundPayment(int amount);
}

class CreditCardProcessor extends PaymentProcessor {
  @override
  void processPayment(int amount) {
    print('Processing credit card payment of \$$amount');
  }
  
  @override
  void refundPayment(int amount) {
    print('Refunding credit card payment of \$$amount');
  }
}

class PayPalProcessor extends PaymentProcessor {
  @override
  void processPayment(int amount) {
    print('Processing PayPal payment of \$$amount');
  }
  
  @override
  void refundPayment(int amount) {
    print('Refunding PayPal payment of \$$amount');
  }
}

class CryptoProcessor extends PaymentProcessor {
  @override
  void processPayment(int amount) {
    print('Processing cryptocurrency payment of \$$amount');
  }
  
  @override
  void refundPayment(int amount) {
    print('Refunding cryptocurrency payment of \$$amount');
  }
}

enum PaymentMethod { creditCard, payPal, crypto }

class PaymentFactory {
  static PaymentProcessor createProcessor(PaymentMethod method) {
    switch (method) {
      case PaymentMethod.creditCard:
        return CreditCardProcessor();
      case PaymentMethod.payPal:
        return PayPalProcessor();
      case PaymentMethod.crypto:
        return CryptoProcessor();
    }
  }
}

// Demo code
void main() {
  print('=== Factory Method Pattern Demo ===\n');
  
  // Using inheritance-based Factory Method
  print('--- Inheritance-based Factory Method ---');
  
  var textEditor = TextEditor();
  textEditor.newDocument();
  print('');
  
  var pdfViewer = PDFViewer();
  pdfViewer.newDocument();
  print('');
  
  var webBrowser = WebBrowser();
  webBrowser.newDocument();
  print('');
  
  // Using parameterized Factory Method
  print('--- Parameterized Factory Method ---');
  
  var textDoc = DocumentFactory.createDocument(DocType.text);
  textDoc.open();
  print('');
  
  var pdfDoc = DocumentFactory.createDocument(DocType.pdf);
  pdfDoc.open();
  print('');
  
  var htmlDoc = DocumentFactory.createDocument(DocType.html);
  htmlDoc.open();
  print('');
  
  // Payment Processing Example
  print('--- Payment Processing Example ---');
  
  var creditCardProcessor = PaymentFactory.createProcessor(PaymentMethod.creditCard);
  creditCardProcessor.processPayment(100);
  creditCardProcessor.refundPayment(50);
  print('');
  
  var payPalProcessor = PaymentFactory.createProcessor(PaymentMethod.payPal);
  payPalProcessor.processPayment(75);
  print('');
  
  var cryptoProcessor = PaymentFactory.createProcessor(PaymentMethod.crypto);
  cryptoProcessor.processPayment(200);
}
