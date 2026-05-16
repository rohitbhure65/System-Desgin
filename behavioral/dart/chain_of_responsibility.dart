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
  Handler? _nextHandler;
  
  // Set the next handler in the chain
  Handler setNext(Handler handler) {
    _nextHandler = handler;
    return handler;
  }
  
  // Handle the request - to be implemented by concrete handlers
  void handle(String request);
  
  // Pass the request to the next handler if it exists
  void passRequest(String request) {
    _nextHandler?.handle(request);
  }
}

// Concrete Handler 1: Support Agent
class SupportAgent extends Handler {
  @override
  void handle(String request) {
    if (request == 'technical_issue' || request == 'basic_question') {
      print('SupportAgent: Handling request - $request');
    } else {
      print('SupportAgent: Passing to next handler...');
      passRequest(request);
    }
  }
}

// Concrete Handler 2: Technical Specialist
class TechnicalSpecialist extends Handler {
  @override
  void handle(String request) {
    if (request == 'complex_technical' || request == 'bug_report') {
      print('TechnicalSpecialist: Handling request - $request');
    } else {
      print('TechnicalSpecialist: Passing to next handler...');
      passRequest(request);
    }
  }
}

// Concrete Handler 3: Manager
class Manager extends Handler {
  @override
  void handle(String request) {
    if (request == 'refund' || request == 'complaint' || request == 'escalation') {
      print('Manager: Handling request - $request');
    } else {
      print('Manager: Passing to next handler...');
      passRequest(request);
    }
  }
}

// Example 2: Document Approval Chain
// Shows how Chain of Responsibility can be used for approval workflows

abstract class Approver {
  Approver? _nextApprover;
  
  Approver setNext(Approver approver) {
    _nextApprover = approver;
    return approver;
  }
  
  void approveRequest(double amount);
  
  void passRequest(double amount) {
    _nextApprover?.approveRequest(amount);
  }
}

class TeamLead extends Approver {
  @override
  void approveRequest(double amount) {
    if (amount <= 1000) {
      print('TeamLead: Approved request of \$${amount}');
    } else {
      print('TeamLead: Amount exceeds limit, passing to manager...');
      passRequest(amount);
    }
  }
}

class ManagerApprover extends Approver {
  @override
  void approveRequest(double amount) {
    if (amount <= 5000) {
      print('Manager: Approved request of \$${amount}');
    } else {
      print('Manager: Amount exceeds limit, passing to director...');
      passRequest(amount);
    }
  }
}

class Director extends Approver {
  @override
  void approveRequest(double amount) {
    if (amount <= 20000) {
      print('Director: Approved request of \$${amount}');
    } else {
      print('Director: Amount exceeds limit, passing to CEO...');
      passRequest(amount);
    }
  }
}

class CEO extends Approver {
  @override
  void approveRequest(double amount) {
    print('CEO: Approved request of \$${amount} (final approver)');
  }
}

// Example 3: Logging Chain
// Shows how Chain of Responsibility can be used for logging

abstract class Logger {
  Logger? _nextLogger;
  
  Logger setNext(Logger logger) {
    _nextLogger = logger;
    return logger;
  }
  
  void log(String message, int severity);
  
  void passLog(String message, int severity) {
    _nextLogger?.log(message, severity);
  }
}

class ConsoleLogger extends Logger {
  @override
  void log(String message, int severity) {
    if (severity >= 1) {
      print('[CONSOLE] $message');
    }
    passLog(message, severity);
  }
}

class FileLogger extends Logger {
  @override
  void log(String message, int severity) {
    if (severity >= 2) {
      print('[FILE] $message');
    }
    passLog(message, severity);
  }
}

class ErrorLogger extends Logger {
  @override
  void log(String message, int severity) {
    if (severity >= 3) {
      print('[ERROR] $message');
    }
    passLog(message, severity);
  }
}

// Demo code
void main() {
  print('=== Chain of Responsibility Pattern Demo ===\n');
  
  // Example 1: Customer Service Chain
  print('--- Customer Service Chain ---');
  
  var agent = SupportAgent();
  var specialist = TechnicalSpecialist();
  var manager = Manager();
  
  agent.setNext(specialist).setNext(manager);
  
  print('\nRequest: basic_question');
  agent.handle('basic_question');
  
  print('\nRequest: complex_technical');
  agent.handle('complex_technical');
  
  print('\nRequest: refund');
  agent.handle('refund');
  
  print('\nRequest: unknown');
  agent.handle('unknown');
  
  print('');
  
  // Example 2: Document Approval Chain
  print('--- Document Approval Chain ---');
  
  var teamLead = TeamLead();
  var manager2 = ManagerApprover();
  var director = Director();
  var ceo = CEO();
  
  teamLead.setNext(manager2).setNext(director).setNext(ceo);
  
  print('\nRequest: \$500');
  teamLead.approveRequest(500);
  
  print('\nRequest: \$3000');
  teamLead.approveRequest(3000);
  
  print('\nRequest: \$15000');
  teamLead.approveRequest(15000);
  
  print('\nRequest: \$50000');
  teamLead.approveRequest(50000);
  
  print('');
  
  // Example 3: Logging Chain
  print('--- Logging Chain ---');
  
  var consoleLogger = ConsoleLogger();
  var fileLogger = FileLogger();
  var errorLogger = ErrorLogger();
  
  consoleLogger.setNext(fileLogger).setNext(errorLogger);
  
  print('\nLog: Info message (severity 1)');
  consoleLogger.log('Info message', 1);
  
  print('\nLog: Warning message (severity 2)');
  consoleLogger.log('Warning message', 2);
  
  print('\nLog: Error message (severity 3)');
  consoleLogger.log('Error message', 3);
}
