/*
 * CHAIN OF RESPONSIBILITY DESIGN PATTERN
 * 
 * WHAT IS IT?
 * The Chain of Responsibility pattern lets you pass requests along a chain of handlers.
 * Each handler decides either to process the request or to pass it to the next handler in the chain.
 * 
 * WHY DOES IT EXIST?
 * - When you want to decouple senders of a request from its receivers
 * - When multiple objects can handle a request without the sender knowing which one will
 * - When you want to dynamically add or remove handlers at runtime
 * 
 * WHEN TO USE IT?
 * - When more than one object can handle a request, and the handler isn't known a priori
 * - When you want to issue a request to one of several objects without specifying the receiver explicitly
 * - When the set of objects that can handle a request should be specified dynamically
 * - Common use cases: event handling systems, logging frameworks, approval workflows, help systems
 * 
 * PROS:
 * - Decouples sender from receiver (sender doesn't know which handler will process)
 * - Open/Closed Principle (can add new handlers without changing existing code)
 * - Can control the order of handling
 * - Simplifies object interactions
 * 
 * CONS:
 * - No guarantee that a request will be handled
 * - Can lead to deep chains that are hard to debug
 * - May affect performance if the chain is long
 * - Can be difficult to observe runtime characteristics
 * 
 * REAL-WORLD ANALOGY:
 * Think of a customer service call center. When you call, your request goes through a chain of representatives. If the first representative can't help, they transfer you to a specialist. If that specialist can't help, they transfer you to a manager. The call moves up the chain until someone can help or you reach the end.
 */

// Handler interface - declares the handling method and sets a reference to the next handler
abstract class Handler {
  protected nextHandler: Handler | null = null;
  
  // Set the next handler in the chain
  setNext(handler: Handler): Handler {
    this.nextHandler = handler;
    return handler;
  }
  
  // Handle the request - to be implemented by concrete handlers
  abstract handle(request: string): void;
  
  // Pass the request to the next handler if it exists
  protected passRequest(request: string): void {
    if (this.nextHandler) {
      this.nextHandler.handle(request);
    } else {
      console.log('Request could not be handled');
    }
  }
}

// Concrete Handler 1: Support Agent
class SupportAgent extends Handler {
  handle(request: string): void {
    if (request === 'technical_issue' || request === 'basic_question') {
      console.log(`SupportAgent: Handling request - ${request}`);
    } else {
      console.log('SupportAgent: Passing to next handler...');
      this.passRequest(request);
    }
  }
}

// Concrete Handler 2: Technical Specialist
class TechnicalSpecialist extends Handler {
  handle(request: string): void {
    if (request === 'complex_technical' || request === 'bug_report') {
      console.log(`TechnicalSpecialist: Handling request - ${request}`);
    } else {
      console.log('TechnicalSpecialist: Passing to next handler...');
      this.passRequest(request);
    }
  }
}

// Concrete Handler 3: Manager
class Manager extends Handler {
  handle(request: string): void {
    if (request === 'refund' || request === 'complaint' || request === 'escalation') {
      console.log(`Manager: Handling request - ${request}`);
    } else {
      console.log('Manager: Passing to next handler...');
      this.passRequest(request);
    }
  }
}

// Example 2: Document Approval Chain
// Shows how Chain of Responsibility can be used for approval workflows

abstract class Approver {
  protected nextApprover: Approver | null = null;
  
  setNext(approver: Approver): Approver {
    this.nextApprover = approver;
    return approver;
  }
  
  abstract approveRequest(amount: number): void;
  
  protected passRequest(amount: number): void {
    if (this.nextApprover) {
      this.nextApprover.approveRequest(amount);
    } else {
      console.log('Request cannot be approved');
    }
  }
}

class TeamLead extends Approver {
  approveRequest(amount: number): void {
    if (amount <= 1000) {
      console.log(`TeamLead: Approved request of $${amount}`);
    } else {
      console.log('TeamLead: Amount exceeds limit, passing to manager...');
      this.passRequest(amount);
    }
  }
}

class ManagerApprover extends Approver {
  approveRequest(amount: number): void {
    if (amount <= 5000) {
      console.log(`Manager: Approved request of $${amount}`);
    } else {
      console.log('Manager: Amount exceeds limit, passing to director...');
      this.passRequest(amount);
    }
  }
}

class Director extends Approver {
  approveRequest(amount: number): void {
    if (amount <= 20000) {
      console.log(`Director: Approved request of $${amount}`);
    } else {
      console.log('Director: Amount exceeds limit, passing to CEO...');
      this.passRequest(amount);
    }
  }
}

class CEO extends Approver {
  approveRequest(amount: number): void {
    console.log(`CEO: Approved request of $${amount} (final approver)`);
  }
}

// Example 3: Logging Chain
// Shows how Chain of Responsibility can be used for logging

abstract class Logger {
  protected nextLogger: Logger | null = null;
  
  setNext(logger: Logger): Logger {
    this.nextLogger = logger;
    return logger;
  }
  
  abstract log(message: string, severity: number): void;
  
  protected passLog(message: string, severity: number): void {
    if (this.nextLogger) {
      this.nextLogger.log(message, severity);
    }
  }
}

class ConsoleLogger extends Logger {
  log(message: string, severity: number): void {
    if (severity >= 1) {
      console.log(`[CONSOLE] ${message}`);
    }
    this.passLog(message, severity);
  }
}

class FileLogger extends Logger {
  log(message: string, severity: number): void {
    if (severity >= 2) {
      console.log(`[FILE] ${message}`);
    }
    this.passLog(message, severity);
  }
}

class ErrorLogger extends Logger {
  log(message: string, severity: number): void {
    if (severity >= 3) {
      console.log(`[ERROR] ${message}`);
    }
    this.passLog(message, severity);
  }
}

// Demo code
console.log('=== Chain of Responsibility Pattern Demo ===\n');

// Example 1: Customer Service Chain
console.log('--- Customer Service Chain ---');

const agent = new SupportAgent();
const specialist = new TechnicalSpecialist();
const manager = new Manager();

agent.setNext(specialist).setNext(manager);

console.log('\nRequest: basic_question');
agent.handle('basic_question');

console.log('\nRequest: complex_technical');
agent.handle('complex_technical');

console.log('\nRequest: refund');
agent.handle('refund');

console.log('\nRequest: unknown');
agent.handle('unknown');

console.log('');

// Example 2: Document Approval Chain
console.log('--- Document Approval Chain ---');

const teamLead = new TeamLead();
const manager2 = new ManagerApprover();
const director = new Director();
const ceo = new CEO();

teamLead.setNext(manager2).setNext(director).setNext(ceo);

console.log('\nRequest: $500');
teamLead.approveRequest(500);

console.log('\nRequest: $3000');
teamLead.approveRequest(3000);

console.log('\nRequest: $15000');
teamLead.approveRequest(15000);

console.log('\nRequest: $50000');
teamLead.approveRequest(50000);

console.log('');

// Example 3: Logging Chain
console.log('--- Logging Chain ---');

const consoleLogger = new ConsoleLogger();
const fileLogger = new FileLogger();
const errorLogger = new ErrorLogger();

consoleLogger.setNext(fileLogger).setNext(errorLogger);

console.log('\nLog: Info message (severity 1)');
consoleLogger.log('Info message', 1);

console.log('\nLog: Warning message (severity 2)');
consoleLogger.log('Warning message', 2);

console.log('\nLog: Error message (severity 3)');
consoleLogger.log('Error message', 3);
