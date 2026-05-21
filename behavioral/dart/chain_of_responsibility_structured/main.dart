import 'interfaces.dart';
import 'handlers.dart';
import 'approvers.dart';
import 'loggers.dart';

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
