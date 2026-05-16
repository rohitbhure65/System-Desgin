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
interface IDocument {
  open(): void;
  close(): void;
  save(): void;
  getType(): string;
}

// Concrete Product 1: Text Document
class TextDocument implements IDocument {
  open(): void {
    console.log('Opening Text Document in text editor...');
  }
  
  close(): void {
    console.log('Closing Text Document...');
  }
  
  save(): void {
    console.log('Saving Text Document as .txt file...');
  }
  
  getType(): string {
    return 'Text Document';
  }
}

// Concrete Product 2: PDF Document
class PDFDocument implements IDocument {
  open(): void {
    console.log('Opening PDF Document in PDF viewer...');
  }
  
  close(): void {
    console.log('Closing PDF Document...');
  }
  
  save(): void {
    console.log('Saving PDF Document as .pdf file...');
  }
  
  getType(): string {
    return 'PDF Document';
  }
}

// Concrete Product 3: HTML Document
class HtmlDocument implements IDocument {
  open(): void {
    console.log('Opening HTML Document in web browser...');
  }
  
  close(): void {
    console.log('Closing HTML Document...');
  }
  
  save(): void {
    console.log('Saving HTML Document as .html file...');
  }
  
  getType(): string {
    return 'HTML Document';
  }
}

// Creator abstract class - declares the factory method
abstract class DocumentApplication {
  // Factory method - to be implemented by subclasses
  // This is the core of the pattern: subclasses decide what to create
  protected abstract createDocument(): IDocument;
  
  // Business logic that uses the product
  // This method doesn't need to know which specific document is created
  public newDocument(): void {
    const doc = this.createDocument();
    console.log(`Created: ${doc.getType()}`);
    doc.open();
    doc.save();
    doc.close();
  }
}

// Concrete Creator 1: Text Editor Application
class TextEditor extends DocumentApplication {
  protected createDocument(): IDocument {
    return new TextDocument();
  }
}

// Concrete Creator 2: PDF Viewer Application
class PDFViewer extends DocumentApplication {
  protected createDocument(): IDocument {
    return new PDFDocument();
  }
}

// Concrete Creator 3: Web Browser Application
class WebBrowser extends DocumentApplication {
  protected createDocument(): IDocument {
    return new HtmlDocument();
  }
}

// Alternative implementation: Parameterized Factory Method
// This allows a single creator to create multiple types of products
enum DocType {
  TEXT,
  PDF,
  HTML
}

class DocumentFactory {
  public static createDocument(type: DocType): IDocument {
    switch (type) {
      case DocType.TEXT:
        return new TextDocument();
      case DocType.PDF:
        return new PDFDocument();
      case DocType.HTML:
        return new HtmlDocument();
      default:
        throw new Error('Unknown document type');
    }
  }
}

// Example: Payment Processing Factory
interface PaymentProcessor {
  processPayment(amount: number): void;
  refundPayment(amount: number): void;
}

class CreditCardProcessor implements PaymentProcessor {
  processPayment(amount: number): void {
    console.log(`Processing credit card payment of $${amount}`);
  }
  
  refundPayment(amount: number): void {
    console.log(`Refunding credit card payment of $${amount}`);
  }
}

class PayPalProcessor implements PaymentProcessor {
  processPayment(amount: number): void {
    console.log(`Processing PayPal payment of $${amount}`);
  }
  
  refundPayment(amount: number): void {
    console.log(`Refunding PayPal payment of $${amount}`);
  }
}

class CryptoProcessor implements PaymentProcessor {
  processPayment(amount: number): void {
    console.log(`Processing cryptocurrency payment of $${amount}`);
  }
  
  refundPayment(amount: number): void {
    console.log(`Refunding cryptocurrency payment of $${amount}`);
  }
}

enum PaymentMethod {
  CREDIT_CARD,
  PAYPAL,
  CRYPTO
}

class PaymentFactory {
  public static createProcessor(method: PaymentMethod): PaymentProcessor {
    switch (method) {
      case PaymentMethod.CREDIT_CARD:
        return new CreditCardProcessor();
      case PaymentMethod.PAYPAL:
        return new PayPalProcessor();
      case PaymentMethod.CRYPTO:
        return new CryptoProcessor();
      default:
        throw new Error('Unknown payment method');
    }
  }
}

// Demo code
function demoFactoryMethod(): void {
  console.log('=== Factory Method Pattern Demo ===\n');
  
  // Using inheritance-based Factory Method
  console.log('--- Inheritance-based Factory Method ---');
  
  const textEditor = new TextEditor();
  textEditor.newDocument();
  console.log();
  
  const pdfViewer = new PDFViewer();
  pdfViewer.newDocument();
  console.log();
  
  const webBrowser = new WebBrowser();
  webBrowser.newDocument();
  console.log();
  
  // Using parameterized Factory Method
  console.log('--- Parameterized Factory Method ---');
  
  const textDoc = DocumentFactory.createDocument(DocType.TEXT);
  textDoc.open();
  console.log();
  
  const pdfDoc = DocumentFactory.createDocument(DocType.PDF);
  pdfDoc.open();
  console.log();
  
  const htmlDoc = DocumentFactory.createDocument(DocType.HTML);
  htmlDoc.open();
  console.log();
  
  // Payment Processing Example
  console.log('--- Payment Processing Example ---');
  
  const creditCardProcessor = PaymentFactory.createProcessor(PaymentMethod.CREDIT_CARD);
  creditCardProcessor.processPayment(100);
  creditCardProcessor.refundPayment(50);
  console.log();
  
  const payPalProcessor = PaymentFactory.createProcessor(PaymentMethod.PAYPAL);
  payPalProcessor.processPayment(75);
  console.log();
  
  const cryptoProcessor = PaymentFactory.createProcessor(PaymentMethod.CRYPTO);
  cryptoProcessor.processPayment(200);
}

// Run the demo
demoFactoryMethod();
